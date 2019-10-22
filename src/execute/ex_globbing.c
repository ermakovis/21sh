#include "msh.h"

static bool ex_glob_btrack(char *str, char *pat, char *b_str, char *b_pat)
{
	if (*str == 0 || !b_pat)
		return (false);
	return (ex_globbing(b_str + 1, b_pat, b_str + 1, b_pat));
}

static bool ex_glob_liter(char *str, char *pat, char *b_str, char *b_pat)
{
	if (*str == *pat)
	{
		if (*str == 0)
			return (true);
		return (ex_globbing(str + 1, pat + 1, b_str, b_pat));
	}
	ex_glob_btrack(str, pat, b_str, b_pat);
}

static bool	ex_glob_quote(char *str, char *pat, char *b_str, char *b_pat)
{
	char	cmp;

	cmp = *pat++;
	while (*pat == *str && *pat != cmp)
	{
		str++;
		pat++;
	}
	if (*pat == cmp)
		return (ex_globbing(str, pat + 1, b_str, b_pat));
	if (*str != *pat)
		return (ex_glob_btrack(str, pat, b_str, b_pat));
}

static bool ex_glob_class(char *str, char *pat, char *b_str, char *b_pat)
{
	bool	match;
	bool	exclam;
	char	*start;
	char	*end;

	match = false;
	exclam = (*pat == '!');
	start = pat + exclam;
	while (*start && *start != ']')
	{
		if (!(end = start))
			return (ex_glob_liter(str, pat, b_str, b_pat));
		if (*(start + 1) == '-' && *(start + 2) != ']')
			if (!(end = start + 2))
				return (ex_glob_liter(str, pat, b_str, b_pat));
		match |= (*start <= *str && *str <= *end);
		start = end + 1;
	}
	if (match == exclam)
		return (ex_glob_btrack(str, pat, b_str, b_pat));
	return (ex_globbing(str + 1, start + 1, b_str, b_pat));
}

bool		ex_globbing(char *str, char *pat, char *b_str, char *b_pat)
{
	if (*pat == '?' && *str == 0)
		return (false);
	if ((*pat == '*' && *(pat + 1) == 0) || (*pat == *str && !*str))
		return (true);
	if (*pat == '?')
		return (ex_globbing(str + 1, pat + 1, b_str, b_pat));
	if (*pat == '*')
		return (ex_globbing(str, pat + 1, str, pat + 1)); 
	if (*pat == '[')
		return (ex_glob_class(str, pat + 1, b_str, b_pat));
	if (*pat == '\"' || *pat == '\'')
		return (ex_glob_quote(str, pat, b_str, b_pat));
	if (*pat == '\\')
		pat++;
	return (ex_glob_liter(str, pat, b_str, b_pat));
}
