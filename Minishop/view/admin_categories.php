<?php
	session_start();
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
			<h2>Créer une catégorie</h2>
			<form class='form_category' action="/controller/create_category.php" method="POST">
				<p>Nom de la catégorie</p>
				<input class="form_category_input" type="text" name="name"><br>
				<p>Description</p>
				<textarea class="form_category_input" name="desc" rows="10" cols="50"></textarea><br>
				<input class="form_category_input" type="submit" name="submit" value="Créer la catégorie">
				<input type="hidden" name="explore" value="search">
			</form>
			<hr/>
			<h2>Modifier une catégorie</h2>
			<?php
				if (!($db = db_connect()))
					exit(db_error($db));
				$req = "SELECT * FROM categories";
				if (!($res = mysqli_query($db, $req)))
					exit(db_error($db));
				while ($row = mysqli_fetch_assoc($res))
				{
					echo
					"<form class='form_category' action='/controller/modif_category.php' method='POST'>
						<p>Nom de la catégorie</p>
						<input class='form_category_input' type='text' name='name' value='".$row["name"]."'><br>
						<p>Description</p>
						<textarea class='form_category_input' name='desc' rows='10' cols='50' value>".$row["description"]."</textarea><br>
						<div class='form_category_button'>
							<input type='submit' name='modif' value='Appliquer les modifications'>
							<input type='submit' name='delete' value='Supprimer la catégorie'>
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
