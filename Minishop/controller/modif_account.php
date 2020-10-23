<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");

	$index = "/view/account.php";

	if (!isset($_POST["type"]))
		exit("Error");
	if ($_POST["type"] == "password")
	{
		if (!isset($_POST["password"]) || !isset($_POST["c_password"]))
		{
			$_SESSION["account_msg"] = "Veuillez remplir tous les champs";
			header("Location: $index");
			exit();
		}

		if (empty($_POST["password"]) || empty($_POST["c_password"]))
		{
			$_SESSION["account_msg"] = "Veuillez remplir tous les champs";
			header("Location: $index");
			exit();
		}

		if (strlen($_POST["password"]) < 6)
		{
			$_SESSION["account_msg"] = "Merci de choisir un mot de passe avec 6 caractères ou plus";
			header("Location: $index");
			exit();
		}

		if ($_POST["password"] != $_POST["c_password"])
		{
			$_SESSION["account_msg"] = "Le mot de passe et sa confirmation ne correspondent pas";
			header("Location: $index");
			exit();
		}
		modif_user_password($_SESSION["id"], $_POST["password"]);
	}
	else if ($_POST["type"] == "delete")
	{
		delete_user($_SESSION["id"]);
		unset($_SESSION["login"]);
		unset($_SESSION["id"]);
		unset($_SESSION["admin"]);
		header("Location: /index.php");
		exit();
	}
	header("Location: $index");
?>