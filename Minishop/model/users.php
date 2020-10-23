<?php
	require_once("db.php");
	session_start();
	function create_user($login, $password, $address, $city, $tel)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$login = mysqli_real_escape_string($db, $login);
		$address = mysqli_real_escape_string($db, $address);
		$city = mysqli_real_escape_string($db, $city);
		$tel = mysqli_real_escape_string($db, $tel);
		$password = hash("whirlpool" , mysqli_real_escape_string($db, $password));
		$req = "INSERT INTO users VALUES (NULL, '$login', '$password', '$address', '$city', '$tel', 0)";
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function delete_user($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "DELETE FROM users WHERE id=".(int)$id;
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function modif_user_password($id, $password)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$password = hash("whirlpool" , mysqli_real_escape_string($db, $password));
		$req = "UPDATE users SET password='$password' WHERE id=".(int)$id;
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function user_exists($login)
	{
		if (!($db = db_connect()))
			return (db_error($db, true));
		$login = mysqli_real_escape_string($db, $login);
		$req = "SELECT * FROM users";
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db, true));
		while ($row = mysqli_fetch_assoc($res))
		{
			if ($row["login"] == $login)
			{
				mysqli_free_result($res);
				mysqli_close($db);
				return (true);
			}		
	    }
		mysqli_free_result($res);
		mysqli_close($db);
		return (false);
	}

	function user_is_admin($login)
	{
		$db = db_connect();
		$login = mysqli_real_escape_string($db, $login);
		$req = "SELECT * FROM users WHERE login='".$login."'";
		$res = mysqli_query($db, $req);
		while ($row = mysqli_fetch_assoc($res))
		{
			if ($row["login"] == $login)
			{
				$a = (int)$row["admin"];
				return ($a);
			}
		}
		mysqli_free_result($res);
		mysqli_close($db);
		return (0);
	}

	function auth($login, $password)
	{
		$db = db_connect();
		$login = mysqli_real_escape_string($db, $login);
		$req = "SELECT * FROM users WHERE login='".$login."'";
		$res = mysqli_query($db, $req);
		while ($row = mysqli_fetch_assoc($res))
		{
			if ($row["login"] == $login)
			{
				if (hash("whirlpool", $password) == $row["password"])
				{
					$_SESSION["login"] = $login;
					$_SESSION["admin"] = user_is_admin($login);
					$_SESSION["id"] = $row["id"];
					mysqli_free_result($res);
					mysqli_close($db);
					return (true);
				}
				mysqli_free_result($res);
				mysqli_close($db);
				return (false);
			}
		}
		mysqli_free_result($res);
		mysqli_close($db);
		return (false);
	}

	function is_connected()
	{
		if (!isset($_SESSION["login"]) || $_SESSION["login"] == "")
			return (false);
		return (true);
	}

	function is_admin()
	{
		if (!is_connected() || !isset($_SESSION["admin"]) || $_SESSION["admin"] === 0)
			return (false);
		return (true);
	}
?>