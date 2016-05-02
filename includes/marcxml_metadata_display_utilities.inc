<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function marcxml_metadata_to_array($marcxml){
    $marcxml_metadata_display_item_index_list = array(
        'Brief metadata' => array(
            'Author' => '100',
            'Title' =>  '245',
            'Summary'   => '520',
            'Alternate title(s)' => '130,240,246 3_,740,246 18',
            'Physical description' => '300',
            'Publication info' => '260',
        ),

        'Detailed metadata' => array(
            'Author' => '100',
            'Title' => '245',
            'Summary' => '520',
            'Alternate title(s)' => '130,240,246 3_,740,246 18',
            'Physical description' => '300',
            'Publication info' => '260',
            'Place of publication' => '260 |a',
            'Notes' => '500',
            'Contributor(s)' => '700',
            'Subject(s)' => '650',
        ),
       // 'index_array' => '008,010 __|a,035 __|a,040 __|a|b|e|c|d,050 00|a|b,099 __|a,100 00|a,100 1_|a|d,100 10|a,d,245 10|a|h|c,246 30|a,246 3_|a,246 18|a,260 __|a|b|c,260 0_|a|b|c,300 __|a|b|c,500 __|a|5,520 __|a,590 __|a,650 _0|a|x,700 10|a|d|w,710 20|a|5,740 01|a,948 __|a|b|c,994 __|a|b,999 __|a|w|c|i|l|m|r|s|t|u|x|o',
    );
    
    $output = array();
    $xmlDoc = new DOMDocument();
    $xmlDoc->loadXML($marcxml);
    $ind1 = "";
    $ind2 = "";
    $x = $xmlDoc->documentElement;
    foreach($x->childNodes as $item){
        if($item->nodeType == "3"){
            continue;
        }
        $node_name = $item->nodeName;
        $node_value = $item->nodeValue;
        $children = $item->childNodes;
        $tag = $item->getAttribute("tag");
        $ind1 = empty($item->getAttribute("ind1")) ? "_" : $item->getAttribute("ind1");
        $ind2 = empty($item->getAttribute("ind2")) ? "_" : $item->getAttribute("ind2");
        $ind12 = $ind1.$ind2;
        
        if(!empty($tag)){
            if(empty($children)){
                if(empty($node_value)){
                    continue;
                }
                else{
                    if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Brief metadata'])){
                        $output['Brief metadata'][$entry] = $node_value . "<br>";
                    }
                    if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Detailed metadata'])){
                        $output['Detailed metadata'][$entry] = $node_value . "<br>";
                    }
                }
                $output['Catalog record, MARC'][] = $tage . "  " . $node_value . "<br>";
            }
            else{         
                $entry_value = "";
                $entry_marcxml_value = "";
                switch($tag){
                    case "100":
                    case "245":
                    case "520":
                    case "130":
                    case "240":
                    case "740":
                    case "500":
                    case "700":                        
                        foreach ($children as $child){
                            if($code = $child->getAttribute("code")){
                                $child_node_value = $child->nodeValue;
                                $entry_value .= $child_node_value . ",";
                                $entry_marcxml_value .= " |" . $code . "  " . $child_node_value; 
                            }
                            else{
                                continue;
                            }
                        }
                        $entry_value = rtrim($entry_value, ",");
                        $entry_marcxml_value = $tag . "  " . $ind12 . $entry_marcxml_value;
                        
                        if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Brief metadata'])){
                            $output['Brief metadata'][$entry][] = $entry_value . "<br>";
                        }
                        if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Detailed metadata'])){
                            $output['Detailed metadata'][$entry][] = $entry_value . "<br>";
                        }
                        $output['Catalog record, MARC'][] = $entry_marcxml_value;
                        break;
                    case "300":
                        // separated by ;
                        foreach ($children as $child){
                            if($code = $child->getAttribute("code")){
                                $child_node_value = $child->nodeValue;
                                $entry_value .= $child_node_value . ";";
                                $entry_marcxml_value .= " |" . $code . "  " . $child_node_value; 
                            }
                            else{
                                continue;
                            }
                        }
                        $entry_value = rtrim($entry_value, ";");
                        $entry_marcxml_value = $tag . "  " . $ind12 . $entry_marcxml_value;
                        
                        if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Brief metadata'])){
                            $output['Brief metadata'][$entry][] = $entry_value . "<br>";
                        }
                        if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Detailed metadata'])){
                            $output['Detailed metadata'][$entry][] = $entry_value . "<br>";
                        }
                        $output['Catalog record, MARC'][] = $entry_marcxml_value;
                        break;
                    case "260":
                        // pub info and pub place two entries
                        foreach ($children as $child){
                            if($code = $child->getAttribute("code")){
                                $child_node_value = $child->nodeValue;
                                $entry_value .= $child_node_value . ";";
                                $entry_marcxml_value .= " |" . $code . "  " . $child_node_value; 
                                if(!empty($child_node_value) && $ind12 === "__" && $code === "a"){
                                    $output['Detailed metadata']['Place of publication'][] = $child_node_value . "<br>";
                                }
                            }
                            else{
                                continue;
                            }
                        }
                        $entry_value = rtrim($entry_value, ";");
                        $entry_marcxml_value = $tag . "  " . $ind12 . $entry_marcxml_value;
                        
                        if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Brief metadata'])){
                            $output['Brief metadata'][$entry][] = $entry_value . "<br>";
                        }
                        if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Detailed metadata'])){
                            $output['Detailed metadata'][$entry][] = $entry_value . "<br>";
                        }
                        $output['Catalog record, MARC'][] = $entry_marcxml_value;
                        break;
                    case "650":
                        // use -- to separate a and other entries; the LCSH prefix;
                        foreach ($children as $child){
                            $child_node_value = $child->nodeValue;
                            if($code = $child->getAttribute("code")){
                                if($code === "a"){
                                    $entry_value .= "LCSH: " . $child_node_value . " -- ";
                                }
                                else{
                                    $entry_value .= $child_node_value . ",";
                                }
                                $entry_marcxml_value .= " |" . $code . "  " . $child_node_value; 
                            }
                            else{
                                continue;
                            }
                        }
                        $entry_value = rtrim($entry_value, ",");
                        $entry_marcxml_value = $tag . "  " . $ind12 . $entry_marcxml_value;
                        
                        if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Brief metadata'])){
                            $output['Brief metadata'][$entry][] = $entry_value . "<br>";
                        }
                        if($entry = array_search($tag, $marcxml_metadata_display_item_index_list['Detailed metadata'])){
                            $output['Detailed metadata'][$entry][] = $entry_value . "<br>";
                        }
                        $output['Catalog record, MARC'][] = $entry_marcxml_value;
                        break;
                    default:
                        break;
                }
            }
        }
        else{
            continue;
        }
        
//        if(!empty($tag)){
//            switch($tag){
//                case "100":
//                    $output['Author'][] = $node_value;
//                    $output['Detailed metadata']['Author'][] = $node_value;
//                    break;
//                case "245":
//                    $output['Title'][] = $node_value;
//                    $output['Detailed metadata']['Title'][] = $node_value;
//                    break;
//                case "520":
//                    $output['Summary'][] = $node_value;
//                    $output['Detailed metadata']['Summary'][] = $node_value;
//                    break;
//                case "130":
//                case "240":
//                case "246":
//                case "740":
//                case "246":
//                    if($node_name == "246" && ($ind12 != "3_" && $ind12 != "18")){
//                        break;
//                    }
//                    $output['Alternate title(s)'][] = $node_value;
//                    $output['Detailed metadata']['Alternate title(s)'][] = $node_value;
//                    break;
//                case "300":
//                    $output['Physical description'][] = $node_value;
//                    $output['Detailed metadata']['Physical description'][] = $node_value;
//                    break;
//                case "260":
//                    $output['Publication info'][] = $node_value;
//                    $output['Detailed metadata']['Publication info'][] = $node_value;
//                    break;
//                case "500":
//                    $output['Notes'][] = $node_value;
//                    $output['Detailed metadata']['Notes'][] = $node_value;
//                    break;
//                case "700":
//                    $output['Contributor(s)'][] = $node_value;
//                    $output['Detailed metadata']['Contributor(s)'][] = $node_value;
//                    break;
//                case "650":
//                    $output['Subject(s)'][] = $node_value;
//                    $output['Detailed metadata']['SummSubject(s)ary'][] = $node_value;
//                    break;
//                default:
//                    break;
//            }
//        }
//        $item_children = $item->childNodes;
//        if(!empty($item_children) && count($item_children) > 0){
//            foreach($item_children as $subfield){
//                if($item->nodeType == "3"){
//                    continue;
//                }
//                //print($subfield->nodeName . " = " .$subfield->nodeValue . "\n");
//                $output["marcxml"][$tag][$ind12] = $node_value;
//            }
//        }
//        else{
//            $output["marcxml"][$tag][$ind12] = $node_value;
//        }
//        //$output["marcxml"][$tag][$ind12]
    }
    return $output;
}

function getMarcxmlString(){    
    module_load_include("inc", "islandora_marcxml", "includes/utilities");
    module_load_include('inc', 'islandora_internet_archive_bookreader_custom', 'includes/utilities');
    
    $pid = get_pid_by_url();
    if(!empty($pid)){
        $object = islandora_object_load($pid);
        if(!empty($object)){
            return islandora_marcxml_transform_mods_to_marcxml($object);
        }
    }
    else{
        throw new Exception("Cannot get pid from url!");
    }    
}
