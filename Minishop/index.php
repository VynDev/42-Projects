<?php
	session_start();
	require_once("model/products.php");
	require_once("model/categories.php");
?>
<!DOCTYPE html>
<html>
	<head>
		 <?php include($_SERVER['DOCUMENT_ROOT']."/part/head.php"); ?>
		 <style>
		 	<?php
		 		if ($_SESSION["login"])
		 			echo "#login_create
				 	{
				 		display: none;
				 	}";
		 	?>
		 </style>
	</head>
	<body>
		<header>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/header.php"); ?>
		</header>
		<form action='index.php' method='GET' class='category_selector'>
			<select name='category'>
				<option value=''>Tous</option>
				<?php
					$categories = get_categories(0);
					foreach ($categories as $key => $value)
					{
						echo "<option value='".$value["id"]."'>".$value["name"]."</option>";
					}
				?>
				<input type="submit" name="submit" value="Filtrer">
			</select>
		</form>
		<div class="content" id="products_login">
				<div id="products">
					<?php
						if (isset($_GET["category"]) && $_GET["category"] != "")
							$products = get_products_bycat($_GET["category"]);
						else
							$products = get_products(0);
						foreach ($products as $key => $value)
						{
							echo "<div class=\"product\">";
							echo "<a href='/view/product.php?id=".$value["id"]."'><img src='".$value["img"]."' alt='Image' title='Image'></a>";
							echo "<a class='product_name' href='/view/product.php?id=".$value["id"]."'>".$value["name"]."</a>";
							echo "</div>";
						}
					?>
				</div>
				<div id="login_create">
					<div id="connection">
						<form action="controller/login.php" method="POST">
							<label>Identifiant:</label><input type="text" name="login"><br/>
							<label>Mot de passe:</label><input type="password" name="password"><br/>
							<input type="submit" name="submit" value="Connexion">
						</form>
						<?php
							if (isset($_SESSION["login_msg"]) && $_SESSION["login_msg"] != "")
							{
								echo "<p class=\"perror\">".$_SESSION["login_msg"]."<p>";
								$_SESSION["login_msg"] = "";
							}
						?>
					</div>
					<hr/>
					<div id="create">
						<form action="controller/create.php" method="POST">
							<label>Identifiant:</label><input type="text" name="login"><br/>
							<label>Adresse:</label><input type="text" name="address"><br/>
							<label>Ville:</label><input type="text" name="city"><br/>
							<label>Téléphone:</label><input type="text" name="tel"><br/>
							<label>Mot de passe:</label><input type="password" name="password"><br/>
							<label>Confimer mot de passe:</label><input type="password" name="c_password"><br/>
							<input type="submit" name="submit" value="Confirmer">
						</form>
						<?php
							if (isset($_SESSION["create_msg"]) && $_SESSION["create_msg"] != "")
							{
								echo "<p class=\"perror\">".$_SESSION["create_msg"]."<p>";
								$_SESSION["create_msg"] = "";
							}	
						?>
					</div>
				</div>
		</div>
		<footer>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/footer.php"); ?>
		</footer>
	</body>
</html>