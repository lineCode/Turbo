<?php
	class HTML
	{
		public function __construct()
		{

		}

		public function script($file)
		{
			return "<script type='text/javascript' src='" . $file . "'></script>";
		}

		public function style($file)
		{
			return "<link rel='stylesheet' type='text/css' href='" . $file . "'/>";
		}

		public function cutQuery()
		{

		}

		public function element($tag, $content, $properties = null, $tagopen = 0)
		{
			$element = "<" . $tag;

			if($properties != null)
			{
				foreach($properties as $key => $value)
				{
					$element .= " " . $key . "='" . $value . "'";
				}
			}

			if($tagopen == 0)
				$element .= "</" . $tag . ">";
			else
				$element .= "/>";

			return $element;
		}

		/*
		 *	Creates a html table with the given values
		 */
		public function table($headers, $values, $alignment = null, $propeties = null)
		{
			$table = "<table>";

			if($alignment == null)
			{
				$alignment = array();
				foreach($headers as $header)
					array_push($alignment, "lc");
			}

			foreach($alignment as &$align)
			{
				if(strlen($align) == 1)
					$align .= "c";
				str_replace("l", " align='left'", $align[0]);
				str_replace("c", " align='center'", $align[0]);
				str_replace("r", " align='right'", $align[0]);
				str_replace("t", " valign='top'", $align[1]);
				str_replace("c", " valign='middle'", $align[1]);
				str_replace("b", " valign='bottom'", $align[1]);
			}

			$index = 0;
			foreach($headers as $header)
			{
				$table .= "<th" . $alignment[$index] . ">" . $header . "</th>";
				$index++;
			}

			foreach($values as $row => $col)
			{
				$index = 0;
				$table .= "<tr>";
				foreach($col as $c)
				{
					$table .= "<td" . $alignment[$index] . ">" . $header . "</td>";
					$index++;
				}
				$table .= "</tr>";
			}

			return $table . "</table>";
		}
	}
?>