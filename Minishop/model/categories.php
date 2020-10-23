<?php
	require_once("db.php");

	function create_category($name, $desc)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$name = mysqli_real_escape_string($db, $name);
		$desc = mysqli_real_escape_string($db, $desc);
		$req = "INSERT INTO categories VALUES (NULL, '$name', '$desc')";
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function delete_category($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "DELETE FROM categories WHERE id=".(int)$id;
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function modif_category($id, $name, $desc)
	{
		if (!($db = db_connect()))
			return (db_error($db, true));
		$req = "SELECT * FROM categories";
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db, true));
		while ($row = mysqli_fetch_assoc($res))
		{
			if ($row["id"] == $id)
			{
				if (!($db = db_connect()))
					return (db_error($db));
				$name = mysqli_real_escape_string($db, $name);
				$desc = mysqli_real_escape_string($db, $desc);
				$req = "UPDATE categories SET name='".$name."', description='".$desc."' WHERE id=".$id;
				echo $req."<br/>";
				if (!mysqli_query($db, $req))
					return (db_error($db));
				mysqli_close($db);
				return (true);
			}		
	    }
		mysqli_free_result($res);
		mysqli_close($db);
		return (false);
	}

	function category_exists($name)
	{
		if (!($db = db_connect()))
			return (db_error($db, true));
		$name = mysqli_real_escape_string($db, $name);
		$req = "SELECT * FROM categories";
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db, true));
		while ($row = mysqli_fetch_assoc($res))
		{
			if ($row["name"] == $name)
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

	function get_categories($limit)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT * FROM categories";
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

	function get_category_byid($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT * FROM categories WHERE id=".$id;
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db));
		if (mysqli_num_rows($res) == 1)
		{
			$a = mysqli_fetch_assoc($res);
			mysqli_free_result($res);
			mysqli_close($db);
			return ($a);
		}
		mysqli_free_result($res);
		mysqli_close($db);
		return (false);
	}
?>