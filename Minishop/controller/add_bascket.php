<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/products.php");
	if (!isset($_POST["id"]) || !isset($_POST["amount"]))
		exit();
	$product = get_product_byid($_POST["id"]);
	$order = array("id" => $_POST["id"], "amount" => $_POST["amount"], "name" => $product["name"], "price" => $product["price"]);
	$_SESSION["bascket"][] = $order;
	$_SESSION["bascket_msg"] = "Votre panier a été mis a jour !";
	header("Location: /view/bascket.php");
?>