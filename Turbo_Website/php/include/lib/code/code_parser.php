<?php
/*
	More Special Character Stuff
	\t tab (HT, TAB)
	\n newline (LF, NL)
	\r return (CR)
	\f form feed (FF)
	\a alarm (bell) (BEL)
	\e escape (think troff) (ESC)
	\033 octal char (think of a PDP-11)
	\x1B hex char
	\c[ control char
	\l lowercase next char (think vi)
	\u uppercase next char (think vi)
	\L lowercase till \E (think vi)
	\U uppercase till \E (think vi)
	\E end case modification (think vi)
	\Q quote (disable) pattern metacharacters till \E

	Even More Special Characters
	\w Match a "word" character (alphanumeric plus "_")
	\W Match a non-word character
	\s Match a whitespace character
	\S Match a non-whitespace character
	\d Match a digit character
	\D Match a non-digit character
	\b Match a word boundary
	\B Match a non-(word boundary)
	\A Match only at beginning of string
	\Z Match only at end of string, or before newline at the end
	\z Match only at end of string
	\G Match only where previous m//g left off (works only with /g)

	Special Character Definitions
	\ Quote the next metacharacter
	^ Match the beginning of the line
	. Match any character (except newline)
	$ Match the end of the line (or before newline at the end)
	| Alternation
	() Grouping
	[] Character class
	* Match 0 or more times
	+ Match 1 or more times
	? Match 1 or 0 times
	{n} Match exactly n times
	{n,} Match at least n times
	{n,m} Match at least n but not more than m times
	[abc]     A single character: a, b or c
	[^abc]     Any single character but a, b, or c
	[a-z]     Any single character in the range a-z
	[a-zA-Z]     Any single character in the range a-z or A-Z
	(...)     Capture everything enclosed
	(a|b)     a or b
	a?     Zero or one of a
	a*     Zero or more of a
	a+     One or more of a
	a?		Zero or one of a
	a{3}     Exactly 3 of a
	a{3,}     3 or more of a
	a{3,6}     Between 3 and 6 of a
*/
	class CodeHighlighter
	{
		private $preprocessor 	= '%^#.*%';
		private $html 			= '#(<!--.*->)#';
		private $ini 			= '#;.*\n#';
		private $tex 			= '#%.*(\n|%)#';
		private $py 			= '#(\#.*\n|\'{3}.*\'{3})#';
		private $c				= '#/(\*)?.*(\*)?/#';
		private $operator 		= '#(\.|,|:|;|=|\+|\-|\*|~|\^|\||&|%|\?|!|<|>|\(|\)|\[|\]|\{|\})+#';
		private $number 		= '#\b(0x([A-F]|[0-9])*|[0-9]+\.)?[0-9]+\b#';
		private $string			= '#"[^"]*"#';
		private $char			= '#\'[^\']*\'#';

		private $tags 		= array	(
										"docu"			=> "DOCU__",
										"line"			=> "LINE__",
										"comment"		=> "COMMENT__",
										"multiComment"	=> "MULTICOMMENT__",
										"operator"		=> "OPERATOR__",
										"preprocessor"	=> "PREPROCESSOR__",
										"string"		=> "STRING__",
										"char"			=> "CHAR__",
										"number"		=> "NUMBER__",
										"type"			=> "TYPE__",
										"customType"	=> "CUSTOMTYPE__",
										"keyword"		=> "KEYWORD__",
										"special"		=> "SPECIAL__"
									);

		private $languages 	= array	(
										"C" 			=> 	array	(
																		"file" 			=> "#.*(\.c|\.h)#",
																		"keyword" 		=> "#\b("
																							. "(c(ase|on(st|tinue)))|"
																							. "(d(efault|o))|"
																							. "(e(lse|num|xtern))|"
																							. "(f(alse|or))|"
																							. "(n(amespace|ew))|"
																							. "(re(gister|turn))|"
																							. "(s(izeof|t(atic|ruct)|witch))|"
																							. "(t(rue|ypedef))|"
																							. "(auto|break|goto|if|union|volatile|while)"
																						 . ")\b#",
																		"type" 			=> "#\b(bool|char|double|float|int|long|s(hort|igned)|unsigned|vo(id|latile))\b#",
																		"customType" 	=> "",
																		"lineComment"	=> "#//.*\n#",
																		"multiComment"	=> array("#/\*#", "#\*/#"),
																		"special"		=> "%#.*\n%"
																	),
										"C++" 			=> 	array	(
																		"file" 			=> "#.*(\.c|\.cpp|\.cc|\.h\|\.hpp|\.hh)#",
																		"keyword" 		=> "#\b("
																							. "(a(nd(_eq)?|lign(as|of)|sm|uto))|"
																							. "(b(it(and|or)|reak))|"
																							. "(c(a(se|tch)|lass|o(mpl|n(st(_cast|expr)?|tinue))))|"
																							. "(d(e(cltype|fault|lete)|o|ynamic_cast))|"
																							. "(e(lse|num|x(p(licit|ort)|tern)))|"
																							. "(f(alse|inal|or|riend))|"
																							. "(i(f|nline))|"
																							. "(n(amespace|ew|o(t(_eq)?|except)|ullptr))|"
																							. "(o(perator|r(_eq)?|verride))|"
																							. "(p(r(ivate|otected)|ublic))|"
																							. "(re(gister|interpret_cast|turn))|"
																							. "(s(izeof|t(atic(_(cast|assert))?|ruct)|witch))|"
																							. "(t(emplate|h(is|r(ead_local|ow))|r(ue|y)|ype(def|id|name)))|"
																							. "(u(nion|sing))|"
																							. "(v(irtual|olatile))|"
																							. "(goto|mutable|xor(_eq)?|while)|"
																							. "(__(DATE|FILE|LINE|STDC(_VERSION)?|TIME)__)"
																						 . ")\b#",
																		"type" 			=> "#\b(bool|(w)?c(har(16|32)?(_t)?)|double|float|int|long|void)\b#",
																		"customType" 	=> "#\b(st(ring|d))\b#",
																		"lineComment"	=> "#//\b.*\n#",
																		"multiComment"	=> array("#/\*#", "#\*/#"),
																		"special"		=> "%^\#.*\n%"
																	),
										"PHP"			=>	array	(
																		"file" 			=> "#.*(\.php)#",
																		"keyword" 		=> "#\b("
																							. "(a(bstract|nd|rray|s))|"
																							. "(c(a(llable|se|tch)|l(ass|one)|on(st|tinue)))|"
																							. "(d(e(clare|fault)|ie|o))|"
																							. "(e(cho|lse(if)?|mpty|nd(declare|for(each)?|if|switch|while)|val|x(it|tends)))|"
																							. "(f(alse|inal|or(each)?|unction))|"
																							. "(g(lobal|oto))|"
																							. "(i(f|mplements|n(clude(_once)?|st(anceof|eadof)|terface)|sset))|"
																							. "(n(amespace|ew))|"
																							. "(p(r(i(nt|vate)|otected)|ublic))|"
																							. "(re(quire(_once)?|turn))|"
																							. "(s(tatic|witch))|"
																							. "(t(hrow|r(ait|rue|y)))|"
																							. "(u(nset|se))|"
																							. "(break|list|(x)?or|var|while)|"
																							. "(__(CLASS|DIR|F(ILE|UNCTION)|LINE|METHOD|NAMESPACE|TRAIT)__)"
																						 . ")\b#",
																		"type" 			=> "",
																		"customType"	=> "",
																		"lineComment"	=> "#//.*\n#",
																		"multiComment"	=> array("#/\*#", "#\*/#"),
																		"special"		=> ""
																	),
										"Python"		=>	array	(
																		"file" 			=> "#.*(\.py)#",
																		"keyword" 		=> "#\b("
																							. "(a(nd|s(sert)?))|"
																							. "(c(lass|ontinue))|"
																							. "(d(e(f|l)))|"
																							. "(e(l(se|if)|x(cept|ex)))|"
																							. "(f(inally|or|rom))|"
																							. "(i(f|mport|n|s))|"
																							. "(p(ass|rint))|"
																							. "(r(aise|eturn))|"
																							. "(w(hile|ith))|"
																							. "(break|global|lambda|not|or|try|yield)"
																						 . ")\b#",
																		"type" 			=> "#====#",
																		"customType"	=> "#====#",
																		"lineComment"	=> "%#.*\n%",
																		"multiComment"	=> array("#'{3}#", "#'{3}#"),
																		"special"		=> "#====#"
																	),
										"Java"			=>	array	(
																		"file" 			=> "#.*(\.java)#",
																		"keyword" 		=> "#\b("
																							. "(a(bstract|ssert))|"
																							. "(c(a(se|tch)|lass)|on(st|tinue)))|"
																							. "(d(efault|o))|"
																							. "(e(lse|num|xtends))|"
																							. "(f(inal(ly)?|or))|"
																							. "(i(f|m(plements|port)|n(stanceof|terface)))|"
																							. "(n(ative|ew|ull))"
																							. "(p(ackage|r(ivate|otected)|ublic)))|"
																							. "(s(t(rictfp|atic)|witch|uper|ynchronized))|"
																							. "(t(h(is|row(s)?)|r(ansient|ue|y)))|"
																							. "(break|goto|return|volatile|while)"
																						 . ")\b#",
																		"type" 			=> "#\b(b(oolean|yte)|char|double|float|int|long|short|void)\b#",
																		"customType"	=> "",
																		"lineComment"	=> "#//.*\n#",
																		"multiComment"	=> array("#/\*#", "#\*/#"),
																		"special"		=> ""
																	),
										"JavaScript"	=>	array	(
																		"file" 			=> "#.*(\.java)#",
																		"keyword" 		=> "#\b("
																							. "(a(bstract|rguments|wait))|"
																							. "(b(reak|yte))|"
																							. "(c(a(se|tch)|har|lass|on(st|tinue)))|"
																							. "(d(e(bugger|fault|lete|o(uble)?)))|"
																							. "(e(lse|num|val|x(port|tends)))|"
																							. "(f(alse|inal(ly)?|loat|or|unction))|"
																							. "(i(f|mp(lements|ort|n(stanceof|t(erface)?)?)))|"
																							. "(l(et|ong))|"
																							. "(n(ative|ew|ull))|"
																							. "(p(ackage|r(ivate|otected)|ublic))|"
																							. "(s(hort|tatic|uper|witch|ynchronized))|"
																							. "(t(h(is|r(ow(s)?|ansient|ue|y))|ypeof))|"
																							. "(v(ar|o(id|latile)))|"
																							. "(w(hile|ith))|"
																							. "(goto|return|yield)"
																						 . ")\b#",
																		"type" 			=> "",
																		"customType"	=> "",
																		"lineComment"	=> "#//.*\n#",
																		"multiComment"	=> array("#/\*#", "#\*/#"),
																		"special"		=> ""
																	)
									);

		public function __construct($file, $language = "C++")
		{
			if($file != "")
			{
				$this->filename = $file;
				$this->language = $language;
				$this->filetype = substr($file, strrpos($file, '.') + 1);
				$this->handle = fopen($this->filename, "r");

				fseek($this->handle, 0, SEEK_END);
				$this->size = ftell($this->handle);
				fseek($this->handle, 0, SEEK_SET);

				$this->buffer = fread($this->handle, $this->size);
				//$this->buffer = htmlspecialchars($this->buffer, ENT_QUOTES);
				fclose($this->handle);
			}
		}

		/*
			Takes an input string which represents the code file and converts the contents to
			html text with css tags.
			@lang : Code Language
			@text : Code content
		*/
		public function highlightCode($lang = "C++", $text = "")
		{
			$language 		= $this->languages[$lang];
			$code 			= "";
			$line_counter 	= 1;
			$lines			= array();
			$is_comment 	= false;

			if(@$text == "")
			{
				$lines = explode("\n", $this->buffer);
			}
			else
			{
				$lines = explode("\n", $text);
			}

			$code = $this->tagDocu($this->filename, count($lines));

			foreach($lines as $line)
			{
				$matches 		= array();
				$parsed_line 	= "";
				$line			.= "\n";

				if($is_comment)
				{
					if(preg_match($language["multiComment"][1], $line, $matches, PREG_OFFSET_CAPTURE))
					{
						$is_comment = false;
						$parsed_line = substr($line, 0, $matches[0][1] + strlen($matches[0][0]));
						$parsed_line .= "</" . $this->tags["multiComment"] . ">" . substr($line, $matches[0][1] + strlen($matches[0][0]));
						$code .= preg_replace(array('# {2}#', '#\t#'),
									  array("&nbsp;&nbsp;", "&nbsp;&nbsp;&nbsp;&nbsp;"),
									  $parsed_line);
						$code .= $this->tagLine($line_counter, "line");
						$code .= "<br>";
						$line_counter++;
						$line = $parsed_line;
						$parsed_line = "";
						continue;
					}
					else
					{
						$code .= preg_replace(array('# {2}#', '#\t#'),
									  array("&nbsp;&nbsp;", "&nbsp;&nbsp;&nbsp;&nbsp;"),
									  $line);
						$code .= $this->tagLine($line_counter, "line");
						$code .= "<br>";
						$line_counter++;
						continue;
					}
				}
				if(preg_match($language["special"], $line, $matches, PREG_OFFSET_CAPTURE))
				{
					$parsed_line = $this->tagLine($line, "special");
					$line = $parsed_line;
					$parsed_line = "";
				}
				else if(preg_match($language["lineComment"], $line, $matches, PREG_OFFSET_CAPTURE))
				{
					$parsed_line = $this->tagLine($line, "comment");
					$line = $parsed_line;
					$parsed_line = "";
				}
				else if(preg_match($language["multiComment"][0], $line, $matches, PREG_OFFSET_CAPTURE))
				{
					$is_comment = true;
					$line = substr($line, 0, $matches[0][1]) . "<" . $this->tags["multiComment"] . ">"
						  . substr($line, $matches[0][1], $matches[0][1] + strlen($matches[0][0]) + 1);
				}
				else
				{
					if(preg_match_all($this->operator, $line, $matches, PREG_OFFSET_CAPTURE))
					{
						$line = $this->tagLineMatches($line, $matches, "operator");
					}
					if(preg_match_all($this->number, $line, $matches, PREG_OFFSET_CAPTURE))
					{
						$line = $this->tagLineMatches($line, $matches, "number");
					}
					if(preg_match_all($language["keyword"], $line, $matches, PREG_OFFSET_CAPTURE))
					{
						$line = $this->tagLineMatches($line, $matches, "keyword");
					}
					if(preg_match_all($language["type"], $line, $matches, PREG_OFFSET_CAPTURE))
					{
						$line = $this->tagLineMatches($line, $matches, "type");
					}
					if(preg_match_all($language["customType"], $line, $matches, PREG_OFFSET_CAPTURE))
					{
						$line = $this->tagLineMatches($line, $matches, "customType");
					}
					if(preg_match_all($this->string, $line, $matches, PREG_OFFSET_CAPTURE))
					{
						$line = $this->tagLineMatches($line, $matches, "string");
					}
					if(preg_match_all($this->char, $line, $matches, PREG_OFFSET_CAPTURE))
					{
						$line = $this->tagLineMatches($line, $matches, "char");
					}
				}
				$code .= preg_replace(array('# {2}#', '#\t#'),
									  array("&nbsp;&nbsp;", "&nbsp;&nbsp;&nbsp;&nbsp;"),
									  $line);
				$code .= $this->tagLine($line_counter, "line");
				$code .= "<br>";
				$line_counter++;
			}
			return $code;
		}

		public function cutTags($line)
		{
			if(substr_count($line, '<') == 2)
			{
				return substr($line, strpos($line, '>') + 1, strrpos($line, '<') - strpos($line, '>'));
			}
			else
			{
				return $line;
			}
		}

		public function tagDocu($filename, $lines)
		{
			$filename = str_replace("\\", "/", $filename);
			if(strrpos($filename, "/") > 0)
			{
				$filename = substr($filename, strrpos($filename, "/") + 1);
			}
			$docu = ""
				. "<docu>"
					. "File: " . $filename
					. " [<u>" . $lines . " Lines</u>]"
				. "</docu>"
				. "<margin></margin><br>";
			return $docu;
		}

		public function tagLine($line, $tag)
		{
			return "<" . $this->tags[$tag] . ">" . $line . "</" . $this->tags[$tag] . ">";
		}

		public function tagLineMatches($line, $matches, $tag)
		{
			$parsed_line = "";
			$prefix_pos = 0;
			foreach($matches[0] as $match => $pos)
			{
				if($pos[1] != 0)
				{
					$parsed_line .= substr($line, $prefix_pos, $pos[1] - $prefix_pos);
				}
				$parsed_line .= "<" . $this->tags[$tag] . ">" . substr($line, $pos[1], strlen($pos[0])) . "</" . $this->tags[$tag] . ">";
				$prefix_pos = $pos[1] + strlen($pos[0]);
			}
			$parsed_line .= substr($line, $prefix_pos);
			return $parsed_line;
		}

		public function tagWord($word, $tag, $keys = null, $values = null)
		{
			$string = "";

			if(!empty($tag) && !empty($word))
			{
				$string .= "<" . $tag;

				if(!empty($values) && !empty($keys) && (count($values) == count($keys)))
				{
					for($i = 0; $i < count($values); $i++)
					{
						$string .= " " . $keys[$i] . "='" . $values[$i] . "'";
                        if($i != count($values) - 1)
							$string .= " ";
					}
				}
				$string .= ">" . $word . "</" . $tag . ">";
			}
			return $string;
		}

		public function color($word, $value)
		{
			if(!empty($word) && !empty($value))
			{
				return "<font color='" . $value . "'>" . $word . "</font>";
			}
		}
	}
?>