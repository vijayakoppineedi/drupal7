<?php

/**
 * @file
 * Bulk export of facetapi_defaults objects generated by Bulk export module.
 */

/**
 * Implements hook_facetapi_default_facet_settings().
 */
function apachesolr_localfiles_facetapi_default_facet_settings() {
  $facets = array();

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@' . APACHESOLR_LOCALFILES_ID . ':block:content_type';
  $facet->searcher = 'apachesolr@' . APACHESOLR_LOCALFILES_ID; // defined in the .module
  $facet->realm = 'block';
  $facet->facet = 'content_type';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'weight' => 0,
    'widget' => 'facetapi_links',
    'filters' => array(),
    'active_sorts' => array(
      'active' => 'active',
      'count' => 'count',
      'display' => 'display',
    ),
    'sort_weight' => array(
      'active' => -50,
      'count' => -49,
      'display' => -48,
    ),
    'sort_order' => array(
      'active' => 3,
      'count' => 3,
      'display' => 4,
    ),
    'empty_behavior' => 'none',
    'soft_limit' => 20,
    'nofollow' => 1,
    'show_expanded' => 0,
    'empty_text' => array(
      'value' => '',
      'format' => 'plain_text',
    ),
  );
  $facets[$facet->name] = $facet;

  return $facets;
}