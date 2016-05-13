<?php
/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * {{ THEME NAME }} theme.
 */


/**
 * VIJAYA - Implements hook_preprocess_search_results().
 */
function i5k_preprocess_search_result(&$variables) {
  // If this search result is coming from our module, we want to improve the
  // template potential to make life easier for themers.
  if ($variables['module'] == 'apachesolr_search') {
    $result = $variables['result'];
    //VIJAYA - adding document files
    if(!empty($result['fields']['filename'])) {
      $variables['title'] = $result['fields']['filename'];
      $variables['result']['entity_type'] = 'localfile';
      $get_path = preg_split('/data/', $result['fields']['filepath']);
      $split_count = count($get_path);
      $get_filepath = ($split_count > 1) ? "/data".$get_path[1]:"/".$result['fields']['filepath'];
      $filepath = $GLOBALS['base_url'].$get_filepath;
      $variables['url'] = $filepath;
      $variables['localfiles'] = '1';
    }
  }
}

function i5k_bootstrap_preprocess_page(&$variables) {
  //Overriding user login title
  if (arg(0) == 'user' && arg(1) == 'login') {
    $variables['title'] = t('i5k Workspace login');
  } elseif (arg(0) == 'user' && arg(1) == '') {
    $variables['title'] = t('i5k Workspace login');
  }
  // Add information about the number of sidebars.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-4"';
  }
  elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-md-9"';
  }
  else {
    $variables['content_column_class'] = ' class="col-sm-12"';
  }
}


