#include "msh.h"

#define BIN_FC_LIST (1 << 1)
#define BIN_FC_LIST_NONUM (1 << 2)
#define BIN_FC_REV (1 << 3)
#define BIN_FC_NOEDIT (1 << 4)

int		bin_fc(t_list *list)
{
	int		flags;
	char	**tokens;
	t_list	*history;
	
	ex_tokens(&tokens, list);
	if (ft_parse_options("elnrs", tokens, &flags) == -1)
		return (bin_print_error("usage: fc [-lnr] [-e name] [first] [last]",\
			"fc", &tokens));	
	//validate editor name
	if (bin_fc_list(tokens, &history) == -1)
		return (bin_print_error("history specification out of range",\
			"fc", &tokens));
	return (BIN_SUCCESS);
	
	

}
