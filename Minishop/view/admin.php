<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	if (!is_admin())
		exit("Vous n'avez pas accès à cette page");
?>
<!DOCTYPE html>
<html>
	<head>
		<?php include($_SERVER['DOCUMENT_ROOT']."/part/head.php"); ?>
	</head>
	<body>
		<header>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/header.php"); ?>
		</header>
		<div class="content">
			<p>Welcome to the admin zone</p>
			<p><a href="admin_categories.php">Catégories</a></p>
			<p><a href="admin_products.php">Produits</a></p>
			<p><a href="admin_orders.php">Commandes</a></p>
		</div>
		<footer>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/footer.php"); ?>
		</footer>
	</body>
</html>