<?php

$pathfile = "/usr/local/drupal7/organism_pass_text.txt";
$text1 = file_get_contents($pathfile);
$text2 = file_get_contents($pathfile);

$lines1  = explode( "\n", $text1);
$lines2  = explode( "\n", $text2);

$data = Array(); $j = 0;

//echo "<pre>"; print_r($lines1);echo "</pre>";
$count = count($lines1);  // 527 lines

$k = 0; $data = array(); $p = 0; $value_exists = array();
foreach( $lines1 as $line1 ) {
  $first = preg_split('/[\t]/', $line1); //explode('\t', $line1); 

  $name1 = trim($first[0]);  
  $i = 0; 
  
  //echo "<pre>"; print_r($value_exists);echo "</pre>";
  //if(!in_array($name1, $value_exists)) {

    //$value_exists[] = $name1; 
    foreach($lines2 as $line2) {
      $second = preg_split('/[\t]/', $line2);
	  $col_count = count($second);	
	  $name2 = trim($second[0]);	
	  
	  //Checking for equal names and then assign the passwords	  
	  if($name1 == $name2) {	  	  
         for($j = 0; $j < $col_count; $j++) {	
	       if(empty($data[$k][$j])) {		 
                 $data[$k][$j] = ($k == 0)?strtoupper($second[$j]):$second[$j];
		   } 
	     }	   
		
	     $i++;
	   }
	   
	 
    }
   
  if(($k > 3 && $k <= 21) || ($k>21 && $i > 1) || $k == 0) {
    if(!in_array($name1, $value_exists)) {
      $value_exists[] = $name1;
      $apollo_arr[$p] = $data[$k]; 
	  $p++;
	}  
  }
  
  $k++;
  //}
}

 $arr = array(); $t = 0; 
 $str = "<table border='1'>";
foreach($apollo_arr as $key=>$col_arr) {  
  //if($t == 10) break;
  $str = $str."<tr><td>".$key."</td>"; 
  
  for($i = 0; $i < count($col_arr)-4; $i++) {
    $str = $str."<td>".$col_arr[$i]."</td>";
  }
   $table = $str."</tr>";   
  $t++;
}
$str = $str."</table>";
//echo "<pre>"; print_r($data); echo "</pre>";
echo $str;


/*
 $arr = array(); $t = 0; 
 $str = "<table border='1'>";
foreach($data as $key=>$col_arr) {  
  //if($t == 10) break;
  $str = $str."<tr><td>".$key."</td>"; 
  
  for($i = 0; $i < count($col_arr)-4; $i++) {
    $str = $str."<td>".$col_arr[$i]."</td>";
  }
   $table = $str."</tr>";   
  $t++;
}
$str = $str."</table>";
//echo "<pre>"; print_r($data); echo "</pre>";
echo $str;*/


?>
