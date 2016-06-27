/**
 * @file
 * A behavior that fires the change event on text inputs after a delay.
 */

(function ($, _, Drupal) {
  "use strict";

  Drupal.behaviors.changeOnKeyUp = {

    // The element(s) to affect.
    selector: '.keyup-change',

    // How many milliseconds to wait before firing the change event.
    delay: 600,

    // We want to keep a reference to the debounced event handler so
    // that it can be detached if needed.
    onKeyUp: _.debounce(function () {
      $(this).trigger('change');
    }, this.delay),

    attach: function (context) {
      $(this.selector, context).on('keyup', this.onKeyUp);
    },

    detach: function (context) {
      $(this.selector, context).off('keyup', this.onKeyUp);
    }

  };

})(jQuery, _, Drupal);
