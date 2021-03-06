<?php

/**
 * @file
 * Admin page callbacks for the Contact module.
 */
 
 
/**
 * List the web apollo registered users with pagination and 
 * with Approve/Reject options
 **/
function webapollo2_register_users() {
  $output =  "";
  
  if(isset($_GET['sort']) && isset($_GET['order'])){
    // Sort it Ascending or Descending?
    if($_GET['sort'] == 'asc')
      $sort = 'ASC';
    else
      $sort = 'DESC';

    // Which column will be sorted
    switch($_GET['order']){
      case 'Name':
        $order = 'name';
        break;
      case 'Email':
        $order = 'email';
        break;
      case 'Organism':
        $order = 'organisms';
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
  $query = db_select("webapollo2_users", "w");
  // Select fields
  $query->fields("w", array("uid", "name", "email", "organisms", "status", "created"));
    // Set order by
  $query->orderBy($order, $sort);
  // For pagination
  $query = $query->extend('TableSort')->extend('PagerDefault')->limit(25);  
  
  // Execute query
  $result = $query->execute();
  
  // Prepare table header
  // Prepare table header
  $header = array(
			array("data" => t('Name'),"field" => "name"),
            array("data" => t('Email'),"field" => "email"),
			array("data" => t('Organism'),"field" => "Organisms"),
			array("data" => t('Status'),"field" => "status"),
			array("data" => t('Created'),"field" => "created", 'sort' => 'desc'),
			array()			
          );
  
    // Now build the form array
  $web_apollo_organism = variable_get('web_apollo_organism');
  $organism_data = get_webapollo_organisms($web_apollo_organism, $annotation=2); 
  
  $rows = array();  
  $i = 0;

// Looping for filling the table rows  
  while($data = $result->fetchObject()){
    // Fill the table rows
    $rows[$i][] = $data->name;
	$rows[$i][] = $data->email;
	$rows[$i][] = (isset($organism_data[$data->organisms]))?$organism_data[$data->organisms]:'';
	$status = '';
	if($data->status == 1) $status = 'Approved';
 	else if($data->status == 0) $status = 'Rejected';
    else if($data->status == 2) $status = 'Pending'; 	 
	$rows[$i][] = $status; 	 
	$rows[$i][] = date('M d Y h:i:s A', $data->created);
	$rows[$i][] = l('Edit', 'webapollo2/user/'.$data->uid.'/edit');
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
 * Registered user form with options Approve/Reject  
 */ 
function webapollo2_user_approval($form, &$form_state, $uid) { 
 $header = array(); 
 
  // sql here
  $data = db_select('webapollo2_users','w')
          ->fields('w',array('uid', 'name', 'pass', 'email', 'organisms', 'status'))
		  ->condition('w.uid',$uid,'=')
          ->execute()->fetchObject();
	

  // Now build the form array
  $form = array();

  $form['web_apollo_table'] = array(
    '#tree' => TRUE, // Need this for easy submit processing
    '#header' => $header, // We trick Drupal to pass our $header to theme here
    '#theme' => 'webapollo2_user_approval'
  );
  $form['web_apollo_table']['name'] = array(	   
	'#type' => 'value',
	'#title' => t('Name'),
	'#value' => $data->name,
  );
  $form['web_apollo_table']['email'] = array(	   
	'#type' => 'value',
	'#value' => $data->email,
  );
 
  $web_apollo_organism = variable_get('web_apollo_organism');
  $organism_data = get_webapollo_organisms($web_apollo_organism, $annotation=2);         
  $organism_value = $organism_data[$data->organisms];

  $form['web_apollo_table']['organism_key'] = array(	   
	'#type' => 'value',
	'#value' => $data->organisms,
   );
	 
  $form['web_apollo_table']['organism'] = array(	   
	'#type' => 'value',
	'#value' => $organism_value,
  );

  $status = '';

  if($data->status == 1) $status = 'Approved';
  else if($data->status == 0) $status = 'Pending'; 
  else $status = 'Rejected';
	 
  $form['web_apollo_table']['status'] = array(
    '#type' => 'radios',  
    '#default_value' => $data->status,
    '#options' => array(t('Reject'), t('Approve')),
  );
	
  $form['web_apollo_table']['uid'] = array(	   
	'#type' => 'value',
	'#value' => $data->uid,
  );
	
  $form['web_apollo_table']['pass'] = array(	   
	'#type' => 'value',
	'#value' => $data->pass,
   );
	 
  // Submit function
  $form['web_apollo_table']['submit'] = array(
    '#type' => 'submit',
    '#name' => 'submit',
    '#value' => t('Save'),
  );
 
  return $form; 
}

/**
 * @hook_form_submit()
 * Runs the add_user.pl and set_track_permissions.pl to create user accounts and permissions for respective organisms.
 * @sends an email to user regarding login credentails to the web apollo site.
 */ 
function webapollo2_user_approval_submit($form, &$form_state) {
  $values = $form_state['values']['web_apollo_table'];
  $status = $form_state['values']['web_apollo_table']['status'];
  $uid = $form_state['values']['web_apollo_table']['uid'];  
  $genus_species = str_replace(' ', '_', $form_state['values']['web_apollo_table']['organism']);
  $to = $values['email'];  
  $from = FROM_ADDRESS;

  $status_res = db_select('webapollo2_users','w')
          ->fields('w',array('status'))
		  ->condition('w.uid',$uid,'=')
          ->execute()->fetchField();

  if( ($status_res != $status) && ($status == 1)) {  
    /***************web apollo automated login credentials*******************************/
    $web_apollo_organism = variable_get('web_apollo_organism');
    if(!empty($web_apollo_organism)) {
      $organism_data = get_webapollo_organisms($web_apollo_organism, $annotation=2);
    }
	  
    $db_name = "apollo2"; 	
    $db_user = "webapollo";
    $db_pass = "web2apollo";

    /****
      The goal is to make the password same for all organism for same emailid.
      First check for the email already registered for any organism with status=1, if yes then take the most recent password and update in webapollo_users and apollo tables.
      IF not then check for email with status=2, then take most recent password and update in webapollo_uses and apollo tables.
    */
    $email = $to;
    $check_email_status1_exists = db_select('webapollo2_users', 'w')
                                  ->fields('w', array('uid', 'name', 'pass', 'organisms'))
                                  ->condition('w.email', $email, '=')
                                  ->condition('w.status',1,'=')
                                  ->orderby('w.created', 'desc')
                                  ->range(0,1)
                                  ->execute()->fetchObject();


    $check_email_status2_exists = db_select('webapollo2_users', 'w')
                                  ->fields('w', array('uid', 'name', 'pass', 'organisms'))
                                  ->condition('w.email', $email, '=')
                                  ->condition('w.status',2,'=')
                                  ->orderby('w.created', 'desc')
                                  ->range(0,1)
                                  ->execute()->fetchObject();

 
    $user = $values['email'];  
   
    if(isset($check_email_status1_exists) && !empty($check_email_status1_exists)) {   
      $pass = $check_email_status1_exists->pass;
      db_update('webapollo2_users')->fields(array('pass' => $pass))->condition('uid',$uid,'=')->execute();     
       
    } else if(isset($check_email_status2_exists) && !empty($check_email_status2_exists)) {
      $pass = $check_email_status2_exists->pass;
      db_update('webapollo2_users')->fields(array('pass' => $pass))->condition('uid',$uid,'=')->execute();
    } else
      $pass = $values['pass'];

    // If the values['pass'] should be the updated password from recent password.
    if($values['pass'] != $pass) {
      $values['pass'] = $pass;
    } 

    $user_pass_values['organism'] = isset($values['organism_key'])?$organism_data[$values['organism_key']]:'';
    $user_pass_values['user'] = $user;
    $user_pass_values['pass'] = $pass;

    $exec_user = exec("python /usr/local/drupal/sites/all/modules/custom/web_apollo2/adduser.py -dbuser ".$db_user."  -dbname ".$db_name." -user ".$user." -pwd ".$pass." -organism ".$genus_species);

    //Send email to the user about the login credentials to the web apollo site
    $user_email_sent = drupal_mail('web_apollo2', 'webapollo2_user_approve_email', $to, language_default(), $values, $from, TRUE);

    if(!$user_email_sent) {	  
      drupal_set_message(t('Failed to send the email due to some technical problems'));	  
    } else {
	  db_update('webapollo2_users') // Table name no longer needs {}
		->fields(array('status' => $status))
		->condition('uid', $uid, '=')
		->execute();
     drupal_set_message(t('Successfully an email was sent to '.$values['email'].' regarding the status approved.'));
    }
   	
    //Displaying status message on the site
    $status = ($status == 1)?'Approved': 'Rejected';  
    drupal_set_message(t($form_state['values']['web_apollo_table']['name']."'s status was changed to ".$status));    
  } // Status approved condition ends here
  else if($status == 0) {
       db_update('webapollo2_users') // Table name no longer needs {}
		->fields(array('status' => $status))
		->condition('uid', $uid, '=')
		->execute();
	  drupal_set_message(t($values['name'].' has been rejected by  the admin due to some reasons.'));
  }   
  /**********************************************/ 
  
  $form_state['redirect'] = 'admin/structure/webapollo/apollo2';
  return;
}

/**
 * Search key by value from an array
 **/
 function searchkey($organism_data, $needle)
{
   foreach($organism_data as $key => $data)
   {  
      if(strcmp($key, $needle) == 0) {
	   return $key;
	  }
   }
   return false;
}
