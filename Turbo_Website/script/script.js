function getId(id)
{
	return document.getElementById(id);
}

function getTag(id, all)
{
	if(all)
	{
		return document.getElementsByTagName(id);
	}
	else
	{
		return document.getElementsByTagName(id)[0];
	}
}

function getClass(id, all)
{
	if(all)
	{
		return document.getElementsByClassName(id);
	}
	else
	{
		return document.getElementsByClassName(id)[0];
	}
}