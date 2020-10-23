<?php
	session_start();

	$_SESSION["login"] = "";
	$_SESSION["id"] = -1;
	$_SESSION["admin"] = 0;
	header("Location: /index.php");
?>