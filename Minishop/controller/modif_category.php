<?php
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	if (!is_admin())
		exit("Vous n'avez pas accès à cette page");
	echo "Modif category ok<br/>";
	if (isset($_POST["modif"]))
	{
		if (!isset($_POST["name"]) || $_POST["name"] == "")
		{
			echo "Error: Category has no name<br/>";
			exit();
		}
		modif_category((int)$_POST["id"], $_POST["name"], $_POST["desc"]);
		header("Location: /view/admin_categories.php");
	}
	else if (isset($_POST["delete"]))
	{
		delete_category((int)$_POST["id"]);
		header("Location: /view/admin_categories.php");
	}
?>