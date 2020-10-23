<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/products.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	if (!is_admin())
		exit("Vous n'avez pas accès à cette page");
	//create_category("Games", "Just video games here");

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
			<center>
			<h2>Créer un produit</h2>
			<form class='form_category' action="/controller/create_product.php" method="POST">
				<p>Nom du produit</p>
				<input class="form_category_input" type="text" name="name"><br>
				<p>Image du produit</p>
				<input class="form_category_input" type="text" name="img"><br>
				<p>Prix du produit</p>
				<input class="form_category_input" type="number" name="price" min="1" value="1"><br>
				<p>Description</p>
				<textarea class="form_category_input" name="desc" rows="10" cols="50"></textarea><br>
				<?php
				$categories = get_categories(0);
					foreach ($categories as $key => $value)
					{
						echo $value["name"].":<input type='checkbox' name='cat_".$value["id"]."'>";
					}
				?>
				<input class="form_category_input" type="submit" name="submit" value="Créer le produit">
				<input type="hidden" name="explore" value="search">
			</form>
			<hr/>
			<h2>Modifier un produit</h2>
			<?php
				if (!($db = db_connect()))
					exit(db_error($db));
				$req = "SELECT * FROM products";
				if (!($res = mysqli_query($db, $req)))
					exit(db_error($db));
				while ($row = mysqli_fetch_assoc($res))
				{
					echo
					"<form class='form_category' action='/controller/modif_product.php' method='POST'>
						<p>Nom du produit</p>
						<input class='form_category_input' type='text' name='name' value='".$row["name"]."'><br>
						<p>Image du produit</p>
						<input class='form_category_input' type='text' name='img' value='".$row["img"]."'><br>
						<p>Prix du produit</p>
						<input class='form_category_input' type='number' name='price' min='1' value='".$row["price"]."'><br>
						<p>Description</p>
						<textarea class='form_category_input' name='desc' rows='10' cols='50'>".$row["description"]."</textarea><br>";
					$categories = get_categories(0);
					foreach ($categories as $key => $value)
					{
						echo $value["name"].":<input id='cat_".$row["id"]."_".$value["id"]."' type='checkbox' name='cat_".$value["id"]."'>";
						if (prod_has_cat($row["id"], $value["id"]))
						{
							echo 
							"<script>
								document.getElementById(\"cat_".$row["id"]."_".$value["id"]."\").checked = true;
							</script>";
						}
					}
					echo	"<div class='form_category_button'>
							<input type='submit' name='modif' value='Appliquer les modifications'>
							<input type='submit' name='delete' value='Supprimer le produit'>
						</div>
						<input type='hidden' name='id' value='".$row["id"]."'>
					</form>
					<hr/>";
				}
				mysqli_free_result($res);
				mysqli_close($db);
			?>
		</center>
		</div>
		<footer>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/footer.php"); ?>
		</footer>
	</body>
</html>
