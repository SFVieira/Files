<?php /*Subject Code and Section: INT322B
       *Name: Sebastian Vieira
       *Date Submitted: June 25/2015
       *Student Declaration

I/we declare that the attached assignment is my/our own work in accordance with Seneca Academic Policy. No part of this assignment has been copied manually or electronically from any other source (including web sites) or distributed to other students.

Name Sebastian Vieira
Student ID 044830149*/
?>
<?php include("library.php"); ?>
<?php top("View"); ?>
<?php
    //SELECT statement to put the data into a table
    $link = account();
    //Select Query
    $view_query = "SELECT * from inventory";
    $ref = query($link, $view_query);
    //Close mysql
    mysqli_close($link);
?>
<?php //Table for the View.php Page?>
<table class="display">
    <tr>
        <th>ID</th>
        <th>Item Name</th>
        <th>Description</th>
        <th>Supplier</th>
        <th>Cost</th>
        <th>Price</th>
        <th>Number On Hand</th>
        <th>Reorder Level</th>
        <th>On Back Order?</th>
        <th>Delete/Restore</th>
    </tr>
<?php
    /*Loops through the mysql query to put it into the table*/
    while ($store = mysqli_fetch_assoc($ref)) {
?>
    <tr>
        <?php //Puts the data into a table?>
        <td><?= $store['id'] ?></td>
        <td><?= $store['itemName']?></td>
        <td><?= $store['description']?></td>
        <td><?= $store['supplierCode']?></td>
        <td><?= $store['cost']?></td>
        <td><?= $store['price']?></td>
        <td><?= $store['onHand']?></td>
        <td><?= $store['reorderPoint']?></td>
        <td><?= $store['backOrder']?></td>
        <td><a href="delete.php?id=<?php print $store['id'];?>&deleted=<?php print $store['deleted'];?>"><?php if($store['deleted'] == 'n') {echo 'Delete';} else{ echo "Restore";}?></a></td>
    </tr>
<?php }?>
</table>
<?php bottom(); ?>