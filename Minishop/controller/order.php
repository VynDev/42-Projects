<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
	require_once($_SERVER['DOCUMENT_ROOT']."/model/orders.php");
	if (!is_connected())
	{
		echo "Vous devez être connecté pour valider votre panier<br/>";
		?>
		<form action="../index.php" method="POST">
			<input type="submit" name="submit" value="Retourner a l'accueil pour se connecter">
		</form>
		<?php
		exit();
	}
	if (!isset($_POST["submit"]))
	{
		echo "<p>Veuillez réessayer</p><br/>";
		exit();
	}
	echo "OK<br/>";
	if (!isset($_SESSION["bascket"]) || count($_SESSION["bascket"]) == 0)
	{
		echo "<p>Votre panier est vide</p><br/>";
		exit();
	}
	create_order($_SESSION["id"], $_SESSION["bascket"]);
	unset($_SESSION["bascket"]);
	$_SESSION["bascket_msg"] = "Votre commande a été validé avec succès";
	header("Location: /view/bascket.php");
?>