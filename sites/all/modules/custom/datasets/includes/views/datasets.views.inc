<?php

function datasets_views_data() {
  $data['ds_organism_assembly']['table']['group'] = t('ds_organism_assembly');

  $data['ds_organism_assembly']['table']['base'] = array(
    'field' => 'oa_id',
    'title' => t('ds_organism_assembly'), 
    'help' => t('ds_organism_assembly contains assembly dataset for organisms.'), 
    'weight' => -10,
  );

  $data['ds_organism_assembly']['table']['join'] = array(
    'node' => array(
      'left_field' => 'oa_id', 
      'field' => 'oa_id',
    ),
  );

  $data['ds_organism_assembly']['oa_id'] = array(
    'title' => t('oa_id'), 
    'help' => t('Organism assembly id.'),
    /*'relationship' => array(
      'base' => 'node',
      'base field' => 'oa_id', // The name of the field on the joined table.
      // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
      'handler' => 'views_handler_relationship', 
      'label' => t('organism assembly'),
    ),	*/
	'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['ds_organism_assembly']['name'] = array(
    'title' => t('co-ordinator name'), 
    'help' => t('Just a name field.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['ds_organism_assembly']['email'] = array(
    'title' => t('Email'), 
    'help' => t('Just a Email field.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['ds_organism_assembly']['taxid'] = array(
    'title' => t('Taxid'), 
    'help' => t('Just an taxid field.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
    
  $data['ds_organism_assembly']['organism'] = array(
    'title' => t('Organism'), 
    'help' => t('Organism field.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'organism_filter_in_operator',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['ds_organism_assembly']['common_name'] = array(
    'title' => t('common_name'), 
    'help' => t('common_name field.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  $data['ds_organism_assembly']['timestamp_field'] = array(
    'title' => t('Timestamp'), 
    'help' => t('Just a timestamp field.'), 
    'field' => array(
      'handler' => 'views_handler_field_date', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  
  $data['ds_gene_prediction']['table']['group'] = t('ds_gene_prediction');

  $data['ds_gene_prediction']['table']['base'] = array(
    'field' => 'pid',
    'title' => t('ds_gene_prediction'), 
    'help' => t('ds_gene_prediction contains gene prediction data for organisms.'), 
    'weight' => -10,
  );

  $data['ds_gene_prediction']['table']['join'] = array(
    'node' => array(
      'left_field' => 'pid', 
      'field' => 'pid',
    ),
  );

  $data['ds_gene_prediction']['pid'] = array(
    'title' => t('pid'), 
    'help' => t('gene prediction id.'),
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['ds_gene_prediction']['name'] = array(
    'title' => t('co-ordinator name'), 
    'help' => t('Just a name field.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['ds_gene_prediction']['email'] = array(
    'title' => t('Email'), 
    'help' => t('Just a Email field.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

    
  $data['ds_gene_prediction']['organism'] = array(
    'title' => t('Organism'), 
    'help' => t('Organism field.'), 
    'field' => array(
      'handler' => 'views_handler_field', 
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'organism_filter_in_operator',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}


/**
 * Define my custom in_opeator
 */
class organism_filter_in_operator extends views_handler_filter_in_operator {
  // overwrite the get_value_options function.
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }
	$web_apollo_organism = variable_get('web_apollo_organism');
    if(!empty($web_apollo_organism)) {
      $organism_list = get_webapollo_organisms($web_apollo_organism);
    }	

    $this->value_options = $organism_list;
  }
}
