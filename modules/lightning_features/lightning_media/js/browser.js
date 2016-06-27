/**
 * @file
 * Behaviors for the Entity Browser-based Media Library.
 */

(function ($, Drupal) {
  "use strict";

  Drupal.behaviors.entityBrowserSelection = {

    attach: function (context) {
      var $all = $('[data-selectable]', context);

      $all.on('click', function () {
        var $input = $('input[name^="entity_browser_select"]', this);

        $('input[name ^= "entity_browser_select"]', this).prop('checked', true);
        $(this).addClass('selected');

        if ($input.is('[type = "radio"]')) {
          $all.not(this).removeClass('selected');
        }
      });
    }

  };

})(jQuery, Drupal);
