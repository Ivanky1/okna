(function ($) {
    Drupal.behaviors.PhotoGallery = {
        attach: function (context, settings) {

            $(".windows-photo-gallery").lightGallery({
                selector: ".item",
            });

        }
    }

})(jQuery);