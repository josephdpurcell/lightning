<?php

use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;

/**
 * Subcontext containing steps for dealing with fields.
 */
class FieldsSubContext extends DrupalSubContextBase implements DrupalSubContextInterface {

  /**
   * The Mink context.
   *
   * @var \Drupal\DrupalExtension\Context\MinkContext
   */
  protected $minkContext;

  /**
   * Pre-scenario hook.
   *
   * @BeforeScenario
   */
  public function gatherContexts() {
    $this->minkContext = $this->getContext('\Drupal\DrupalExtension\Context\MinkContext');
  }

  /**
   * Creates a field on a node type.
   *
   * @param string $field_type
   *   The field type.
   * @param string $label
   *   The field label.
   * @param string $node_type
   *   The node type ID on which to create the field.
   *
   * @When I create a :field_type field called :label on the :node_type content type
   */
  public function createField($field_type, $label, $node_type) {
    $this->minkContext->visit("/admin/structure/types/manage/{$node_type}/fields");

    $this->minkContext->clickLink('Add field');
    $this->minkContext->selectOption('new_storage_type', $field_type);
    $this->minkContext->fillField('label', $label);
    // Let the JavaScript set the machine name of the field automatically.
    sleep(2);
    $this->minkContext->pressButton('Save and continue');

    // Don't set any field settings.
    $this->minkContext->pressButton('Save field settings');

    // Don't set any widget settings, either.
    $this->minkContext->pressButton('Save settings');
  }

  /**
   * Deletes a field from a content type.
   *
   * @param string $label
   *   The label of the field to delete.
   * @param string $node_type
   *   The content type from which to delete the field.
   *
   * @When I delete the :label field from the :node_type content type
   */
  public function deleteField($label, $node_type) {
    $this->minkContext->visit("/admin/structure/types/manage/{$node_type}/fields");

    $fields = $this->getSession()->getPage()->findAll('css', '#field-overview tbody tr');
    /** @var \Behat\Mink\Element\ElementInterface $field */
    foreach ($fields as $field) {
      if ($field->find('css', 'td')->getText() == $label) {
        // Find the drop button, open it, and click its Delete link.
        $drop_button = $field->find('css', 'ul.dropbutton');
        $drop_button->find('css', 'li.dropbutton-toggle')->click();
        $drop_button->find('css', 'li.delete a')->click();

        $this->minkContext->pressButton('Delete');
        break;
      }
    }
  }

}
