<?php
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	if (!is_admin())
		exit("Vous n'avez pas accès à cette page");
	echo "Create category ok<br/>";
	if (!isset($_POST["name"]) || $_POST["name"] == "")
	{
		echo "Error: Category has no name<br/>";
		exit();
	}
	if (category_exists($_POST["name"]))
	{
		echo "This category already exists<br/>";
		exit();
	}
	create_category($_POST["name"], $_POST["desc"]);
	header("Location: /view/admin_categories.php");
?>