<?php
  $cleared = explode(",",$_GET["clear"]);
  $lines = $_POST["lines"]."|".$_POST["line"].",".$_POST["A"].",".$_POST["B"];

  $s_lines = explode("|", $lines);
  $split_lines = array();

  for($e=0; $e < count($s_lines); $e++) {
    $split_lines[$e] = explode(",", $s_lines[$e]);
  }

  function in_lines($var, $split_lines){
    if($split_lines == null){
      return false;
    }
    foreach ($split_lines as $l) {
      if($l[0] == strval($var)){
        return true;
      }
    }
    return false;
  }

  function getA_B($var, $split_lines) {
    foreach ($split_lines as $l) {
      if($l[0] == strval($var) ){
        return array($l[1], $l[2]);
      }
    }
  }

  echo 
    "<html>
      <head>
        <meta charset=UTF-8>
        <link rel='stylesheet' href='index.css'>
        <title>multiplication</title>
      </head>
      <body>
    ";

  echo "<table id='big_table'>";
  echo "<td id='A'><table id='A'><h1>A</h1>";
  for ($i=1; $i<30; $i++){  
    if(!in_array($i, $cleared)){
      if(in_lines($i, $split_lines)){
        $a = getA_B($i, $split_lines)[0];
        echo "<tr><div id=''>$a</div></tr>";
      }
      else{
        echo "<tr><div>7</div></tr>";
      }  
    }
  }
  echo "</table></td>";

  echo "<td id='B'><table id='B'><h1>B</h1>";
  for ($i=1; $i < 30; $i++) { 
    if(!in_array($i, $cleared)){
      if(in_lines($i, $split_lines)){
        $b = getA_B($i, $split_lines)[1];
        echo "<tr><div>$b</div></tr>";
      }
      else{
        echo "<tr><div>$i</div></tr>";
      }
    }
  }
  echo "</table></td>";
  
  echo "<td id='C'><table id='C'><h1>C</h1>";
  for ($i=1; $i < 30; $i++) { 
    if(!in_array($i,$cleared)){
      if(in_lines($i, $split_lines)){
        $ab = getA_B($i, $split_lines);
        $val = $ab[0] * $ab[1];
        echo "<tr><div>$val</div></tr>";
      }
      else{
        $val = $i * 7;
        echo "<tr><div>$val</div></tr>";
      }  
    }
  }
  echo "</table></td>";

  echo "<td><table id='Action'><h1>Action</h1>";
  for ($i=1; $i < 30; $i++) {
    if(!in_array($i, $cleared)){
      echo "<tr><div>
              <a href='http://www.multiplication.cr/index.php?clear=";

      if(!empty($cleared)){
        foreach ($cleared as $num) {
          echo "$num,";
        }
      }
      echo "$i";
      echo "&lines=$lines'>effacer</a>";

      echo "<a href='http://www.multiplication.cr/modify.php?&clear=";
      if(!empty($cleared)){
        foreach ($cleared as $num) {
          echo "$num,";
        }
      }
      echo "&lines=$lines&line=$i'>modifier</a>
            </div></tr>";
    }
  }
  echo "</td></table>";
  echo "</td></table>";
  echo "</body></html>"

?>

