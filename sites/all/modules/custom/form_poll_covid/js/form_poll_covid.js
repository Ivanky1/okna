(function ($) {
    Drupal.behaviors.PollCovid = {
        attach:function (context, settings) {
            var func = function() {

                $.colorbox({
                    html:
                        '<div class="parent-popup">' +
                        '<div class="popup-img">' +
                        '<img src="/sites/all/modules/custom/block/form_poll_covid/js/popup_covid.png">' +
                        '<a class="covid" href="/research-2020"></a>' +
                        '<a class="close"></a>' +
                        '</div>' +
                        '</div>'
                });

                $('.popup-img .close').on('click', function () {
                    $('#cboxClose').click()
                })

                $('#cboxClose').on('click', function () {
                    var date = new Date(Date.now() + 86400e3);
                    date = date.toUTCString();
                    document.cookie = "popup=disable; expires=" + date;
                })

            }

            $('body', context).once('colorbox-popup-active', function () {

                if (document.cookie.indexOf('popup=disable') == -1) {
                    interval = setTimeout(func, 20000);
                }
            })


        }
    }
}) (jQuery);

