<?php
	include($_SERVER['DOCUMENT_ROOT']."/config.php");
	function db_connect() 
	{
		
		$db = get_config();

		$mysqli = mysqli_connect($db["host"], $db["user"], $db["password"], "minishop");
		if (mysqli_connect_errno())
		{
		    printf("Échec de la connexion : %s<br/>\n", mysqli_connect_error());
		    return (false);
		}
		return ($mysqli);
	}

	function db_error($mysqli, $a = false)
	{
		printf("Erreur : %s\n", mysqli_error($mysqli));
		if ($mysqli)
			mysqli_close($mysqli);
		return ($a);
	}
?>