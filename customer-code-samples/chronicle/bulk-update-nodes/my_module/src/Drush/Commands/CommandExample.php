<?php

namespace Drupal\my_module\Drush\Commands;

use Drupal;
use Drupal\node\Entity\Node;
use Drush\Commands\DrushCommands;

class CommandExample extends DrushCommands {

  #[CLI\Command(name: 'my_module:example-action', aliases: ['example'])]
  #[CLI\Option(name: 'dry-run')]
  public function exampleAction($options = ['dry-run' => false]) {
    $this->io()->title('Example command.');

    // Specify the entity type, in this case, node.
    // (If working on a different entity type, you'll need to add/change the "use" statements at the top.)
    $nodeStorage = Drupal::entityTypeManager()->getStorage('node');
    // We're limiting to published entities (status 1), and the "staffing" content type (aka "bundle").
    $ids = $nodeStorage->getQuery()
      ->condition('status', 1)
      ->condition('type', 'staffing')
      ->accessCheck(FALSE)
      ->execute();

    echo "Staffings to be reviewed: " . count($ids) . "\n";

    $count = 0;
    // Limit processing to 1000 nids at once for memory management
    foreach (array_chunk($ids, 1000) as $id_chunk) {
      $nodes = $nodeStorage->loadMultiple($id_chunk);
      foreach ($nodes as $node) {
        // In this example, the existing value of field_use_position is simply being transformed by uppercasing the first character in its string value.
        // https://php.net/manual/en/function.ucfirst.php
        $node->field_user_position = ucfirst($node->field_user_position);
        // I'm not sure if this will work as-is, or if it needs to be defined in this script -- the intent is to only save the nodes with changes if the "dry-run" CLI option is not used.
        if (!$dryRun) {
          $node->save();
          $count++;
        }
      }
    }
    $this->io()->info(dt('Processed @count nodes.', ['@count' => count($ids)]));
  }
}
