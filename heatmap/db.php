<?php
// include the credentials file
require_once('db_credentials.php');

// connect to the database and return the connection object
function connect_db() {
  global $servername, $username, $password, $dbname;
  $conn = new mysqli($servername, $username, $password, $dbname);

  if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }

  return $conn;
}

// register a randomly generated user key and upload the keymap
function register_keymap($map, &$random_key) {
  // generate a random hex key
  $random_key = bin2hex(random_bytes(32)); // 32 bytes = 256 bits

  // get the database connection
  $db = connect_db();

  // prepare and execute the SQL statement to insert the data into the 'keymap' table
  $stmt = $db->prepare("INSERT INTO keymap (user, map) VALUES (?, ?)");
  $stmt->bind_param("ss", $random_key, $map);

  $result = $stmt->execute();
  if (!$result)
      return 0;

  // close the statement and database connection
  $stmt->close();
  $db->close();

  // return the success value
  return 1;
}

// insert data into the table and return a success or error value
function insert_data($user, $count) {
  // get the current time in UTC format
  $time = gmdate("Y-m-d H:i:s");

  // connect to the database
  $conn = connect_db();

  // prepare and execute the insert query
  $stmt = $conn->prepare("INSERT INTO keycount (time, user, count) VALUES (?, ?, ?)");
  $stmt->bind_param("sss", $time, $user, $count);

  $result = $stmt->execute();
  if (!$result)
      return 0;

  // close the statement and the connection
  $stmt->close();
  $conn->close();

  // return the success value
  return 1;
}

// call Python script to generate heatmap
function draw_heatmap($user, &$image) {
  // generate heatmap from data
  exec("python3 heatmap.py $user", $output, $return);
  if ($return != 0) {
    return 0;
  }
  $image = $output[0];

  // set a success value
  return 1;
}
?>
