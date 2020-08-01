<?php
/**
 * @return string
 */
function game_bisa_table() {
    $q = db_select('node', 'n')->extend('PagerDefault')->limit(50);
    $q->innerJoin('field_data_field_response_return', 'response', 'response.entity_id = n.nid');
    $q->innerJoin('field_data_field_present_result', 'result', 'result.entity_id = n.nid');
    $q->innerJoin('field_data_field_name_response', 'name', 'name.entity_id = n.nid');
    $q->leftJoin('field_data_field_post_response', 'post', 'post.entity_id = n.nid');
    $q->condition('n.type', 'result_response');
    $q->addField('name', 'field_name_response_value', 'name');
    $q->addField('post', 'field_post_response_value', 'post');
    $q->addField('result', 'field_present_result_value', 'present');
    $q->addField('n', 'created', 'created');
    $q->addField('n', 'nid', 'nid');
    $q->orderBy("result.field_present_result_value", 'DESC');
    $q->orderBy("n.created", 'DESC');
    $res = $q->execute()->fetchAll();
    $header = array('Имя игрока', 'Должность', 'Количество правильных ответов', 'Дата');
    $rows = $ars = array();
    foreach($res as $r) {
        $ars[date('d-m-Y', $r->created)][$r->nid] = $r->present;
        $rows[] = array($r->name, ($r->post)?$r->post :'', $r->present, date('d-m-Y', $r->created));
    }
    /*
    $rows_return = array();
    foreach($ars as $toDate) {
        arsort($toDate);
        foreach($toDate as $k=>$v) {
            $rows_return[] = $rows[$k];
        }
    }*/

    $q1 = db_select('node', 'n');
    $q1->condition('n.type', 'result_response');
    $q1->addExpression('count(*)');
    $cnt_all = $q1->execute()->fetchField();

    $q2 = db_select('node', 'n');
    $q2->condition('n.type', 'result_response');
    $q2->fields('n', array('created'));
    $q2->where("FROM_UNIXTIME(created, '%Y%d%m') = :created", array(':created' => date('Ydm')));
    $today = $q2->execute()->rowCount();

    return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'game_result_table'), )).
           theme('pager', array('quantity' => 3)).
           "<br/><p style='text-align:center'>Сыграно сегодня - $today, ".
           "всего - $cnt_all</p>";
}

