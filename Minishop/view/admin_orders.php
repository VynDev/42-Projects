<?php
	require_once($_SERVER['DOCUMENT_ROOT']."/model/orders.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
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
			<h2>Liste des commandes</h2>
			<?php
				$orders = get_orders(0);
				foreach ($orders as $key => $value)
				{
					echo "<p><a href='/view/order_description.php?id=".$value["id"]."'> Commande de ".$value["login"]." (".$value["id"].")</a></p><br/>";
				}
			?>
		</div>
		<footer>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/footer.php"); ?>
		</footer>
	</body>
</html>
