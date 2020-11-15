<?php

$items = [];

foreach ($node->field_img_photogallery[LANGUAGE_NONE] as $item) {
    $img_url_absolute = file_create_url($item['uri']);

    global $base_url;
    $img_url_relative = str_replace($base_url .'/', '', $img_url_absolute);

    $hero_image = array(
        'style_name' => 'medium',
        'path' => $item['uri'],
    );
    $img = theme('image_style',$hero_image);
    $img = str_replace($base_url, '', $img);

    $items[] = [
        'class' => ['photo-item'],
        'data' => l($img, $img_url_relative,
            [
                'html' => true,
                'attributes' => [
                    'class' => ['item']
                ]
            ]
        )
    ];
}

$attributes = array(
    'class' => 'windows-photo-gallery',
);

echo theme_item_list(array('items' => $items,  'type' => 'ul', 'title' => '', 'attributes' => $attributes));