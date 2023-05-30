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


// check user input for validity
function check_userhash($hash, &$message) {
  // check length and valid hex characters
  if (strlen($hash) != 64 or !ctype_xdigit($hash)) {
    $message .= "The user hash is not valid.<br>";
    return 0;
  }

  // check if user hash exists in the keymap table
  $conn = connect_db();
  $stmt = $conn->prepare("SELECT COUNT(*) AS count FROM keymap WHERE user = ?");
  $stmt->bind_param("s", $hash);
  $stmt->execute();
  $result = $stmt->get_result();
  $row = $result->fetch_assoc();
  $count = $row['count'];
  $stmt->close();
  $conn->close();

  if ($count == 0) {
    $message .= "User hash does not exist in the database.<br>";
    return 0;
  }

  // user hash is valid
  return 1;
}

function check_array($array, &$dims, &$message) {
  // check the overall string length
  if (strlen($array) >= 500) {
    $message .= "Array input is longer than 500 characters.<br>";
    return 0;
  }

  // validate as Python-formatted 2D array of integers using JSON and NumPy
  $python_snippet = 'import sys, json, numpy
try:
    arr = json.loads("' . $array . '")
    arr = numpy.array(arr).astype(float)
    assert arr.ndim == 2
except Exception as e:
    print(e)
    sys.exit(1)
print(arr.shape[0])
print(arr.shape[1])';
  exec("python3 -c '" . $python_snippet . "'", $output, $return);

  if ($return != 0) {
    $message .= "Array input is not a valid 2D array of numbers.<br>";
    return 0;
  }

  // all checks passed
  $dims = $output;
  return 1;
}

function check_dims($user, $dims, $table, &$message) {
  // get the dimensions from the table
  $db = connect_db();
  $stmt = $db->prepare("SELECT `rows`, `cols` FROM $table WHERE `user` = ?");
  $stmt->bind_param("s", $user);
  $stmt->execute();
  $result = $stmt->get_result();
  $record = $result->fetch_assoc();
  $stmt->close();
  $db->close();

  // compare rows and cols with the provided dimensions
  if ($record['rows'] != $dims[0] or $record['cols'] != $dims[1]) {
    $message .= "The array dimensions do not match the ones provided during registration.<br>";
    return 0;
  }

  return 1;
}


// register a randomly generated user key and upload the keymap
function register_keymap(&$random_key, $map, $dims, &$message) {
  // generate a random hex key
  $random_key = bin2hex(random_bytes(32)); // 32 bytes = 256 bits

  // get the database connection
  $db = connect_db();

  // prepare and execute the SQL statement to insert the data into the 'keymap' table
  $stmt = $db->prepare("INSERT INTO keymap (user, map, rows, cols) VALUES (?, ?, ?, ?)");
  $stmt->bind_param("ssii", $random_key, $map, $dims[0], $dims[1] - 1);

  $result = $stmt->execute();
  if (!$result) {
    $message .= "The keymap could not be uploaded.<br>";
    return 0;
  }

  // close the statement and database connection
  $stmt->close();
  $db->close();

  // return the success value
  $message .= "Your unique user key is <code>" . $random_key . "</code>.<br>";
  return 1;
}


// insert data into the keycount table
function insert_keycount($user, $count, &$message) {
  // get the current time in UTC format
  $time = gmdate("Y-m-d H:i:s");

  // connect to the database
  $conn = connect_db();

  // prepare and execute the insert query
  $stmt = $conn->prepare("INSERT INTO keycount (time, user, count) VALUES (?, ?, ?)");
  $stmt->bind_param("sss", $time, $user, $count);

  $result = $stmt->execute();
  if (!$result) {
    $message .= "Database upload was unsuccessful.<br>";
    return 0;
  }

  // close the statement and the connection
  $stmt->close();
  $conn->close();

  // return the success value
  $message .= "Your keycounts have been uploaded.<br>";
  return 1;
}


// call Python script to generate heatmap
function draw_heatmap($user, &$image, &$message) {
  // generate heatmap from data
  exec("python3 heatmap.py $user", $output, $return);
  if ($return != 0) {
    $message .= "Heatmap generation was unsuccessful.<br>";
    return 0;
  }
  $image = $output[0];

  // set a success value
  $message .= "Heatmap generated (see below).<br>";
  return 1;
}
?>
