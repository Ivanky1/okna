<?php
/**
 * Форма
 */
function select_test_form($form, $form_state) {
    // Враппер для селектов
    $form['terms'] = array(
        '#tree' => TRUE,
        '#prefix' => '<div id="terms">',
        '#suffix' => '</div>',
    );

    // Если сработает AJAX, то в $form_state['values']['terms'] будут выбранные значения селектов
    $terms_values = isset($form_state['values']['terms']) ? $form_state['values']['terms'] : array();
    // Селектов будет генерится на 1 больше чем есть в $form_state['values']['terms']
    $terms_values += array('term' . (count($terms_values) + 1) => 'none');
    // В первом селекте будут выводится термины без родителя
    $parent_tid = 0;

    foreach ($terms_values as $input_name => $tid) {
        // Завершаем цикл если в предыдущем селекте ничего не выбрано
        // или у термина нет дочерних терминов
        if ($parent_tid === 'none' || !($terms = taxonomy_get_tree(1, $parent_tid, 1))) {
            break;
        }

        // Формируем данные для селекта
        $options = array('none' => '<none>');
        foreach ($terms as $term) {
            $options[$term->tid] = $term->name;
        }

        // Создаём сам селект
        $form['terms'][$input_name] = array(
            '#type' => 'select',
            '#options' => $options,
            '#default_value' => $tid,
            '#ajax' => array(
                'callback' => 'select_test_form_ajax_callback',
                'wrapper' => 'terms',
            ),
        );

        $parent_tid = isset($options[$tid]) ? $tid : 'none';
    }

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
    );

    $t = taxonomy_get_tree(1);
    $options = array();
    foreach ($t as $term) {

        if ($term->parents[0] == 0)
            $options[$term->tid] = $term->name;
        else $options[$term->tid][$term->parents[0]] = $term->name;

    }
    print_r($options);
    echo theme('select', array('element' => array('#options' => $options)));

    return $form;
}

/**
 * AJAX callback
 */
function select_test_form_ajax_callback($form, $form_state) {
    return $form['terms'];
}