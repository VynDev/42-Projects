<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");

	$index = "/index.php";

	if (!$_POST["login"] || !$_POST["password"])
	{
		$_SESSION["login_msg"] = "Veuillez renseigner correctement les champs";
		header("Location: $index");
		exit();
	}
	if (!auth($_POST["login"], $_POST["password"]))
	{
		$_SESSION["login_msg"] = "Mauvais login/mot de passe";
		header("Location: $index");
		exit();
	}
	header("Location: $index");
?>