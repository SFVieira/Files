<?php /*Subject Code and Section: INT322B
       *Name: Sebastian Vieira
       *Date Submitted: June 25/2015
       *Student Declaration

I/we declare that the attached assignment is my/our own work in accordance with Seneca Academic Policy. No part of this assignment has been copied manually or electronically from any other source (including web sites) or distributed to other students.

Name Sebastian Vieira
Student ID 044830149*/
?>
<?php include("library.php");?>
<?php
    /*Retrieving the id and changing the delete column to either y or n*/ 
    $_GET['id'];
    $a = $_GET['id'];
    $b = $_GET['deleted'];
    if($b == 'y')
    {
        $change = 'n';
    }
    else
    {
        $change = 'y';
    }
    $link = account();
    //Update query 
    $update_query = "UPDATE inventory set deleted='$change' WHERE id='$a'";
    $status = query($link, $update_query);
    //close mysql
    mysqli_close($link);
    if($status)
    {
        header("Location: view.php");
    }
    else
    {
        echo "You query did not work.";
    }
?>