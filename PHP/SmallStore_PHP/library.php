<?php /*Subject Code and Section: INT322B
       *Name: Sebastian Vieira
       *Date Submitted: June 25/2015
       *Student Declaration

I/we declare that the attached assignment is my/our own work in accordance with Seneca Academic Policy. No part of this assignment has been copied manually or electronically from any other source (including web sites) or distributed to other students.

Name Sebastian Vieira
Student ID 044830149*/
?>
<?php function top($title) { ?>
<?php //Title of all the pages?>
<!DOCTYPE html>
    <html>
        <head>
           <link rel="stylesheet" type="text/css" href="css/site.css"/>
           <title><?php echo $title; ?></title>
        </head>
        <body>
            <h1>Sebastian's Sporting Good Company</h1>
            <img src="logo/websiteLogo.PNG" alt="sportLogo"/>
            <ul id="titlebar">
                <li><a href="add.php">Add</a></li>
                <li><a href="view.php">View All</a></li>
            </ul>
            <div>
<?php }?>
<?php function account() {
    //SQL Account Login
    $secret = file('/home/int322_152b28/secret/topsecret');
    $link = mysqli_connect(trim($secret[0]),trim($secret[1]),trim($secret[2]),trim($secret[3])) or die(mysqli_connect_error($link));
    return $link;
}?>
<?php function query($link, $query) {
    //Query Function
   $store_query = mysqli_query($link, $query) or die("couldn't query: " . mysqli_error($link));
   return $store_query;
}?>
<?php function bottom() { ?>
<?php //Bottom of all pages?>
            <p class="text1">"Copyright &copy; <?php echo date('Y');?> Sebastian's Sporting Good Company"</p>
            </div>
            <hr/>
        </body>
    </html>
<?php }?>