<?php
/**
 * @file
 * mymodule.tokens.inc
 */

/**
 * Implements hook_token_info().
 */
function mymodule_token_info() {
  $info['tokens']['node']['first_letter'] = array(
    'name' => t('First Letter'),
    'description' => t('The first letter of the node title.'),
  );
  $info['tokens']['node']['field_services_titleshort_join'] = array(
    'name' => t('All subsites from field_services'),
    'description' => t('Referenced subsite short title values, joined.'),
  );
  return $info;
}

/**
 * Implements hook_tokens().
 */
function mymodule_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  //$sanitize = !empty($options['sanitize']);
  // Node tokens.
  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];
    foreach ($tokens as $name => $original) {
    	switch ($name) {
    		case 'first_letter':
    			$the_title = $node->title;
          $title_fl = substr($the_title,0,1);
          $replacements[$original] = $title_fl;
          break;
        case 'field_services_titleshort_join':
          if (isset($node->field_services) && $node->field_services <> NULL) {
            $node_svc0 = node_load($node->field_services['und'][0]['target_id']);
            if (isset($node_svc0) && $node_svc0 <> NULL) {
              if (isset($node_svc0->field_title_short) && $node_svc0->field_title_short <> NULL) {
                $titleshort_svc0 = $node_svc0->field_title_short['und'][0]['safe_value'];
              } else {
                $titleshort_svc0 = $node_svc0->title;
              }
              $replacements[$original] = $titleshort_svc0;
              watchdog('mymodule', 'After svc0, replorig equals :replorig (type :replorig_type)', array(':replorig' => $replacements[$original], ':replorig_type' => gettype($replacements[$original])));
              if (sizeof($node->field_services['und']) > 1) {
                for ( $i=1; $i<sizeof($node->field_services['und']); $i++ ) {
                  $node_svc1on = node_load($node->field_services['und'][$i]['target_id']);
                  if (isset($node_svc1on) && $node_svc1on <> NULL) {
                    if (isset($node_svc1on->field_title_short) && $node_svc1on->field_title_short <> NULL) {
                      $titleshort_svc1on = $node_svc1on->field_title_short['und'][0]['safe_value'];
                    } else {
                      $titleshort_svc1on = $node_svc1on->title;
                    }
                    $replacements[$original] .= ', ' . $titleshort_svc1on;
                    watchdog('mymodule', 'titleshort_svc1on :i equals :titleshort (type :titleshort_type)', array(':i' => $i, ':titleshort' => $titleshort_svc1on, ':titleshort_type' => gettype($titleshort_svc1on)));
                    watchdog('mymodule', 'After svc1on :i, replorig equals :replorig (type :replorig_type)', array(':i' => $i, ':replorig' => $replacements[$original], ':replorig_type' => gettype($replacements[$original])));
                  }
                }
                break;
              } else {
                break;
              }
            }
          }
    	}
    }
    
    // Chained token relationships.
    // http://cgit.drupalcode.org/examples/tree/token_example/token_example.tokens.inc?h=7.x-1.x
    /*if ($format_tokens = token_find_with_prefix($tokens, 'body-format')) {
      if ($items = field_get_items('node', $node, 'body')) {
        $body_format = filter_format_load($items[0]['format']);
        $replacements += token_generate('format', $format_tokens, array('format' => $body_format), $options);
      }
    }*/

  }
  return $replacements;
}
