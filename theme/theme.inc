<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Implements hook_preprocess().
 */
function islandora_marcxml_metadata_display_preprocess_islandora_dublin_core_display(&$variables){
    module_load_include('inc','islandora_internet_archive_bookreader_custom', 'includes/marcxml_metadata_display_utilities');
    
    $path = drupal_get_path('module', 'islandora_marcxml_metadata_display');
    
    $marcxml = getMarcxmlString();
    $marcxml_output = marcxml_metadata_to_array($marcxml);
    
    $variables['marcxml_output'] = isset($marcxml_output) ? $marcxml_output : array();

    drupal_add_css($path.'/css/marcxml_display.css');
    //print_r($output);
    //drupal_add_js($data, $options);
}