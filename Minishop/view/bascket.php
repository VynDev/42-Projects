<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/products.php");
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
			<?php
			if (isset($_SESSION["bascket_msg"]) && $_SESSION["bascket_msg"] != "")
			{
				echo "<p>".$_SESSION["bascket_msg"]."</p><br/>";
				$_SESSION["bascket_msg"] = "";
			}
			$price_total = 0;
			foreach ($_SESSION["bascket"] as $key => $value)
			{
				echo "<p><a href='/view/product.php?id=".$value["id"]."'>".$value["name"]."</a> (".$value["amount"]."): ".$value["price"] * $value["amount"]." €</p><br/>";
				$price_total += $value["price"] * $value["amount"];
			}
			echo "<br/><p>Prix total: <strong>".$price_total." €</strong></p>";
			if (!isset($_SESSION["bascket"]))
				echo "<p>Votre panier est vide</p><br/>";
			else
			{
				echo
				"<form action=\"/controller/order.php\" method=\"POST\">
					<input type=\"submit\" name=\"submit\" value=\"Confirmer le panier\">
				</form>";
			}
			?>
		</div>
		<footer>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/footer.php"); ?>
		</footer>
	</body>
</html>