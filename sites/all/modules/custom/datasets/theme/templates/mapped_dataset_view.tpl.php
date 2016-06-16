<?php 
$data = $variables['data']; 
//echo "<pre>"; print_r($data);echo "</pre>";
?>
<h4>Organism: <?php print $data[0]->organism; ?><br></h4>
<b>Data provider</b><br>
Name: <?php print $data[0]->name; ?><br>
Email: <?php print $data[0]->email; ?><br>
Affiliation: <?php print $data[0]->affiliation; ?><br>

<b>Data source Information</b><br>
<?php if(!empty($data[0]->geo_location)) { ?>
Geo location: <?php print $data[0]->geo_location; ?><br>
<?php } ?>

<?php if(!empty($data[0]->tissues_located)) { ?>
Tissues/Life stage included: <?php print $data[0]->tissues_located; ?><br>
<?php } ?>

<?php if(!empty($data[0]->gender)) { ?>
Sex: <?php print $data[0]->gender ?><br>
<?php } ?>

<?php if(!empty($data[0]->gender) && ($data[0]->gender == 'NA') ) { ?>
Other: <?php print $data[0]->other_gender; ?> <br>
<?php } ?>

<?php if(!empty($data[0]->sequence_platform)) { ?>
Sequencing platform and version (Illumina Hi-Seq 200 bp): <?php print $data[0]->sequence_platform; ?><br>
<?php } ?>

Is the data published?: <?php print $data[0]->is_publish; ?><br>

<?php if($data[0]->is_publish == 'Yes') { ?>
Reason: <?php print $data[0]->publish_field_data; ?> <br>
<?php } ?>

<b>Analysis Method</b><br>
Descriptive Track: <?php print $data[0]->descriptive_track; ?><br>
<?php if(!empty($data[0]->data_source_url)) { ?>
Data source URL: <?php print $data[0]->data_source_url; ?><br>
<?php } ?>

Program: <?php print $data[0]->program; ?><br>
Version: <?php print $data[0]->version; ?><br>

<?php if(!empty($data[0]->additional_info)) { ?>
Addition Information: <?php print $data[0]->additional_info; ?><br>
<?php } ?>

Other Methods: <?php print rtrim($data[0]->other_methods,','); ?><br>

<b>File Information</b><br>
<?php   
  $file = explode(',', $data[0]->filename);
  $md5 = explode(',', $data[0]->md5sum);
  $file_md5sum = '';
  foreach($file as $key => $name) {
    if(!empty($name))  
	$file_md5sum .= "File name: ".$name;
    if(!empty($md5[$key]))
       $file_md5sum .= "<br>md5sum: ".$md5[$key]."<br><br>";  
  }
?>
<?php print $file_md5sum; ?>



