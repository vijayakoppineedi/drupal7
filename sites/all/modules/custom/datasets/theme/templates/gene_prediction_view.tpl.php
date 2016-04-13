<?php 
$data = $variables['data']; 
//echo "<pre>"; print_r($data);echo "</pre>";
?>
<h4>Organism: <?php print $data[0]->organism; ?><br></h4>
<b>Analysis Method</b><br>
Program: <?php print $data[0]->program; ?><br>
Version: <?php print $data[0]->version; ?><br>

<?php if(!empty($data[0]->additional_info)) { ?>
Addition Information: <?php print $data[0]->additional_info; ?><br>
<?php } ?>

Other Methods: <?php print $data[0]->other_methods; ?><br>
<b>Analysis Provider</b><br>
Name: <?php print $data[0]->name; ?><br>
Email: <?php print $data[0]->email; ?><br>
Affiliation: <?php print $data[0]->affiliation; ?><br>

<b>Gene set information</b><br>
Name: <?php print $data[0]->gene_name; ?>  <br>
Version: <?php print $data[0]->gene_version; ?><br>
Descriptive Track: <?php print $data[0]->descriptive_track; ?><br>
Is this an OGS?: <?php print $data[0]->is_ogs; ?><br>

<?php if($data[0]->is_ogs == 'Yes') { ?>
Reason: <?php print $data[0]->reason; ?> <br>
<?php } ?>

<b>File Information</b><br>
<?php   
  $file = explode(',', $data[0]->filename);
  $md5 = explode(',', $data[0]->md5sum);
  $file_md5sum = '';
  foreach($file as $key => $name) {
	$file_md5sum .= "File name: ".$name."<br>md5sum: ".$md5[$key]."<br><br>";  
  }
?>
<?php print $file_md5sum; ?>


