<?php
// include the db file
require_once 'db.php';

if (isset($_POST['submit'])) {
  // get the user input
  $user = $_POST['user'];
  $count = !empty($_POST['count']) ? $_POST['count'] : null;

  // TODO: check hash and count input
  // TODO: check if hash exists in keymap table

  // initialize success indicators
  $success = 1;
  $success_message = '';

  // insert data into the table if count is provided
  if ($count !== null) {
    $success &= insert_data($user, $count);
    if ($success) {
      $success_message .= 'Upload successful';
    } else {
      $success_message .= 'Database upload was unsuccessful';
    }
    $success_message .= '<br>';
  }

  // return the heatmap as HTML
  $heatmap = "";
  $success &= draw_heatmap($user, $heatmap);
  if ($success) {
    $success_message .= 'Heatmap generated (see below)';
  } else {
    $success_message .= 'Heatmap generation was unsuccessful';
  }
}

if (isset($_POST['register'])) {
  $map = $_POST['map'];
  $user_hash = "";

  // TODO: check map input

  // insert data into the database
  $success = register_keymap($map, $user_hash);
  if ($success) {
    $success_message = 'Your unique user key is <code>' . $user_hash . '</code>';
  } else {
    $success_message = 'The keymap could not be uploaded';
  }
}
?>

<html>
  <head>
    <title>maptikal | Heatmap Generator for QMK Keybords</title>
    <link rel="stylesheet" type="text/css" href="style.css">
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
            <p><textarea name="user" rows="2" cols="50" placeholder="User Hash (Step 3)" required></textarea></p>
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
if (isset($_POST['submit']) and $success) {
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
    // If success, update classes and content
    echo 'span.innerHTML = "' . $success_message . '";';
    echo 'icon.classList.add("fa-check-circle");';
    echo 'submitMessage.classList.add("alert", "success");';
  } else {
    // If error, update classes and content
    echo 'span.innerHTML = "' . $success_message . '";';
    echo 'icon.classList.add("fa-times-circle");';
    echo 'submitMessage.classList.add("alert", "error");';
  }

  echo '</script>';
}
?>
  </body>
</html>
