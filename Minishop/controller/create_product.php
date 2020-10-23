<?php
	require_once($_SERVER['DOCUMENT_ROOT']."/model/products.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	if (!is_admin())
		exit("Vous n'avez pas accès à cette page");
	echo "Create product ok<br/>";
	if (!isset($_POST["name"]) || $_POST["name"] == "")
	{
		echo "Error: product has no name<br/>";
		exit();
	}
	if (!isset($_POST["price"]) || $_POST["price"] == "")
	{
		echo "Error: product has no price<br/>";
		exit();
	}
	if (product_exists($_POST["name"]))
	{
		echo "This product already exists<br/>";
		exit();
	}
	create_product($_POST["name"], $_POST["desc"], $_POST["img"], $_POST["price"]);
	$list_cat = get_categories(0);
	$product = get_product_byname($_POST["name"]);
	assoc_prod_cat((int)$product["id"], $list_cat, $_POST);
	header("Location: /view/admin_products.php");
?>