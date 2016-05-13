<?php
$form = $variables['form'];

$output = '';
  if(!empty($form['datasets_table']['fullname']['#value'])) {       
    $output = "<a href='/admin/structure/datasets'>Back to datasets list</a>";
    $output .= '<table>';      
    $output .= '<tr><td>Name</td><td>: '.$form['datasets_table']['fullname']['#value']."</td></tr>";  
    $output .= '<Tr><td>Email</td><td>: '.$form['datasets_table']['email']['#value']."</td></tr>";
    $output .= '<tr><td>Scientific Name</td><td>: '.$form['datasets_table']['genus']['#value']." ".$form['datasets_table']['species']['#value']."</td></tr>";
    $output .= '<tr><td>NCBI TaxId</td><td>: '.$form['datasets_table']['ncbi_taxid']['#value']."</td></tr>"; 
    $output .= '<tr><td>Genome Assembly hosted?</td><td>: '.$form['datasets_table']['genome_assembly_hosted']['#value'].'</td></tr>';   
    $output .= '<tr><td>Has submitted GA to NCBI?</td><td>: '.$form['datasets_table']['is_ncbi_submitted']['#value']."</td></tr>";
    $output .= '<tr><td>Re-assembly or New assembly</td><td>: '.$form['datasets_table']['is_assembly']['#value']."</td></tr>";
    $output .= '<tr><td>Were you involved in the generation of this genome assembly?</td><td>: '.$form['datasets_table']['involved_in_generation']['#value']."</td></tr>";

    $output .= '<tr><td>Describe plans for this Genome Project</td><td>: '.$form['datasets_table']['description']['#value']."</td></tr>";


    $output .= '<tr><td>Status</td><td> '.drupal_render($form['datasets_table']['status']).'</td></tr>';   
    $output .= "</table>";
  } 
  $output .= drupal_render_children($form);
  
  print $output;  
?>


 
 
 
 
