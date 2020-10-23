<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/categories.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/products.php");
	if (!is_connected())
		exit("Vous devez être connecté pour acceder à cette page");
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
				if (isset($_SESSION["account_msg"]))
				{
					echo "<p class='perror'>".$_SESSION["account_msg"]."</p><br/>";
					unset($_SESSION["account_msg"]);
				}
			?>
			<h2>Modifier mon mot de passe</h2>
			<form action="/controller/modif_account.php" method='POST'>
				<label>Nouveau mot de passe:</label><input type='password' name='password'><br/>
				<label>Confimer le mot de passe:</label><input type='password' name='c_password'><br/>
				<input type='submit' name='submit' value='Confirmer'>
				<input type='hidden' name='type' value='password'>
			</form>
			<h2>Supprimer mon compte</h2>
			<form action="/controller/modif_account.php" method='POST'>
				<input type='submit' name='submit' value='Supprimer le compte (Attention vous ne pourrez pas revenir en arrière)'>
				<input type='hidden' name='type' value='delete'>
			</form>
		</div>
		<footer>
			<?php include($_SERVER['DOCUMENT_ROOT']."/part/footer.php"); ?>
		</footer>
	</body>
</html>