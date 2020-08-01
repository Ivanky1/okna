<?php
/**
 * @param $nid
 */
function facebook_bisa_update($nid) {
    $furl = 'https://graph.facebook.com';
    $ch = curl_init();
    curl_setopt( $ch, CURLOPT_URL, $furl );
    curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
    curl_setopt( $ch, CURLOPT_POST, true );
    $params = array(
        'id' => url('http://project.bis-expert.ru/games/sadovnik/result/'.$nid, array('absolute' => TRUE)),
        'scrape' => true );
    $data = http_build_query( $params );
    curl_setopt( $ch, CURLOPT_POSTFIELDS, $data );
    curl_exec( $ch );
    $httpCode = curl_getinfo( $ch, CURLINFO_HTTP_CODE );
}

function game_bisa_result_form($form, &$form_state, $nid) {

    if (isset($_SESSION['table_result'])) {
        setcookie('table_result', $_SESSION['table_result']);
    }
    $response = node_load($nid);
    if ($response) {
        $response_all = old_response_percent_return($nid, null);
        $present_cnt = 0;
        if ($response_all) {
            foreach($response_all as $r) {
                if ($r->field_present_result_value == $response->field_present_result[LANGUAGE_NONE][0]['value']) {
                    $present_cnt++;
                }
            }
        }
        $presents = ($present_cnt) ?round(($present_cnt*100)/count($response_all)) : 0;
        $form['description']  = array(
            '#type' => 'item',
            '#markup' => result_text($response->field_present_result[LANGUAGE_NONE][0]['value'], count(questions_return()), $presents),
        );

            $form['pod'] = array(
                '#type' => 'item',
                '#markup' => 'Вы можете поделиться этим результатом с друзьями:
                    <script type="text/javascript" src="//yastatic.net/es5-shims/0.0.2/es5-shims.min.js" charset="utf-8"></script>
    <script type="text/javascript" src="//yastatic.net/share2/share.js" charset="utf-8"></script>
    <div class="ya-share2" data-services="vkontakte,facebook,gplus,twitter"></div>
                    ',
            );
        if ( (isset($_SESSION['table_result']) && $_SESSION['table_result'] == $nid) ||
             (isset($_COOKIE['table_result']) && $_COOKIE['table_result'] == $nid)
        ) {
            $form['table_result'] = array(
                '#type' => 'fieldset',
                '#title' => 'Укажите ваши данные для таблицы рекордов:',
                '#collapsible' => false,
                '#collapsed' => FALSE,
            );
            $form['table_result']['fio'] = array(
                '#type' => 'textfield',
                '#title' => 'Ваше имя (можно с фамилией, можно ненастоящие)',
                '#required' => true,
            );
            $form['table_result']['post'] = array(
                '#type' => 'textfield',
                '#title' => 'Ваша должность (всем будет интересно)',
            );
            $form_state['res_nid'] = $response->nid;
            $form['table']['submit'] = array(
                '#type' => 'submit',
                '#value' => 'Сохранить результат'
            );

        }
        if (isset($response->field_name_response[LANGUAGE_NONE])) {
            $form['fio']  = array(
                '#type' => 'item',
                '#markup' => 'Игру проходил(а) '.$response->field_name_response[LANGUAGE_NONE][0]['value']
                    .(isset($response->field_post_response[LANGUAGE_NONE]) ?', '.$response->field_post_response[LANGUAGE_NONE][0]['value'] : ""),
            );
        }

        if (isset($_SESSION['table_result'])) {
            unset($_SESSION['table_result']);
        }

        return $form;
    }
}

function game_bisa_result_form_validate($form, &$form_state) {
    if (isset($form_state['values']['fio'])) {
        $form_state['values']['fio'] = trim(addslashes(strip_tags($form_state['values']['fio'])));
    }
    if (isset($form_state['values']['post'])) {
        $form_state['values']['post'] = trim(addslashes(strip_tags($form_state['values']['post'])));
    }
}
/**
 * @param $form
 * @param $form_state
 */
function game_bisa_result_form_submit($form, &$form_state) {
    setcookie('table_result', '');
    $res = node_load($form_state['res_nid']);
    $res->field_name_response[LANGUAGE_NONE][0]['value'] = $form_state['values']['fio'];
    if (isset($form_state['values']['post'])) {
        $res->field_post_response[LANGUAGE_NONE][0]['value'] = $form_state['values']['post'];
    }
    node_save($res);
    drupal_set_message('Ваш результат сохранен в таблицу результатов');
}

/**
 * @param $cnt
 * @param $all
 * @param $present
 * @return string
 */
function result_text($cnt, $all, $present) {
    $atom = 'всего';
    $text_dop = '';
    $path = drupal_get_path('module', 'game_bisa');
    if ($cnt >8) {
        $result = 'Идеально';
        $title = 'Поздравляем, вы идеальный садовник!';
        $atom = 'лишь';
        $text_dop = '<br />Мы даже подозреваем, что вас зовут Михаил Юрьевич. Нет? Ну нет так нет ;).';
        $ims_src = "/{$path}/img/medal_idial.png";
    } elseif($cnt > 6) {
        $result = 'Отличный результат';
        $title = 'Поздравляем, вы отличный садовник!';
        $ims_src = "/{$path}/img/medal_best.png";
    } elseif ($cnt > 4) {
        $result = 'Нормальный результат';
        $title = 'Ну.. Мы видели лучше. Правда, и хуже тоже.';
        $ims_src = "/{$path}/img/medal_not_bed.png";
    } elseif ($cnt > 2) {
        $result = 'Плохой результат';
        $title = 'Вам еще учиться и учиться. Вы плохой садовник.';
        $ims_src = "/{$path}/img/medal_bed.png";
    } elseif ($cnt <= 2) {
        $result = 'Ужасный результат';
        $title = 'Вы ужасный, просто ужасный садовник! Вас нельзя подпускать к цветам.. то есть к подсудимым.';
        $ims_src = "/{$path}/img/medal_worst.png";
    }
    $text = "<h2 class='result'>{$result}<br/>{$title}</h2>

                <p class='number_response'><strong>Правильных ответов $cnt из $all!</strong></p>

                <p class='present_people'>Такого результата добились {$atom} {$present}% участников. {$text_dop} </p> <img src='http://{$_SERVER['HTTP_HOST']}$ims_src' />";

    $meta_image = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
            'property' => 'og:image',
            'content' => 'http://'.$_SERVER['HTTP_HOST'].$ims_src
        )
    );
    drupal_add_html_head( $meta_image, 'meta_image' );

    return $text;
}