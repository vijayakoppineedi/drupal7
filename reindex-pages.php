<?php
$db_con = pg_connect("host=localhost dbname=tripal2d7 user=tripal password=tri2pal");

$sql = "select nid from chado.feature f , public.chado_feature cf where f.feature_id=cf.feature_id and f.type_id=289";
$result = pg_query($db_con, $sql);
$i=1;
while ($row = pg_fetch_row($result)) {
  $nid = $row[0];
  $nid_exists = pg_num_rows(pg_query("select count(entity_id) from apachesolr_index_entities_node where entity_id=$nid"));

  $time = time();

  if($nid_exists > 0) {
    $update = pg_query("update apachesolr_index_entities_node set changed=$time where entity_id=$nid");
    echo "update ".$update." <br>";
  } else {   
    $insert = pg_query("INSERT INTO apachesolr_index_entities_node values ('node', $nid, 'chado_feature', 1, $time)");
    echo "insert ".$insert."<br>";
  }
  echo "count ".$i;
  $i = $i+1; 
  echo "<br />\n";
}

echo "Total Count ".$i;


?>
