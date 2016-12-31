<?php
    require("../includes/config.php");
    
    
    if ($_SERVER["REQUEST_METHOD"] = "POST"){
        if (empty($_POST["symbol"])){
            render("quote_form.php", ["title" => "Quote"]);
        }
        else if (!empty($_POST["symbol"])){
            $arr = lookup($_POST["symbol"]);
            
            if($arr != false){
                $arr["title"] = "Quote";
                render("quote_display.php", ["title" => "Quote", "name" => $arr["name"], "price" => $arr["price"], "symbol" => $arr["symbol"]]);
            }
            else if ($arr == false){
                apologize("Invalid symbol entered.");
            }
        }
    }
    
    // else render page.
    else{
        render("quote_form.php", ["title" => "Quote"]);
    }
?>