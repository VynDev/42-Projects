<?php
	require_once($_SERVER['DOCUMENT_ROOT']."/model/products.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	if (!is_admin())
		exit("Vous n'avez pas accès à cette page");
	if (isset($_POST["modif"]))
	{
		if (!isset($_POST["name"]) || $_POST["name"] == "")
		{
			echo "Error: product has no name<br/>";
			exit();
		}
		modif_product((int)$_POST["id"], $_POST["name"], $_POST["desc"], $_POST["img"], $_POST["price"]);
		$list_cat = get_categories(0);
		assoc_prod_cat((int)$_POST["id"], $list_cat, $_POST);
		header("Location: /view/admin_products.php");
	}
	else if (isset($_POST["delete"]))
	{
		delete_product((int)$_POST["id"]);
		header("Location: /view/admin_products.php");
	}
?>