(function ($) {
    Drupal.behaviors.GameBisa = {
        attach:function (context, settings) {
            var imgUrl1 = '/sites/all/themes/my_theme/images/btn1_activ.png';
            var imgUrl2 = '/sites/all/themes/my_theme/images/btn2_activ.png';
            var imgUrl1_dis = '/sites/all/themes/my_theme/images/btn1_dis.png';
            var imgUrl2_dis = '/sites/all/themes/my_theme/images/btn2_dis.png';

            var imgUrl1_hover = '/sites/all/themes/my_theme/images/btn1_hover.png';
            var imgUrl2_hover = '/sites/all/themes/my_theme/images/btn2_hover.png';

            if ($('#game-bisa-form .yes').length) {
                $('#game-bisa-form .form-submit').hide();
                $('#game-bisa-form .cusom_uveren').hide();
            }

            if ($('.page-games-sadovnik').length) {
                window.scrollTo(0, 120)
            }
            $('.colorbox-inline').on('click', function() {
                window.scrollTo(0, 120)
            })

            $('#game-bisa-form .yes, #game-bisa-form .noo').on('click', function(e){
                e.preventDefault();
                var img = ($(this).hasClass('yes')) ?imgUrl1 : imgUrl2;
                var img_hover = ($(this).hasClass('yes')) ?imgUrl2_dis : imgUrl1_dis;
                if (!$(this).hasClass('active')) {
                    $(this).addClass('active');
                    $(this).css({'background-image' : 'url('+img+')', cursor : 'default'});
                    ($(this).hasClass('yes')) ? $('input[value="Да"]').click()
                                              : $('input[value="Нет"]').click();
                    $('#game-bisa-form').submit();
                    /*
                    if ($('#game-bisa-form .form-submit').is(':hidden')) {
                        $('#game-bisa-form .form-submit').show();
                        $('#game-bisa-form .cusom_uveren').show();
                    } */
                }
                $(this).siblings('a').removeClass('active');
                $(this).siblings('a').css({'background-image' : 'url('+img_hover+')', cursor : 'pointer'});

            })

            $('.form-type-item .yes, .form-type-item .noo').hover(
                function(){
                    var img_hover = ($(this).hasClass('yes')) ?imgUrl1_hover : imgUrl2_hover;
                    if (!$(this).hasClass('active')) {
                        $(this).css({'background-image' : 'url('+img_hover+')', cursor : 'pointer'});
                    }
                }, function () {
                    var img_dis = ($(this).hasClass('yes')) ?imgUrl1_dis : imgUrl2_dis;
                    if (!$(this).hasClass('active')) {
                        $(this).css({'background-image' : 'url('+img_dis+')', cursor : 'pointer'});
                    }
                }
            )

            if ($('h2.result_games').length && $("h2.result_games:contains('НЕ УГАДАЛИ')").length) {
                $('h2.result_games').css('color', '#C93C00');
                $('.present_result').css('color', '#C93C00');
            }
            if ($('h2.result').length && ($("h2.result:contains('Ужасный результат')").length || $("h2.result:contains('Плохой результат')").length)) {
                $('h2.result').css('color', '#C93C00');
            }

        }
    };
})(jQuery);

