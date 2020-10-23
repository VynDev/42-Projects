<?php
	require_once("db.php");
	function create_order($id_user, $order)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$login = mysqli_real_escape_string($db, $login);
		$password = hash("whirlpool" , mysqli_real_escape_string($db, $password));
		$req = "INSERT INTO orders VALUES (NULL, '$id_user', '".serialize($order)."')";
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function delete_order($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "DELETE FROM orders WHERE id=".(int)$id;
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function get_orders($limit)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT orders.id , orders.id_user, orders.products, users.login FROM orders, users WHERE orders.id_user=users.id;";
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db));
		$array;
		while ($row = mysqli_fetch_assoc($res))
		{
			$array[] = $row;	
	    }
		mysqli_free_result($res);
		mysqli_close($db);
		return ($array);
	}

	function get_order_byid($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT orders.id , orders.id_user, orders.products, users.login, users.address, users.city, users.tel FROM orders, users WHERE orders.id_user=users.id AND orders.id=".(int)$id;
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db));
		if (mysqli_num_rows($res) == 1)
		{
			$a = mysqli_fetch_assoc($res);
			mysqli_free_result($res);
			mysqli_close($db);
			$a["products"] = unserialize($a["products"]);
			return ($a);
		}
		mysqli_free_result($res);
		mysqli_close($db);
		return (false);
	}

?>