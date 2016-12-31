<?php
    
    // configuration
    require("../includes/config.php");
    
    //if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
    // else if user reached page via post (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"])){
            apologize("You must provide a username.");
        }
        else if (empty($_POST["password"])){
            apologize("You must provide a password.");
        }
        else if ($_POST["password"] != $_POST["confirmation"]){
            apologize("The password provided does not match.");
        }
        
        // insert new user into database.
        $create_user = CS50::query("INSERT IGNORE INTO users(username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        if ($create_user == 0){
            apologize("User already exist.");
        }
        $rows = CS50::query("SELECT LAST_INSERT_ID() AS ID");
        $id = $rows[0]["id"];
        $_SESSION["id"] == $id;
        
        // redirect to portfolio.
        redirect("index.php");
    }
    
?>