<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/products.php");

	if (!isset($_GET["id"]))
		exit();

	$id = (int) $_GET["id"];
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
			<div id="product_description">
				<div class="product_description_div">
					<?php
					$product = get_product_byid($id);
					echo "<p>".$product["name"]."</p><br/>";
					echo "<p><strong>".$product["price"]." €</strong></p><br/>";
					echo "<img src='".$product["img"]."' alt='Image' title='Image'>";
					?>
				</div>
				<div class="product_description_div">
					<?php
					echo "<p>".$product["description"]."</p>";
					echo "<hr/>";
					$categories = get_prod_cat($id);
					echo "<p>";
					foreach ($categories as $key => $value)
					{
						$category = get_category_byid($value["id_category"]);
						echo $category["name"]." ";
					}
					echo "</p>";
					?>
				</div>	
			</div>
			<form action="/controller/add_bascket.php", method="POST">
				<input type="submit" name="submit" value="Ajouter au panier">
				<input type="number" name="amount" value="1" min="1">
				<input type="hidden" name="id" value="<?php echo $id; ?>">
			</form>
		</div>
		<footer>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/footer.php"); ?>
		</footer>
	</body>
</html>