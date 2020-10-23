<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/orders.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	if (!isset($_GET["id"]))
		exit();
	$order = get_order_byid($_GET["id"]);
	if (!is_admin() && $order["id_user"] != $_SESSION["id"])
		exit();
?>
<html>
	<head>
		<?php include($_SERVER['DOCUMENT_ROOT']."/part/head.php"); ?>
	</head>
	<body>
		<header>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/header.php"); ?>
		</header>
		<div class="content">
			<h2>Description de la commande</h2>
			<?php
				$price_total = 0;
				echo "<p>".$order["login"]." (".$order["id"]."):</p><br/>";
				echo "<p>".$order["address"]."<br/>";
				echo $order["city"]."<br/>";
				echo $order["tel"]."</p><br/>";
				echo "<p>";
				foreach ($order["products"] as $key => $value)
				{
					echo $value["name"].": ".$value["amount"]." (<strong>".$value["price"]." €</strong>)<br/>";
					$price_total += $value["amount"] * $value["price"];
				}
				echo "<br/>Total: <strong>".$price_total. "€</strong></p>";
				if (is_admin())
				{
					echo
					"<form action='/controller/finish_order.php' method='POST'>
						<input type='submit' name='submit' value='Terminer la commande'>
						<input type='hidden' name='id' value='".$order["id"]."'>
					</form>";
				}
			?>
		</div>
		<footer>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/footer.php"); ?>
		</footer>
	</body>
</html>
