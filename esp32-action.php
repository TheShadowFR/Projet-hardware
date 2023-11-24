<?php
    include_once('esp-db.php');

    if ($_SERVER["REQUEST_METHOD"] == "GET") {
        $action = test_input($_GET["action"]);
        if ($action == "authorized_uid") {
            $result = getAllAuthorizedUid();
            if ($result) {
                while ($row = $result->fetch_assoc()) {
                    $rows[] = $row["UID"];
                }
            }
            echo json_encode($rows);
        }
        else {
            echo "Invalid HTTP request.";
        }
    }

    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
?>