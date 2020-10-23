<?php
	require_once($_SERVER['DOCUMENT_ROOT']."/model/orders.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	if (!is_admin())
		exit("Vous n'avez pas accès à cette page");
	session_start();
	delete_order($_POST["id"]);
	header("Location: /view/admin_orders.php");
?>