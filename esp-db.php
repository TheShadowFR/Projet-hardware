<?php
    $servername = "localhost";
    // Your Database name
    $dbname = "esp32c3_rfid";
    // Your Database user
    $username = "YOUR_USERNAME";
    // Your Database user password
    $password = "YOUR_PASSWORD";
    
    function getAllAuthorizedUid() {
        global $servername, $username, $password, $dbname;

        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }

        $sql = "SELECT UID FROM badge WHERE state=1";
        if ($result = $conn->query($sql)) {
            return $result;
        }
        else {
            return false;
        }
        $conn->close();
    }



?>