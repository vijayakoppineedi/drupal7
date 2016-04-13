<?php

/**
 * @file
 * Drush commands needed to search and index files.
 */
//require_once  'sites/all/modules/contrib/apachesolr/apachesolr.module';
/**
 * Implements hook_drush_command().
 * VIJAYA - Added 2 parameters
 * - one for first/update and
 * - For specific filename
 * 
 */
function apachesolr_localfiles_drush_command() {
  $commands = array();
  $commands['solr-local'] = array(
    'description' => t('Search for files changed after the last search'),
    'required-arguments' => 1,
    'arguments' => array('search type' => "Specify if it's the first search or an update search",
	                    
	                     ),
  );
  return $commands;
}

/**
 * Callback for command search-updated-files.
 * VIJAYA - Added 2nd parameter to specific filename
 *        - For Multiple filenames separate with space
 *        - Ex: test.pdf, test.pdf hello.pdf 
 */
function drush_apachesolr_localfiles_solr_local() {
  $folders_to_search = variable_get('apachesolr_localfiles_folder');
  //echo "folders search "; print_r($folders_to_search);exit;
  $folders_to_search_formatted = '';
  foreach ($folders_to_search as $folder) {
    $folders_to_search_formatted .=  '"' . $folder['to'] . '" ';
  }
  $numargs = func_num_args();
  $args = func_get_args();
  if($args[1] != 'data')
    print t('Starting to search on ') . $folders_to_search_formatted . '...' . "\n";
  $opt = '';
  if(($numargs == 2) && ($args[1] == 'data')) {
    print t('Starting to search on sites/default/files/data').  "\n";
    $cmd = 'find ../drupal/sites/default/files/data -name "*.*"';
  } else if(($numargs == 2) && ($args[0] == 'update') && isset($args[1])) {  
    //VIJAYA  - added parameter to the index specific file    
    $second_param = explode(' ', $args[1]);	
	if(count($second_param) >= 1) {
	  $opt_file = '';
	  foreach($second_param as $key => $specific_file) {
	    $opt_file .= ' -name '.$specific_file.' -o';
	  }	  	  
	  
	  $opt_file = substr($opt_file, 0, -3); 
	}   	
	$cmd = 'find ' . $folders_to_search_formatted . $opt_file;
	
  } else if (($numargs == 1) && ($args[0] == 'update' || $args[0] == 'first')) { // updating the index with new files
    $last_index = variable_get('apachesolr_localfiles_last_index');	
    if (!empty($last_index)) {
      $now = time();
      $difference_in_minutes = ceil(($now - $last_index) / 60);
      $opt .= ' -mmin -' . $difference_in_minutes;
    }
	//echo "last index ".$opt;    
	
    $file_extensions_to_search = variable_get('apachesolr_localfiles_mimetypes_allowed');
    if (!empty($file_extensions_to_search)) {
      foreach ($file_extensions_to_search as $ext) {
        if (!empty($ext)) { // The settings form save option as zero
          $opt .= ' -name "*.' . $ext . '" -o';
        }
      }
	
      $opt = substr($opt, 0, -3);
    }
    $cmd = 'find ' . $folders_to_search_formatted . ' -type f' . $opt;     
  } else {
    print t('[ERROR] You passed the wrong parameters. The only two options are "first" and "update".') . "\n";
    return FALSE;
  } 

  $shell_return = shell_exec($cmd);

  if ($shell_return) {

    $files_array = explode("\n", $shell_return);
    array_pop($files_array);

    $solr_url = 'http://gmod-dev7.nal.usda.gov:8983/solr/collection_one';
    foreach ($files_array as $filepath) {
      $parameter_via_hooks = module_invoke_all('apachesolr_localfiles_indexing_parameter', $filepath);
      if(basename($filepath) == ".htaccess") {
        continue;
      }

      // Check if it is directory or file  
      if(is_file($filepath) && (urlencode(basename($filepath)) != 'readme') ) {
        $id = transliteration_clean_filename($filepath);
        $cmd = 'curl "' . $solr_url . '/update/extract?commit=true&literal.id=' . $id;	  
        $cmd .= '&literal.filepath=' . urlencode($filepath);
        $cmd .= '&literal.filename=' . urlencode(basename($filepath));
	  if($args[1] == 'data') {
            $split_filepath = preg_match_all('/\((.*?)\)/', $filepath, $matches);
            $organism_name = preg_replace('/_/', '+', $matches[1][0]);
            $content_text = $organism_name.'+'.urlencode(basename($filepath));
           //$content_text =  preg_replace('/\s+/s', ' ', $content_text);
            $content_text = apachesolr_clean_text($content_text);  
	    $cmd .= '&literal.content='.$content_text;
          }
        if (!empty($parameter_via_hooks)) {
          $cmd .= '&' . implode('&', $parameter_via_hooks);
        }
        $cmd .= '"';
        $cmd .= ' -F "file=@' . $filepath . '"';
        shell_exec($cmd);
      } 
    }

    variable_set('apachesolr_localfiles_last_index', time());
  }
  else {
    watchdog('error', t('apachesolr_localfiles had a problem indexing the files'));
  }
}
