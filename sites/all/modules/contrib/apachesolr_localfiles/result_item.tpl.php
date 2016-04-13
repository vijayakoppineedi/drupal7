<?php 
//echo "<pre>"; print_r($vars);echo "</pre>";
?>
<div class="title">
  <a href="<?php print $vars['filepath'] ?>" target="_blank"><?php print $vars['filename'] ?></a>
  (<?php print t('File size') . ': ' . $vars['size'] ?>)
</div>
<?php if ($vars['snippet'] != ' ...') : ?>
  <div class="snippet">
    <?php print $vars['snippet'] ?>
  </div>
<?php endif ?>
<div class="filepath">
  <?php print $vars['filepath'] ?>
</div>
<div class="changed">
  <?php print t('Last modification: ') . $vars['changed'] ?>
</div>