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

// insert data into the table and return a success or error message
function insert_data($user, $count) {
  // get the current time in UTC format
  $time = gmdate("Y-m-d H:i:s");

  // connect to the database
  $conn = connect_db();

  // prepare and execute the insert query
  $unsuccessful_message = "The database upload was unsuccessful";

  $stmt = $conn->prepare("INSERT INTO keycount (time, user, count) VALUES (?, ?, ?)");
  if (!$stmt) {
    $conn->close();
    return $unsuccessful_message;
  }

  // execute the statement
  $stmt->bind_param("sss", $time, $user, $count);
  if (!$stmt) {
    $conn->close();
    return $unsuccessful_message;
  }

  $result = $stmt->execute();
  if (!$result) {
    $conn->close();
    return $unsuccessful_message;
  }

  // close the statement and the connection
  $stmt->close();
  $conn->close();

  // generate heatmap from data
  exec("python3 heatmap.py $user", $output, $return);
  if ($return != 0) {
    return "Something went wrong with the heatmap generation";
  }

  // set a success message
  return "Upload successful!";
}
?>
