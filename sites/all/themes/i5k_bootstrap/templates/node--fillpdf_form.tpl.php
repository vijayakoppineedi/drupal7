<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the page--fillpdf_form.tpl.php template in this directory.
 */
?>

<h1>Image Permissions for i5k Workspace</h1>

<h3>Please download the pdf file, sign it, and return to i5k@ars.usda.gov.
<?php
//echo "<pre>"; print_r($node);echo "</pre>";
print  "<a href='/fillpdf?fid=183&nids[]=".$node->nid."'>Download</a>"; ?>
</h3>


