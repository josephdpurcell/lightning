@media @api
Feature: Image media assets
  A media asset representing a locally hosted image.

  @javascript
  Scenario: Creating an image
    Given I am logged in as a user with the media_creator role
    When I visit "/media/add/image"
    And I attach the file "puppy.jpg" to "Image"
    And I wait for AJAX to finish
    And I enter "Foobaz" for "Media name"
    And I press "Save and publish"
    # Queue the image for deletion now so it will be deleted even if the
    # test fails.
    And I queue the latest media entity for deletion
    Then I should be visiting a media entity
    And I should see "Foobaz"

  @javascript
  Scenario: Uploading an image to be ignored by the media library
    Given I am logged in as a user with the media_creator role
    When I visit "/media/add/image"
    And I attach the file "puppy.jpg" to "Image"
    And I wait for AJAX to finish
    And I enter "Blorg" for "Media name"
    And I uncheck the box "Save to my media library"
    And I press "Save and publish"
    # Queue the image for deletion now so it will be deleted even if the
    # test fails.
    And I queue the latest media entity for deletion
    And I visit "/entity-browser/iframe/media_browser"
    Then I should see "There are no media items to display."

  @javascript
  Scenario: New image fields should use the image browser by default
    Given I am logged in as a user with the administrator role
    When I visit "/admin/structure/types/manage/page/fields"
    And I create a image field called "Foo Image" on the page content type
    And I visit "/admin/structure/types/manage/page/form-display"
    And I click "Manage form display"
    And I press "field_foo_image_settings_edit"
    And I wait for AJAX to finish
    Then the formatter should be "Entity browser (file)"
    And the "Entity browser" field should contain "image_browser"
    And the "File view mode" field should contain "thumbnail"
    And I delete the "Foo Image" field from the page content type
