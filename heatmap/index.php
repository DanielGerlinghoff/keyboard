<?php
// include the db file
require_once 'db.php';

// check if the form is submitted
if (isset($_POST['submit'])) {
  // get the user input
  $user = $_POST['user'];
  $count = $_POST['count'];

  // insert data into the table and display the result
  $success_message = insert_data($user, $count);
}
?>

<html>
  <head>
    <title>My Website</title>
    <link rel="stylesheet" type="text/css" href="style.css">
  </head>
  <body>
    <div id="container">
      <div id="form-container">
        <div id="submit-container">
          <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
            <p><textarea name="user" rows="2" cols="50" placeholder="User Hash" required></textarea></p>
            <p><textarea name="count" rows="5" cols="40" placeholder="Key Count Array" required></textarea></p>
            <p><input type="submit" name="submit" value="Submit"></p>
            <div id="success-message"></div>
          </form>
        </div>
        <div id="hash-container">
          <form>
            <p><button type="button" id="generate-hash">Generate Hash</button></p>
            <p><textarea id="hash-textbox" rows="2" cols="50"></textarea></p>
          </form>
        </div>
      </div>
      <div id="guide-container">
        <h2>User Guide</h2>
        <p>Here's how to use the website:</p>
        <ul>
          <li>Step 1: Do something</li>
          <li>Step 2: Do something else</li>
          <li>Step 3: Do something else</li>
        </ul>
      </div>
    </div>
    <div id="image-container">
      <!-- Bypass browser caching by making URL unique -->
      <img src="heatmap.png?t=<?php echo time(); ?>" alt="Your heatmap will be displayed here">
    </div>

<?php
if (isset($_POST['submit'])) {
  // display the success message
  echo '<script>document.getElementById("success-message").innerHTML = "'.$success_message.'";</script>';
}
?>
    <script>
      // Function to generate a random 256-bit hex string
      function generateRandomHex() {
        let array = new Uint8Array(32);
        window.crypto.getRandomValues(array);
        let hex = Array.from(array, function(byte) {
          return ('0' + byte.toString(16)).slice(-2);
        }).join('');
        return hex;
      }

      // Get the button and textbox elements
      const generateHashButton = document.getElementById("generate-hash");
      const hashTextbox = document.getElementById("hash-textbox");

      // Add a click event listener to the button
      generateHashButton.addEventListener("click", function() {
        // Insert the random string into the textbox
        hashTextbox.value = generateRandomHex();
      });
    </script>
  </body>
</html>
