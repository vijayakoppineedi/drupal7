<?php

/**
 * @file
 * Admin page callbacks for the datasets module.
 */
 
 
/**
 * Form builder; Admin interface to approve/reject the organisms add by the 
 * co-ordinators.
 */

/**
 * Admin interface to approve/reject the organisms add by the 
 * co-ordinators. 
 */
function dataset_cordinator_organisms() {
  $output =  "";
  
  if(isset($_GET['sort']) && isset($_GET['order'])){
    // Sort it Ascending or Descending?
    if($_GET['sort'] == 'asc')
      $sort = 'ASC';
    else
      $sort = 'DESC';

    // Which column will be sorted
    switch($_GET['order']){
      case 'Request User':
        $order = 'fullname';
        break;
      case 'Email':
        $order = 'email';
        break;
      case 'Scientific Name':
        $order = 'genus';
        break;
      case 'Status':
        $order = 'status';
        break;
      default:
        $order = 'created';
    }
  }
  else{
    // Default sort
    $sort = 'DESC';
    $order = 'created';
  }
  // Select table
  $query = db_select("ds_request_project", "rp");
  // Select fields
  $query->fields("rp", array("id", "fullname", "email", "genus", "species", "genome_assembly_hosted", "involved_in_generation", "status", "created"));

    // Set order by
  $query->orderBy($order, $sort);
  // For pagination
  $query = $query->extend('TableSort')->extend('PagerDefault')->limit(25);  
  
  // Execute query
  $result = $query->execute();

  // Prepare table header
  // Prepare table header
  $header = array(
	      array("data" => t('Request User'),"field" => "fullname"),
              array("data" => t('Email'),"field" => "email"),
	      array("data" => t('Scientific Name'),"field" => "scientific_name"),
	      array("data" => t('Submitted GA to NCBI?'),"field" => "genome_assembly_hosted"),               
	      array("data" => t('Involved in the <br>generation of GA?'),"field" => "involved_in_generation"),
	      array("data" => t('Status'),"field" => "status"),
	      array("data" => t('Created'),"field" => "created", 'sort' => 'desc'),
	      array()			
            );  
  $rows = array();  
  $i = 0;

// Looping for filling the table rows  
  while($data = $result->fetchObject()){
    // Fill the table rows
    $rows[$i][] = $data->fullname;
	$rows[$i][] = $data->email;
	$rows[$i][] = $data->genus." ".$data->species;
	$rows[$i][] = $data->genome_assembly_hosted;
	$rows[$i][] = $data->involved_in_generation;
	$status = '';
	if($data->status == 1) $status = 'Approved';
 	else if($data->status == 0) $status = 'Rejected';
    else if($data->status == 2) $status = 'Pending'; 	 
	$rows[$i][] = $status; 	 
	$rows[$i][] = date('M d Y h:i:s A', $data->created);
	$rows[$i][] = l('Edit', 'datasets/organism/'.$data->id.'/edit');
	$i++;
  }
  	 
// Output of table with the paging
  $output = theme_table(
    array(
      "header" => $header,
      "rows" => $rows,
      "attributes" => array(),
      "sticky" => true, // Table header will be sticky
      "caption" => "",
      "colgroups" => array(),
      "empty" => t("Table has no row!") // The message to be displayed if table is empty
    )
  ).theme("pager");
  
  return $output;
}


/**
 * @hook_form()
 * Requested Organism form with options Approve/Reject  
 */ 
function datasets_organism_approval($form, &$form_state, $id) { 
 $header = array(); 
 
  // sql here
  $data = db_select('ds_request_project','rp')
          ->fields('rp',array('id', 'fullname', 'email', 'genus', 'species', 'common_name', 'genome_assembly_hosted', 'is_ncbi_submitted', 'is_assembly', 'involved_in_generation', 'no_fund', 'description', 'status'))
		  ->condition('rp.id',$id,'=')
          ->execute()->fetchObject();
  // Now build the form array
  $form = array();

  $form['datasets_table'] = array(
    '#tree' => TRUE, // Need this for easy submit processing
    '#header' => $header, // We trick Drupal to pass our $header to theme here
    '#theme' => 'datasets_organism_approval'
  );
  $form['datasets_table']['fullname'] = array(	   
	'#type' => 'value',
	'#title' => t('Name'),
	'#value' => $data->fullname,
  );
  $form['datasets_table']['email'] = array(	   
	'#type' => 'value',
	'#value' => $data->email,
  );
  $form['datasets_table']['genus'] = array(	   
	'#type' => 'value',
	'#value' => $data->genus,
  );
  $form['datasets_table']['species'] = array(
        '#type' => 'value',
        '#value' => $data->species,
  );
  $form['datasets_table']['common_name'] = array(
        '#type' => 'value',
        '#value' => $data->common_name,
  );
  $form['datasets_table']['genome_assembly_hosted'] = array(	   
	'#type' => 'value',
	'#value' => $data->genome_assembly_hosted,
  );
  
  $form['datasets_table']['is_ncbi_submitted'] = array(	   
	'#type' => 'value',
	'#value' => $data->is_ncbi_submitted,
   );

   $form['datasets_table']['is_assembly'] = array(	   
	'#type' => 'value',
	'#value' => $data->is_assembly,
  );
   
  $form['datasets_table']['involved_in_generation'] = array(	   
	'#type' => 'value',
	'#value' => $data->involved_in_generation,
  );

  $form['datasets_table']['description'] = array(
        '#type' => 'value',
        '#title' => 'Description',
        '#value' => $data->description,
  );

  $status = '';

  if($data->status == 1) $status = 'Approved';
  else if($data->status == 0) $status = 'Pending'; 
  else $status = 'Rejected';
	 
  $form['datasets_table']['status'] = array(
    '#type' => 'radios',  	
    '#default_value' => $data->status,
    '#options' => array(t('Reject'), t('Approve')),
  );
  $form['datasets_table']['id'] = array(	   
	'#type' => 'value',
	'#value' => $data->id,
  );
	 
  // Submit function
  $form['datasets_table']['submit'] = array(
    '#type' => 'submit',
    '#name' => 'submit',
    '#value' => t('Save'),
  );

  return $form; 
}

/**
 * @hook_form_submit()
 * 
 * @sends an email to user regarding login credentails to the web apollo site.
 */ 
function datasets_organism_approval_submit($form, &$form_state) {
  $values = $form_state['values']['datasets_table'];
  //echo "<pre>"; print_r($values);echo "</pre>";exit;
  $status = $values['status'];
  $id = $values['id'];  
  $to = $values['email'];  
  $from = FROM_ADDRESS; 
  
  $status_res = db_select('ds_request_project','rq')
          ->fields('rq',array('status'))
		  ->condition('rq.id',$id,'=')
          ->execute()->fetchField();
		
  if($status_res != $status && $status == 1) {	
     db_update('ds_request_project')
		->fields(array('status' => $status))
		->condition('id', $id, '=')
		->execute();
   //   Send email to the user about the login credentials to the web apollo site
      $user_email_sent = drupal_mail('datasets', 'request_project_approved_email', $to, language_default(), $values, $from, TRUE);

    // drupal_set_message(t('Successfully an email was sent to '.$values['email'].' regarding the status approved.'));

      /************************************************************
       ***********************************************************
       INSERT the approved request project 'organism' into  chado .*/
     // sql here
 /*  $data = db_select('ds_request_project','rp')
          ->fields('rp',array('id', 'fullname', 'email', 'genus', 'species', 'genome_assembly_hosted', 'is_ncbi_submitted', 'is_assembly', 'involved_in_generation', 'no_fund', 'description', 'status'))
                  ->condition('rp.id',$id,'=')
          ->execute()->fetchObject();
*/
      $node = new stdClass();
      $node->type = "chado_organism";
      $node->language = "und";
      $node->title = $values['genus']." ".$values['species'];
      $node->uid = 1;
      $node->status = 0;
      $node->created = time();
      $node->changed = time();
      $node->promote = 0;

    
      $node->genus = trim($values['genus']);               
      $node->species = trim($values['species']);
      $node->abbreviation = $node->genus[0].". ".$node->species; //trim($data->abbreviation);
      $node->common_name  = trim($values['common_name']);
      $node->description  = trim($values['description']);

      node_save(&$node);

      $organism_id = $node->organism->organism_id;
//echo "<pre>"; print_r($node); echo "</pre>"; exit;
      $check_org_id = chado_get_id_from_nid('organism', $node->nid);
      if (!$check_org_id) {
        $record = new stdClass();
        $record->nid = $node->nid;
        $record->vid = $node->vid;
        $record->organism_id = $organism_id;
	drupal_write_record('chado_organism', $record);
      }
      // Adding the new approved organism to the datasets settings textarea - admin/structure/webapollo/settings.
      $web_apollo_organism = variable_get('web_apollo_organism');
      $web_apollo_organism = $web_apollo_organism."\n";
      $organism_shortcut = strtolower(substr($values['genus'], 0, 3).substr($values['species'], 0, 3));
      $web_apollo_organism .= $organism_shortcut.'|'. $values['genus'].' '.$values['species'].'|0';
      
      variable_set('web_apollo_organism', $web_apollo_organism);
 
      /*******************************************************************************************
       *******************************************************************************************/
	
	//} 
	//Displaying status message on the site
   $status = ($status == 1)?'Approved': 'Rejected';  
    drupal_set_message(t($values['genus']." ".$values['species']." status was changed to ".$status));
  } else if($status == 0) {
    db_update('ds_request_project') // Table name no longer needs {}
	  ->fields(array('status' => $status))
	  ->condition('id', $id, '=')
	  ->execute();

    $query = db_select('organism', 'o');
    // Select fields
    $query->fields("o", array("organism_id"));
    // Condition
    $query->condition("genus", $values['genus']);
    // Execute query
    $result = $query->execute()->fetchObject();

    $oid = $result->organism_id;
    $node_id = chado_get_nid_from_id('organism', $oid);
    // Deletinge node related tables, chado_organism and chado.organism table
    db_delete('node')
      ->condition('nid', $node_id, '=')
      ->execute();
    db_delete('node_revision')
      ->condition('nid', $node_id, '=')
      ->execute();
    db_delete('history')
      ->condition('nid', $node_id, '=')
      ->execute();
    db_delete('node_access')
      ->condition('nid', $node_id, '=')
      ->execute();
    db_delete('chado_organism')
      ->condition('nid', $node_id, '=')
      ->execute();
    db_delete('organism')
      ->condition('organism_id', $oid, '=')
      ->execute();

    //Also removing rejected organism from the settings form - admin/structure/webapollo/settings
    $web_apollo_organism = variable_get('web_apollo_organism');
    $organism_shortcut = strtolower(substr($values['genus'], 0, 3).substr($values['species'], 0, 3));
    $remove_str = $organism_shortcut.'|'. $values['genus'].' '.$values['species'].'|0';
    $replace_organism = str_replace($remove_str, '', $web_apollo_organism);
    variable_set('web_apollo_organism', $replace_organism);

    drupal_set_message(t($values['genus'].' '.$values['species'].' has been rejected by  the admin due to some reasons.'));    
  }   
 
  $form_state['redirect'] = 'admin/structure/datasets';
  return;
}



function dataset_report($form, &$form_state) {  
  $web_apollo_organism = variable_get('web_apollo_organism');
  if(!empty($web_apollo_organism)) {    
    $organism_options = get_webapollo_organisms($web_apollo_organism); 
  }
  ksort($organism_options, 2);
 
  if(!empty($form_state['input']['organism'])) {  
    $organism_selected = $form_state['input']['organism']; 
  } else if(isset($_GET['organism']) && !empty($_GET['organism'])) {
    $organism_selected = $_GET['organism'];
  } 

  $_GET['q'] = 'admin/structure/datasets/report';  
//echo "organism selected ".$_SESSION['organism']." - ".$organism_selected;

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'datasets') . '/css/report.css',
  );
   $form['header_text'] = array(
    '#markup' => t('<div id="text">Below report is for user\'s who submitted their datasets for Assembly, gene and mapped.</div>')
    );  

  $form['organism'] = array(
    '#type' => 'select',
    '#title' => t('Organism'),
    '#options' => $organism_options, 
    '#default_value' => $organism_selected,
    '#description' => t('If no organism is selected it shows by default all organism data.'),
    '#ajax' => array(      
           'callback' => 'report_callback',
           'wrapper' => 'report',
      ),    
  );

  $rows = array(); 
  if(isset($organism_selected)) {
    $rows = datasets_all($organism_selected);
  } else {  
    $rows = datasets_all();
  }
  
  // Prepare table header
  $header = array(
	      array("data" => t('Name'), 'field' => 'name'),
              array("data" => t('Email'), 'field' => 'email'),
	      array("data" => t('Organism'), 'field' => 'organism', 'org' => 'vj'),
	      array("data" => t('Type'), 'field' => 'type'),
	      array("data" => t('Created'), 'field' => 'created'),		  
	      array(),			
        ); 

  $order = tablesort_get_order($header);
  $sort = tablesort_get_sort($header);
  $sql=$order['sql']; 
  if($sort=='desc') {
    usort($rows, function($a, $b) use($sql) {
      $order_fields = array('name' => 0, 'email' => 1, 'organism' => 2, 'type' => 3, 'created' => 4); 
      $okey = $order_fields[$sql];
      return strtolower($a[$okey]) > strtolower($b[$okey])? -1 : 1;
    });

  }
  if($sort=='asc') {
      usort($rows, function($a, $b) use ($sql) {
        $order_fields = array('name' => 0, 'email' => 1, 'organism' => 2, 'type' => 3, 'created' => 4);
        $okey = $order_fields[$sql];
        return strtolower($a[$okey]) < strtolower($b[$okey])? -1 : 1;
      });
  }
		
//   echo "<prE>";   print_r($rows);echo "</pre>";
  $per_page = 25;
  // Initialize the pager
  $current_page = pager_default_initialize(count($rows), $per_page);

  // Split your list into page sized chunks
  $chunks = array_chunk($rows, $per_page, TRUE);

  // Show the appropriate items from the list
  //$output = theme('table', array('header' => $header, 'rows' => $chunks[$current_page]));
  // Show the pager
  //$output .= theme('pager', array('quantity',count($rows)));
  
  $output = theme_datasets_table(
    array(
      "header" => $header,
      "rows" => $chunks[$current_page],
      "attributes" => array('org' => $organism_selected),
      "sticky" => true, // Table header will be sticky
      "caption" => "",
      "colgroups" => array(),
      "empty" => t("Table has no row!") // The message to be displayed if table is empty
    )
  ); 
  $parameters = array('organism', $organism_selected);
  $pager = array();
  $pager['quantity'] = count($rows);
  $output .= theme('pager', array('quantity' => count($rows), 'parameters' => array('organism' => $organism_selected)) );
//   $output .= theme('pager', array('quantity' => count($rows));

  $form['result'] = array(
    '#prefix' => '<div id="report">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',    
  );

  if (isset($form_state['input']['organism']) ) { 	  
    $form['result']['report']['#suffix'] = $output;
  } else {    
    $form['result']['report']['#suffix'] = $output;
  }
  
  return $form;
}

function datasets_report_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

class DsTableSort extends TableSort {
/**
 * Compose a URL query parameter array for table sorting links.
 *
 * @return
 *   A URL query parameter array that consists of all components of the current
 *   page request except for those pertaining to table sorting.
 */
  public function tablesort_get_query_parameters() {
    return drupal_get_query_parameters($_GET, array('q', 'sort', 'order', 'nid'));
  }
}

function datasets_all($organism) {
  $web_apollo_organism = variable_get('web_apollo_organism');
  if(!empty($web_apollo_organism)) {    
    $organism_options = get_webapollo_organisms($web_apollo_organism); 
  }  
  
  $sort = 'DESC';
  $order = 'name';
  //echo "organism ".$organism;
  // Select table
  $query = db_select("ds_organism_assembly", "c");
  // Select fields
  $query->fields("c", array("oa_id", "name", "email", "organism", "created"));  
  // condition
  if(!empty($organism)) {
    $query->condition('organism', $organism);  
  }
    // Set order by
  $query->orderBy($order, $sort);
  // Execute query
  $result_oa = $query->execute()->fetchAll(); 
   
  $rows = array();  
  $i = 0;

  // Looping for filling the table rows  
  foreach($result_oa as $key => $data) {
    // Fill the table rows
    $rows[$i][] = $data->name;
    $rows[$i][] = $data->email;
    $rows[$i][] = $organism_options[$data->organism];
    $rows[$i][] = "Assembly";
    $rows[$i][] = date('M d Y', $data->created);
	
    $rows[$i][] = l('view', '/datasets_og/'.$data->oa_id.'/view',  array('attributes' => array('target'=>'_blank')));
    $i++;
  }
  
  // Gene prediction   
  $query_gene = db_select("ds_gene_prediction", "c");
  // Select fields
  $query_gene->fields("c", array("pid", "name", "email", "organism", "created"));  
   // condition
  if(!empty($organism)) {
    $query_gene->condition('organism', $organism);  
  }
    // Set order by
  $query_gene->orderBy($order, $sort);
  // Execute query
  $result_gene = $query_gene->execute()->fetchAll();

  if(!empty($result_gene)) { 
    foreach($result_gene as $key_gene => $data_gene) {
      // Fill the table rows
      $rows[$i][] = $data_gene->name;
	  $rows[$i][] = $data_gene->email;
	  $rows[$i][] = $organism_options[$data_gene->organism];
	  $rows[$i][] = "Gene Prediction";
	  $rows[$i][] = date('M d Y', $data_gene->created);
	
	  $rows[$i][] = l('view', '/datasets_gp/'.$data_gene->pid.'/view',  array('attributes' => array('target'=>'_blank')));
	  $i++;
    }
  }
  
  // Mapped dataset - Select table
  $query_map = db_select("ds_mapped_dataset", "c");
  // Select fields
  $query_map->fields("c", array("id", "name", "email", "organism", "created"));  
   // condition
  if(!empty($organism)) {
    $query_map->condition('organism', $organism);  
  } 
    // Set order by
  $query_map->orderBy($order, $sort);
  // For pagination
 // $query = $query_map->extend('TableSort')->extend('PagerDefault')->limit(10);    
  // Execute query
  $result_map = $query_map->execute()->fetchAll();
  
  
  if(!empty($result_map)) {
    foreach($result_map as $key_map => $data_map) {
      // Fill the table rows
      $rows[$i][] = $data_map->name;
	  $rows[$i][] = $data_map->email;
	  $rows[$i][] = $organism_options[$data_map->organism];
	  $rows[$i][] = "Mapped dataset";
	  $rows[$i][] = date('M d Y', $data_map->created);
	
	  $rows[$i][] = l('view', '/datasets_md/'.$data_map->id.'/view',  array('attributes' => array('target'=>'_blank')));
	  $i++;
    }
  }
    
  return $rows;
  
}

function report_callback($form, $form_state) {    
  return $form['result'];  
}
