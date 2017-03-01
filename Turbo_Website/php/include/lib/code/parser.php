<?php
/*
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
	[abc]     A single character: a, b or c
	[^abc]     Any single character but a, b, or c
	[a-z]     Any single character in the range a-z
	[a-zA-Z]     Any single character in the range a-z or A-Z

	^     Start of line
	$     End of line
	\A     Start of string
	\z     End of string
	.     Any single character
	\s     Any whitespace character
	\S     Any non-whitespace character
	\d     Any digit
	\D     Any non-digit
	\w     Any word character (letter, number, underscore)
	\W     Any non-word character
	\b     Any word boundary character
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

// priority string | comment | preprocessor

	$defaults = array( "cpp" 	=> array( 	"keywords" 	=> "(break|case|class|continue|const|default|do|else|enum|for|if|include|namespace|private|protected|public|return|static|struct|switch|using|while)",
											"types" 	=> "(bool|char|double|float|int|string|void)"),
						"c"		=> array( 	"keywords" 	=> "(break|case|class|continue|const|default|do|else|enum|for|if|include|return|static|struct|switch|while)",
											"types" 	=> "(bool|char|double|float|int|string|void)"),
						"h" 	=> array( 	"keywords" 	=> "(break|case|class|continue|const|default|do|else|enum|for|if|include|namespace|private|protected|public|return|static|struct|switch|using|while)",
											"types" 	=> "(bool|char|double|float|int|string|void)"),
						"php" 	=> array( 	"keywords" 	=> "(break|case|class|continue|default|do|else|for|foreach|if|include|return|require|switch|while)",
											"types" 	=> "()"),
						"js" 	=> array( 	"keywords" 	=> "(break|case|continue|default|do|else|for|if|return|switch|while)",
											"types" 	=> "()"),
						"java" 	=> array( 	"keywords" 	=> "(break|case|continue|default|do|else|for|final|if|return|switch|static|while)",
											"types" 	=> "(boolean|char|double|float|int|string|void)"),
						"py" 	=> array( 	"keywords" 	=> "(break|case|class|continue|default|do|else|elif|for|if|return|switch|while)",
											"types" 	=> "()")
					);

	class CodeParser
	{
		private $brackets = '\(\)\[\]\{\}';
		private $signs = '\.,:;=+\-\*~\^\|&%?!<>';
		private $operator = '';
		private $commentLine = '#\/\/.*\n#';
		private $commentMultiLine = '#\/\*.*\*\/#';

		//private $string = '#(?:(?:"(?:\\"|[^"])+")|(?:\'(?:\\\'|[^\'])+\'))#';

		private $preprocessor = '%^#.*%';
		private $comment = '/((?:\/\*(?:[^*]|(?:\*+[^*\/]))*\*+\/)|(?:\/\/.*))/'; //'#\/[\/|\*].*(\*\/)?#'
		private $number = '#[0-9]*#';
		private $string	= '#".*"#';
		private $char	= '#\'.*\'#';
		private $type = '#\b(bool|char|double|float|int|string|void)\b#';
		private $customType = '#\b(XML|Config|EventSignal|app_state|log_state|timer_state|render_state|music_state|file_state|BlendType|RendererFlipType|FontRenderType|EventType|EventType|ObserverType|TextureType|XMLType|LayerType|Uint32|Sint16|int32_t)\b#';
		private $keyword = '#\b(break|case|class|continue|const|default|do|else|enum|for|if|include|namespace|private|protected|public|return|static|struct|switch|using|while)\b#';

		public function __construct($file)
		{
			if($file != "")
			{
				$this->filename = $file;
				$this->filetype = substr($file, strrpos($file, '.') + 1);
				$this->handle = fopen($this->filename, "r");

				fseek($this->handle, 0, SEEK_END);
				$this->size = ftell($this->handle);
				fseek($this->handle, 0, SEEK_SET);

				$this->buffer = fread($this->handle, $this->size);
				//$this->buffer = htmlspecialchars($this->buffer, ENT_QUOTES);
				fclose($this->handle);
			}
			$this->operator = '#[' . $this->brackets . $this->signs . ']#';
		}

		/* A function to do sth */
		public function highlightCode($text = "")
		{
			$echo = "";
			$i = 1;
			if(@$text == "")
				$lines = explode("\n", $this->buffer);
			else
				$lines = explode("\n", $text);
			$this->lines = count($lines);

			foreach($lines as $line)
			{
				$echo .= "<line>" . $i . "</line>";
				$parsedLine = "";
				$matches = array();
				if(preg_match($this->comment, $line, $matches, PREG_OFFSET_CAPTURE))
				{
					$parsedLine = $this->tagWord($line, "comment");
				}
				else if(preg_match($this->preprocessor, $line, $matches, PREG_OFFSET_CAPTURE))
				{
					$parsedLine = $this->tagWord($line, "preprocessor");
				}
				else
				{
					$mod = 0;
					$words = explode(" ", $line);
					foreach($words as $word)
					{
						$matches = array();
						if(preg_match($this->string, $word, $matches, PREG_OFFSET_CAPTURE))
						{
							foreach($matches as $match => $info)
							{
								$word = str_replace($info[0], $this->tagWord($info[0], "string"), $word);
							}
						}
						else if(preg_match($this->char, $word, $matches, PREG_OFFSET_CAPTURE))
						{
							foreach($matches as $match => $info)
							{
								$word = str_replace($info[0], $this->tagWord($info[0], "char"), $word);
							}
						}
						else
						{
							if(preg_match($this->keyword, $word, $matches, PREG_OFFSET_CAPTURE))
							{
								foreach($matches as $match => $info)
								{
									$word= str_replace($info[0], $this->tagWord($info[0], "keyword"), $word);
								}
							}
							else
							{
								if(preg_match($this->operator, $word, $matches, PREG_OFFSET_CAPTURE))
								{
									foreach($matches as $match => $info)
									{
										$word = str_replace($info[0], $this->tagWord($info[0], "operator"), $word);
									}
								}
								if(preg_match($this->number, $word, $matches, PREG_OFFSET_CAPTURE) || is_numeric($word))
								{
									foreach($matches as $match => $info)
									{
										$word = str_replace($info[0], $this->tagWord($info[0], "number"), $word);
									}
								}
								if(preg_match($this->type, $word, $matches, PREG_OFFSET_CAPTURE))
								{
									foreach($matches as $match => $info)
									{
										$word = str_replace($info[0], $this->tagWord($info[0], "type"), $word);
									}
								}
								if(preg_match($this->customType, $word, $matches, PREG_OFFSET_CAPTURE))
								{
									foreach($matches as $match => $info)
									{
										$word= str_replace($info[0], $this->tagWord($info[0], "customType"), $word);
									}
								}
							}
						}
						$word = str_replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;", $word);
						$parsedLine .= $word . "&nbsp;";
					}
				}
				$echo .= str_replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;", $parsedLine);
				$echo .= "<br>";
				$i++;
			}
			return $echo;
		}

		public function getLineCount()
		{
			return $this->lines;
		}

		public function cutTags($line)
		{
			if(substr_count($line, '<') == 2)
				return substr($line, strpos($line, '>') + 1, strrpos($line, '<') - strpos($line, '>'));
			else
				return $line;
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
				return "<font color='" . $value . "'>" . $word . "</font>";
		}
	}
?>