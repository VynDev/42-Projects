<?php
	session_start();
	require_once($_SERVER['DOCUMENT_ROOT']."/model/users.php");
?>
<span class="logo"><h1><a href="/index.php" >Minishop</a></h1></span>
<?php

if (is_connected())
{
	echo "<p id=\"plogin\">Connecté en tant que ".$_SESSION["login"];
	echo " | <a href='/view/bascket.php'>Panier</a>";
	echo " | <a href='/view/account.php'>Mon compte</a>";
	if (is_admin())
		echo " | <a href=\"/view/admin.php\">Admin zone</a>";
	echo " | <a class='deconnection' href=\"/controller/logout.php\">Déconnexion</a>";
	echo "</p>";
}
else
	echo "<p id=\"plogin\">Vous n'êtes pas connecté | <a href='/view/bascket.php'>Panier</a></p>";
?>