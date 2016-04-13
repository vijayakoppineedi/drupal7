<?php
/**
 * @file
 * latest_news_category.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function latest_news_category_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function latest_news_category_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function latest_news_category_node_info() {
  $items = array(
    'news' => array(
      'name' => t('News'),
      'base' => 'node_content',
      'description' => t('Creates News content type and displays the latest news in a block'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'news_category' => array(
      'name' => t('News category'),
      'base' => 'node_content',
      'description' => t('Add an image based on the new category'),
      'has_title' => '1',
      'title_label' => t('Category'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
