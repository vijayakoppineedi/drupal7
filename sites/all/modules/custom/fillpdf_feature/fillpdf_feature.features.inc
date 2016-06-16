<?php
/**
 * @file
 * fillpdf_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fillpdf_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function fillpdf_feature_node_info() {
  $items = array(
    'fillpdf_form' => array(
      'name' => t('Image use permission form'),
      'base' => 'node_content',
      'description' => t('PDF form'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
