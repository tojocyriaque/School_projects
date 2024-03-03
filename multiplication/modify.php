<?php

$line = $_GET["line"];
$lines = $_GET["lines"];
$cleared = $_GET["clear"];

echo "
<html>
  <head>
    <meta charset='UTF-8'>
    <title>Modifier</title>
  </head>

  <body>
    <form method='post' action='http://www.multiplication.cr/index.php?&clear=$cleared'>
      <input type='text' name='lines' value='$lines' hidden>
      <input type='number' name='line' value='$line' hidden>
      <input type='number' name='A'><br>
      <input type='number' name='B'><br>
      <input type='submit' name='submit' value='modifier'>
    </form>
  </body>

</html>
";

$e = "7";

?>

