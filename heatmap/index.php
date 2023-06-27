<?php
// include the db file
require_once 'db.php';

if (isset($_POST['submit'])) {
  // initialize success indicators
  $success = 1;
  $success_message = "";

  // get the user input and check for validity
  $user = $_POST['user'];
  $success &= check_userhash($user, $success_message);

  $count = !empty($_POST['count']) ? $_POST['count'] : null;
  $dims = [];
  if ($count !== null) {
    $count = preg_replace('/[\r\n\s]+/', '', $count);
    $success &= check_array($count, $dims, $success_message);
  }

  // check if the dims are the same as specified in keymap table
  if ($success and $count !== null) {
    $success &= check_dims($user, $dims, "keymap", $success_message);
  }

  // insert data into the table if count is provided
  if ($success and $count !== null) {
    $success &= insert_keycount($user, $count, $success_message);
  }

  // return the heatmap as HTML
  $heatmap = "";
  $success &= draw_heatmap($user, $heatmap, $success_message);
}

if (isset($_POST['register'])) {
  $user_hash = "";
  $dims = [];

  // initialize success indicators
  $success = 1;
  $success_message = "";

  // get the user input, remove line breaks and check for validity
  $map = $_POST['map'];
  $map = preg_replace('/[\r\n\s]+/', '', $map);

  $success &= check_array($map, $dims, $success_message);

  // insert data into the database
  if ($success) {
    $success &= register_keymap($user_hash, $map, $dims, $success_message);
  }
}
?>

<html>
  <head>
    <title>maptikal | Heatmap Generator for QMK Keyboards</title>
    <link rel="stylesheet" type="text/css" href="style.css">
    <link rel="icon" type="image/png" href="favicon.png">
    <script src="https://kit.fontawesome.com/129a986cf5.js" crossorigin="anonymous"></script>
  </head>
  <body>
    <div id="container">
      <div id="guide-container">
        <?php include 'guide.html'; ?>
      </div>
      <div id="form-container">
        <div id="submit-container">
          <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
            <p><textarea name="user" rows="2" cols="50" placeholder="User Hash (Step 3)" required autofocus></textarea></p>
            <p><textarea name="count" rows="5" cols="40" placeholder="Key Count Array (optional)"></textarea></p>
            <p><input type="submit" name="submit" value="Submit and Draw Heatmap"></p>
            <div id="submit-message" class="alert">
              <i class="fas"></i>
              <span></span>
            </div>
          </form>
        </div>
        <div id="register-container">
          <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
            <p><textarea name="map" rows="5" cols="40" placeholder="Map of Key Widths (Step 1)" required></textarea></p>
            <p><input type="submit" name="register" value="Register Keymap"></p>
            <div id="register-message" class="alert">
              <i class="fas"></i>
              <span></span>
            </div>
          </form>
        </div>
      </div>
    </div>
    <div id="image-container">
<?php
if (isset($_POST['submit']) and $heatmap != "") {
  echo $heatmap;
} else {
  echo "Your heatmap will be displayed here";
}
?>
    </div>

<?php
if (isset($_POST['submit']))
  $id = "submit-message";
if (isset($_POST['register']))
  $id = "register-message";

if (isset($id)) {
  echo '<script>';
  echo 'var submitMessage = document.getElementById("'. $id . '");';
  echo 'var span = submitMessage.querySelector("span");';
  echo 'var icon = submitMessage.querySelector("i");';

  if ($success == 1) {
    // if success, update classes and content
    echo 'span.innerHTML = "' . $success_message . '";';
    echo 'icon.classList.add("fa-check-circle");';
    echo 'submitMessage.classList.add("alert", "success");';
  } else {
    // if error, update classes and content
    echo 'span.innerHTML = "' . $success_message . '";';
    echo 'icon.classList.add("fa-times-circle");';
    echo 'submitMessage.classList.add("alert", "error");';
  }

  echo '</script>';
}
?>
  </body>
</html>
