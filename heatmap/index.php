<?php
// include the db file
require_once 'db.php';

if (isset($_POST['submit'])) {
  // get the user input
  $user = $_POST['user'];
  $count = $_POST['count'];

  // insert data into the table
  $success_message = insert_data($user, $count);
  $success_message .= "<br>";

  // return the heatmap as HTML
  $heatmap = "";
  $success_message .= draw_heatmap($user, $heatmap);
}

if (isset($_POST['register'])) {
    $map = $_POST['map'];
    $user_hash = register_keymap($map);

    $hash_message = 'Your unique user key is <code>' . $user_hash . '</code>';
}
?>

<html>
  <head>
    <title>maptikal | Heatmap Generator for QMK Keybords</title>
    <link rel="stylesheet" type="text/css" href="style.css">
  </head>
  <body>
    <div id="container">
      <div id="guide-container">
        <?php include 'guide.html'; ?>
      </div>
      <div id="form-container">
        <div id="submit-container">
          <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
            <p><textarea name="user" rows="2" cols="50" placeholder="User Hash (Step 3)" required></textarea></p>
            <p><textarea name="count" rows="5" cols="40" placeholder="Key Count Array" required></textarea></p>
            <p><input type="submit" name="submit" value="Submit and Draw Heatmap"></p>
            <div id="success-message"></div>
          </form>
        </div>
        <div id="register-container">
          <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
            <p><textarea name="map" rows="5" cols="40" placeholder="Map of Key Widths (Step 1)" required></textarea></p>
            <p><input type="submit" name="register" value="Register Keymap"></p>
            <div id="hash-message"></div>
          </form>
        </div>
      </div>
    </div>
    <div id="image-container">
<?php
if (isset($heatmap)) {
  echo $heatmap;
} else {
  echo "Your heatmap will be displayed here";
}
?>
    </div>

<?php
if (isset($_POST['submit'])) {
  echo '<script>document.getElementById("success-message").innerHTML = "'.$success_message.'";</script>';
}
if (isset($_POST['register'])) {
  echo '<script>document.getElementById("hash-message").innerHTML = "'.$hash_message.'";</script>';
}
?>
  </body>
</html>
