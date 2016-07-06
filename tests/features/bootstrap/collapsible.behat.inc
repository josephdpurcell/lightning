<?php

use Behat\Mink\Exception\ElementNotFoundException;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;

/**
 * Contains steps for working with collapsible elements.
 */
class CollapsibleSubContext extends DrupalSubContextBase implements DrupalSubContextInterface {

  /**
   * Expands a collapsible element.
   *
   * @param string $label
   *   The label of the collapsible.
   *
   * @When I open the :label collapsible
   */
  public function openCollapsible($label) {
    $this->assertCollapsible($label)->find('css', 'summary')->click();
  }

  /**
   * Asserts that a collapsible element exists by label.
   *
   * @param string $label
   *   The label of the collapsible.
   *
   * @return \Behat\Mink\Element\ElementInterface
   *   The collapsible element.
   *
   * @throws ElementNotFoundException
   *   If the collapsible was not found.
   * 
   * @Then I should see a :label collapsible
   */
  public function assertCollapsible($label) {
    $session = $this->getSession();

    // We'll need to normalize case, since it appears as though elements'
    // getText() methods may be affected by styling directives in JS-aware
    // test cases.
    $label = strtolower($label);

    $elements = $session->getPage()->findAll('css', 'details');
    /** @var \Behat\Mink\Element\ElementInterface $element */
    foreach ($elements as $element) {
      $summary = $element->find('css', 'summary');
      if ($summary && strtolower($summary->getText()) == $label) {
        return $element;
      }
    }

    throw new ElementNotFoundException($session->getDriver(), 'collapsible', 'css', 'details');
  }

}
