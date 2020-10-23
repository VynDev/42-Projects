<?php
	include($_SERVER['DOCUMENT_ROOT']."/config.php");
	function ft_print($str)
	{
		echo $str."<br/>";
	}

	ft_print("installation...");
	$db = get_config();
	$mysqli = mysqli_connect($db["host"], $db["user"], $db["password"]);
	if (mysqli_connect_errno())
	{
	    printf("Échec de la connexion : %s<br/>\n", mysqli_connect_error());
	    exit();
	}
	if (!mysqli_query($mysqli, "CREATE DATABASE IF NOT EXISTS minishop"))
	{
		ft_print("Can't create database");
		exit();
	}
	if (!mysqli_select_db($mysqli, "minishop"))
		ft_print("Can't select database");
	if (!mysqli_query($mysqli, "CREATE TABLE IF NOT EXISTS users (
			id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
			login VARCHAR(30) NOT NULL,
			password VARCHAR(255) NOT NULL,
			address VARCHAR(255) NOT NULL,
			city VARCHAR(255) NOT NULL,
			tel VARCHAR(255) NOT NULL,
			admin SMALLINT NOT NULL)"))
		ft_print("Can't create users table");

	if (!mysqli_query($mysqli, "CREATE TABLE IF NOT EXISTS products (
			id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
			name VARCHAR(50) NOT NULL,
			description TEXT,
			img VARCHAR(255),
			price INT UNSIGNED NOT NULL)"))
		ft_print("Can't create products table");

	if (!mysqli_query($mysqli, "CREATE TABLE IF NOT EXISTS categories (
			id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
			name VARCHAR(50) NOT NULL,
			description TEXT)"))
		ft_print("Can't create categories table");

	if (!mysqli_query($mysqli, "CREATE TABLE IF NOT EXISTS prod_cat (
			id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
			id_product INT UNSIGNED NOT NULL,
			id_category INT UNSIGNED NOT NULL)"))
		ft_print("Can't create categories table");

	if (!mysqli_query($mysqli, "CREATE TABLE IF NOT EXISTS orders (
			id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
			id_user INT UNSIGNED NOT NULL,
			products TEXT NOT NULL)"))
		ft_print("Can't create categories table");
	mysqli_close($mysqli);
	ft_print("installation finished");
?>