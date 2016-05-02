<?php
/**
* @file
* This is the template file for the object page for large image
*
* Available variables:
* - $islandora_object: The Islandora object rendered in this template file
* - $islandora_dublin_core: The DC datastream object
* - $dc_array: The DC datastream object values as a sanitized array. This
* includes label, value and class name.
* - $islandora_object_label: The sanitized object label.
*
* @see template_preprocess_islandora_dublin_core_display()
* @see theme_islandora_dublin_core_display()
*/
?>
<?php
    $brief_metadata_list = array(
        'Author', 'Title', 'Summary', 'Alternate title(s)', 'Physical description', 'Publication info',
    );
    
    $detailed_metadata_list = array(
        'Author', 'Title', 'Summary', 'Alternate title(s)', 'Physical description', 'Publication info', 'Place of publication', 'Notes', 'Contributor(s)', 'Subject(s)',
    );
    $alternate_class = array(
        0 => "style='background:' ",
        1 => '',
    );

if(!empty($marcxml_output['Brief metadata']) && count($marcxml_output['Brief metadata']) > 0){
?>

<fieldset <?php $print ? print('class="islandora "') : print('class="islandora "');?>>
  <legend><span class=""><?php print t('Brief metadata'); ?></span></legend>
  <div class="fieldset-wrapper">
      <table>
          <?php
            foreach($brief_metadata_list as $item){
                if(!empty($marcxml_output['Brief metadata'][$item])){
                    ?>
          <tr>
              <td><?php print($item); ?></td>
              <td>
                <?php 
                    foreach ($marcxml_output['Brief metadata'][$item] as $entry){
                        print((string)$entry);
                    }
                    
                ?>
              </td>
          </tr>
                    <?php
                }
            }
          ?>          
      </table>
  </div>
</fieldset>

<?php
}

if(!empty($marcxml_output['Detailed metadata']) && count($marcxml_output['Detailed metadata']) > 0){
?>

<fieldset <?php $print ? print('class="islandora islandora-metadata"') : print('class="islandora islandora-metadata"');?>>
  <legend><span class="fieldset-legend"><?php print t('Detailed metadata'); ?></span></legend>
  <div class="fieldset-wrapper">
      <table>
          <?php
            foreach($detailed_metadata_list as $item){
                if(!empty($marcxml_output['Detailed metadata'][$item])){
                    ?>
          <tr>
              <td><?php print($item); ?></td>
              <td>
                <?php 
                    foreach ($marcxml_output['Detailed metadata'][$item] as $entry){
                        print((string)$entry);
                    }
                    
                ?>
              </td>
          </tr>
                    <?php
                }
            }
          ?>          
      </table>
  </div>
</fieldset>

<?php
}

if(!empty($marcxml_output['Catalog record, MARC']) && count($marcxml_output['Catalog record, MARC']) > 0){
?>

<fieldset <?php $print ? print('class="islandora islandora-metadata"') : print('class="islandora islandora-metadata"');?>>
  <legend><span class="fieldset-legend"><?php print t('Catalog record, MARC'); ?></span></legend>
  <div class="fieldset-wrapper">
      <table>
          <?php
            foreach($marcxml_output['Catalog record, MARC'] as $record){
                if(!empty($record)){
                    ?>
          <tr>
              <td><?php print($record); ?></td>
          </tr>
                    <?php
                }
            }
          ?>          
      </table>
  </div>
</fieldset>

<?php
}
?>
