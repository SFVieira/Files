<?php /*Subject Code and Section: INT322B
       *Name: Sebastian Vieira
       *Date Submitted: June 25/2015
       *Student Declaration

I/we declare that the attached assignment is my/our own work in accordance with Seneca Academic Policy. No part of this assignment has been copied manually or electronically from any other source (including web sites) or distributed to other students.

Name Sebastian Vieira
Student ID 044830149*/
?>
<?php include("library.php"); ?>
<?php
    //Validation variables
    $data_validation = true;
    $name_error = "";
    $description_error = "";
    $supplierCode_error = "";
    $cost_error ="";
    $price_error = "";
    $onHand_error = "";
    $reorderPoint_error = "";
    if($_POST)
    {   //Error checking
        //Validation for Item Name
        if(!preg_match("/^([a-z]|[,: ';-]|[0-9]){1,40}$/i", trim($_POST['name'])))
        {
            $name_error = "Item name must contain letters, digits, and any of these characters (,;:'-)";
            $data_validation = false;
        }
        //Validation for Description
        if(!preg_match("/^([a-z]|[., '-]|[\\r\\n]|[0-9]){1,}$/i", trim($_POST['description'])))
        {
            $description_error = "Description must contain letters, digits and any of these character (.,'-)";
            $data_validation = false;
        }
        //Validation for Supplier Code
        if(!preg_match("/^([a-z]|[0-9]|[ -]){1,40}$/i", trim($_POST['supplierCode'])))
        {
            $supplierCode_error = "Supplier Code must contain letters, digits, and dashes";
            $data_validation = false;
        }
        //Validation for Cost
        if(!preg_match("/^[0-9]{1,8}\.[0-9]{2}$/", trim($_POST['cost'])))
        {
            $cost_error = "Cost must be a monetary amount with digits a period and two digits";
            $data_validation = false;
        }
        //Validation for Selling Price
        if(!preg_match("/^[0-9]{1,8}\.[0-9]{2}$/", trim($_POST['price'])))
        {
            $price_error = "Selling Price must be a monetary amount with digits a period and two digits";
            $data_validation = false;
        }
        //Validation for Number on Hand
        if(!preg_match("/^[0-9]{1,}$/", trim($_POST['onHand'])))
        {
            $onHand_error = "Number on Hand must only contain digits";
            $data_validation = false;
        }
        //Validation for Reorder Point
        if(!preg_match("/^[0-9]{1,}$/", trim($_POST['reorderPoint'])))
        {
            $reorderPoint_error = "Reorder Point must only contain digits";
            $data_validation = false;
        }
        //Checks if all data is valid
        if($_POST && $data_validation)
        {
            $link = account();
            $item = $_POST['name'];
            $desc = $_POST['description'];
            $supp_code = $_POST['supplierCode'];
            $cst = $_POST['cost'];
            $pre = $_POST['price'];
            $on_hd = $_POST['onHand'];
            $re_point = $_POST['reorderPoint'];
            $back_ord = $_POST['backOrder'];
            $delete_link = "n";
            //Insert query
            $insert_query = 'INSERT INTO inventory set id="", itemName="' . $item . '", description="' . $desc . '", supplierCode="' . $supp_code . '", cost="' . $cst . '", price="' . $pre . '", onHand="' . $on_hd . '", reorderPoint="' . $re_point . '", backOrder="' . $back_ord . '", deleted="' . $delete_link . '"';  
            $status = query($link, $insert_query);
            //Close mysql
            mysqli_close($link);
            if($status)
            {
                header("Location: view.php");
            }
            else
            {
                echo "Your query did not work.";
            }
        }
        else
        {
            //Send error messages to form
            form($name_error, $description_error, $supplierCode_error, $cost_error, $price_error, $onHand_error, $reorderPoint_error);
        }
    }
    else
    {
        //Displays plank form
        form('','','','','','','');
    }
?>
<?php function form($name ="", $descritpion = "", $supplierCode ="", $cost ="", $price = "", $onHand ="", $reorderPoint = "") {?>
<?php top("Add"); ?>
                <?php //Form Layout?>
                <form method="post" action="">
                <p class="text1">All items mandatory expect "On Back Order"</p>
                <table>
                    <tr>
                        <td>    
                            <label class="labels" for="name">Item Name: </label>
                        </td>
                        <td class="errors">
                            <input type="text" id="name" name="name" value="<?php if(isset($_POST['name'])) {echo $_POST['name'];}?>"/>
                            <?php if(isset($_POST['name'])) {echo  $name;}?>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <label class="labels">Description:</label> 
                        </td>
                        <td class="errors">
                            <textarea name="description" rows="5" cols="20"><?php if(isset($_POST['description'])) {echo $_POST['description'];}?>
                            </textarea>
                             <span class="inline"><?php if(isset($_POST['description'])) {echo $descritpion;}?></span>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <label class="labels" for="supplierCode">Supplier Code:</label>
                        </td>
                        <td class="errors">
                            <input type="text" id="supplierCode" name="supplierCode" value="<?php if(isset($_POST['supplierCode'])) {echo $_POST['supplierCode'];}?>"/>
                            <?php if(isset($_POST['supplierCode'])) {echo $supplierCode;}?>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <label class="labels" for="cost">Cost:</label>
                        </td>
                        <td class="errors">
                            <input type="text" id="cost" name="cost" value="<?php if(isset($_POST['cost'])) {echo $_POST['cost'];}?>"/>
                            <?php if(isset($_POST['cost'])) {echo $cost;}?>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <label class="labels" for="price">Selling price:</label>
                        </td>
                        <td class="errors">
                            <input type="text" id="price" name="price" value="<?php if(isset($_POST['price'])) {echo $_POST['price'];}?>">
                            <?php if(isset($_POST['price'])) {echo $price;}?>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <label class="labels" for="onHand">Number on hand:</label>
                        </td>
                        <td class="errors">
                            <input type="text" id="onHand" name="onHand" value="<?php if(isset($_POST['onHand'])) {echo $_POST['onHand'];}?>"/>
                            <?php if(isset($_POST['onHand'])) {echo $onHand;}?>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <label class="labels" for="reorderPoint">Reorder Point:</label>
                        </td>
                        <td class="errors">
                            <input type="text" id="reorderPoint" name="reorderPoint" value="<?php if(isset($_POST['reorderPoint'])) {echo $_POST['reorderPoint'];}?>"/>
                            <?php if(isset($_POST['reorderPoint'])) {echo $reorderPoint;}?>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <label class="labels" for="backOrder">On Back Order:</label>
                        </td>
                        <td>
                            <input type="text" id="backOrder" name="backOrder" value="<?php if(isset($_POST['backOrder'])) {echo $_POST['backOrder'];}?>" size="2" maxlength="1"/>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <input type="submit" name="submit"/>
                        </td>
                    </tr>
                </table>
                </form>
<?php }?>
<?php bottom(); ?>