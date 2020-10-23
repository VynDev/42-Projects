<?php
	require_once("db.php");

	function create_product($name, $desc, $img, $price)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$name = mysqli_real_escape_string($db, $name);
		$desc = mysqli_real_escape_string($db, $desc);
		$img = mysqli_real_escape_string($db, $img);
		$price = mysqli_real_escape_string($db, $price);
		$req = "INSERT INTO products VALUES (NULL, '$name', '$desc', '$img', $price)";
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function delete_product($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "DELETE FROM products WHERE id=".(int)$id;
		if (!mysqli_query($db, $req))
			return (db_error($db));
		mysqli_close($db);
		return (true);
	}

	function modif_product($id, $name, $desc, $img, $price)
	{
		if (!($db = db_connect()))
			return (db_error($db, true));
		$req = "SELECT * FROM products";
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
				$img = mysqli_real_escape_string($db, $img);
				$price = mysqli_real_escape_string($db, $price);
				$req = "UPDATE products SET name='".$name."', description='".$desc."', img='".$img."', price=".$price." WHERE id=".$id;
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

	function product_exists($name)
	{
		if (!($db = db_connect()))
			return (db_error($db, true));
		$req = "SELECT * FROM products";
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

	function get_products($limit)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT * FROM products";
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

	function get_product_byid($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT * FROM products WHERE id=".$id;
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

	function get_products_bycat($id_cat)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT products.id, products.name, products.img, products.price FROM prod_cat, products WHERE prod_cat.id_product=products.id AND prod_cat.id_category=".(int)$id_cat;
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

	function get_product_byname($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT * FROM products WHERE name='".$id."'";
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db));
		if (mysqli_num_rows($res) == 1)
		{
			return (mysqli_fetch_assoc($res));
		}
		mysqli_free_result($res);
		mysqli_close($db);
		return (false);
	}

	function assoc_prod_cat($id_product, $list_cat, $post)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "DELETE FROM prod_cat WHERE id_product=".$id_product;
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db));
		foreach ($list_cat as $key => $value)
		{
			if (isset($post["cat_".$value["id"]]))
			{
				$req = "INSERT INTO prod_cat VALUES (NULL, ".$id_product.", ".$value["id"].")";
				$res = mysqli_query($db, $req);
				if (!$res)
					return (db_error($db));
			}	
		}
		mysqli_free_result($res);
		mysqli_close($db);
		return (true);
	}

	function get_prod_cat($id)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT * FROM prod_cat WHERE id_product=".$id;
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db));
		while ($row = mysqli_fetch_assoc($res))
		{
			$array[] = $row;	
	    }
		mysqli_free_result($res);
		mysqli_close($db);
		return ($array);
	}

	function prod_has_cat($id, $id_cat)
	{
		if (!($db = db_connect()))
			return (db_error($db));
		$req = "SELECT * FROM prod_cat WHERE id_product=".$id." AND id_category=".$id_cat;
		$res = mysqli_query($db, $req);
		if (!$res)
			return (db_error($db));
		while (mysqli_num_rows($res) == 1)
		{
			mysqli_free_result($res);
			mysqli_close($db);
			return (true);	
	    }
		mysqli_free_result($res);
		mysqli_close($db);
		return (false);
	}
?>