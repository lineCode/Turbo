<?php
	require_once(dirname(__FILE__) . "/../../script/script.php");
	require_once(dirname(__FILE__) . "/../../lib/db/main.php");

	class Session
	{
		private $user = null;

		public function __construct()
		{
			$this->user	= new User();
			$this->user->setBrowser(getBrowserType());
			$this->user->setDevice(getDeviceType());
		}

		public function start($username = "Guest", $realname = "Guest")
		{
			$this->user->setUsername($username);
			$this->user->setRealname($realname);
			$dt 				= new DateTime("now");
			$this->user->setLogintime($dt->getTimestamp());
		}

		public function getUserObject()
		{
			return $this->user;
		}

		public function destory()
		{
			$this->user = new User();
		}
	}
?>