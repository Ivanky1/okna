(function ($) {
    Drupal.behaviors.GameBisaAjax = {
        attach:function (context, settings) {
            window.onload = function() {
                $('.ya-share2__link[title="Facebook"]').hide()
                var nid = parseInt($('#game-bisa-result-form').attr('action').replace(/.*\/(\d+).*/, "$1"));
                $.ajax({
                    url: 'http://project.bis-expert.ru/games/sadovnik/facebook/'+nid,
                    success: function() {
                        $('.ya-share2__link[title="Facebook"]').show()
                    }
                })
            }
        }
    };
})(jQuery);

