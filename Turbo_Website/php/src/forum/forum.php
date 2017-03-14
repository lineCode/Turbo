<?php

	require_once("../../include/lib/db/database.php");
	require_once("../../include/lib/html/html.php");

	class Forum
	{
		private $forum_name		= "";
		private $db				= null;
		private $db_info		= array	(
											"db_host"	=> "localhost",
											"db_user"	=> "root",
											"db_pw"		=> "root",
											"db_name"	=> "forum_name"
										);

		public function __construct()
		{
			$this->db = new DB($db_info["db_host"], $db_info["db_user"],
							   $db_info["db_pw"], $db_info["db_name"]);
		}

		public function showMainPage()
		{

		}

		public function showTopicPage()
		{

		}

		public function showEntryPage()
		{

		}

		public function __destruct()
		{

		}
	}

	class User
	{
		private $user_name			= "";

		public function __construct()
		{

		}
	}

	class Section
	{
		private $section_id			= 0;
		private $section_name		= "";

		public function __construct()
		{

		}
	}

	class SubSection
	{
		private $sub_section_id		= 0;
		private $sub_section_name 	= "";

		public function __construct()
		{

		}
	}

	class Topic
	{
		private $topic_id			= 0;
		private $topic_name			= "";

		public function __construct()
		{

		}
	}

	class Entry
	{
		private $topic_id			= 0;
		private $topc_name			= "";

		public function __construct()
		{

		}
	}
?>