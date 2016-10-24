<?php
/**
 * @file
 * ajm_news.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ajm_news_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ajm_news_node_info() {
  $items = array(
    'news' => array(
      'name' => t('News article'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
