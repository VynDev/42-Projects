<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");

	$index = "/index.php";

	if (!isset($_POST["login"]) || !isset($_POST["password"]) || !isset($_POST["c_password"]) || !isset($_POST["address"]) || !isset($_POST["city"]) || !isset($_POST["tel"]))
	{
		$_SESSION["create_msg"] = "Veuillez remplir tous les champs";
		header("Location: $index");
		exit();
	}

	if (empty($_POST["login"]) || empty($_POST["password"]) || empty($_POST["c_password"]) || empty($_POST["address"]) || empty($_POST["city"]) || empty($_POST["tel"]))
	{
		$_SESSION["create_msg"] = "Veuillez remplir tous les champs";
		header("Location: $index");
		exit();
	}

	if (user_exists($_POST["login"]))
	{
		$_SESSION["create_msg"] = "Ce login est déjà utilisé";
		header("Location: $index");
		exit();
	}

	if (strlen($_POST["login"]) < 3)
	{
		$_SESSION["create_msg"] = "Merci de choisir un login avec 6 caractères ou plus";
		header("Location: $index");
		exit();
	}

	if (strlen($_POST["password"]) < 6)
	{
		$_SESSION["create_msg"] = "Merci de choisir un mot de passe avec 6 caractères ou plus";
		header("Location: $index");
		exit();
	}

	if ($_POST["password"] != $_POST["c_password"])
	{
		$_SESSION["create_msg"] = "Le mot de passe et sa confirmation ne correspondent pas";
		header("Location: $index");
		exit();
	}
	create_user($_POST["login"], $_POST["password"], $_POST["address"], $_POST["city"], $_POST["tel"]);
	auth($_POST["login"], $_POST["password"]);
	header("Location: $index");
?>