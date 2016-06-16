<?php 
$data = $variables['data']; 
?>
<h4>Organism: <?php print $data[0]->organism; ?><br></h4>
<b>Genome co-ordinator Information</b><br>
Name: <?php print $data[0]->name; ?><br>
Email: <?php print $data[0]->email; ?><br>
<b>Project Background</b><br>
Organism: <?php print $data[0]->organism; ?><br>
Common name: <?php print $data[0]->common_name; ?><br>
Project description for your organism page: <?php print $data[0]->description; ?><br>
<?php if(!empty($data[0]->organism_image_url)) { ?>
Image for your organism page: <?php print $data[0]->organism_image_url; ?><br>
<?php } ?>

Will you manually curate this assembly using i5k workspace tools?: <?php print $data[0]->is_curate_assembly; ?><br>
<?php if($data[0]->is_curate_assembly == 'Yes') { ?>
is_same: <?php print $is_same = ($data[0]->is_same == 1)?'Yes':'No'; ?><br>
Co-ordinator Name:  <?php print $data[0]->manual_curation_name; ?><br>
Co-ordinator Email: <?php print $data[0]->manual_curation_email; ?><br>
Do you need assistance developing an OGS?: <?php print $data[0]->need_assistance; ?><br>

<?php if(!empty($data[0]->reason)) { ?>
Reason: <?php print $data[0]->reason; ?><br>
<?php } ?>

Start date: <?php print date('M d Y', $data[0]->time_from); ?><br>
End date: <?php print date('M d Y', $data[0]->time_to); ?><br>
<?php } ?>

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

<?php if(!empty($data[0]->data_source_strain)) { ?>
Strain: <?php print $data[0]->data_source_strain; ?><br>
<?php } ?>

<?php if(!empty($data[0]->data_source_notes)) { ?>
Other notes: <?php print $data[0]->data_source_notes; ?><br>
<?php } ?>

<?php if(!empty($data[0]->data_source_seqplatform)) { ?>
Sequencing platform and version (Illumina Hi-Seq 200 bp): <?php print $data[0]->data_source_seqplatform; ?><br>
<?php } ?>

<?php if(!empty($data[0]->data_source_url)) { ?>
Data source URL: <?php print $data[0]->data_source_url; ?><br>
<?php } ?>

<b>Assembly Information</b><br>
Name: <?php print $data[0]->assembly_name; ?>  <br>
Version: <?php print $data[0]->assembly_version; ?><br>
NCBI/INSDC Genome Assembly accession #: <?php print $data[0]->assembly_accession; ?><br>
Analysis method: <?php print $data[0]->assembly_method; ?><br>
Is the assembly published?: <?php print $data[0]->is_publish; ?><br>

<?php if($data[0]->is_publish == 'Yes') { ?>
Reason: <?php print $data[0]->publish_field_data; ?> <br>
<?php } ?>

<?php if(!empty($data[0]->other_notes)) { ?>
Other notes: <?php print $data[0]->other_notes; ?><br>
<?php } ?>


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


