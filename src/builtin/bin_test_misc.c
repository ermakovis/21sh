#include "msh.h"

int		bin_test_return(int code, char ***tokens)
{
	if (tokens && *tokens)
		ft_free_table(tokens);
	return (code);
}

int		bin_test_error(char *var, char *message, char ***tokens)
{
	if (message)
		ft_dprintf(2, "%s: test: %s: %s\n", g_msh->shell_name, var, message);
	if (tokens && *tokens)
		ft_free_table(tokens);
	return (2);
}

int		bin_test_get_unary(char *arg, int *flag)
{
	int	shift;

	shift = 0;
	if (arg[0] != '-')
		return (0);
	if (!arg[1])
		return (0);
	if ((shift = ft_strchrlen(BIN_TEST_UN_OPTIONS, arg[1])) == -1)
		return (0);
	*flag |= (1 << shift);
	return (1);
}

static int bin_test_get_binary_return(int *flag, int shift)
{
	*flag |= shift;
	return (1);
}

int		bin_test_get_binary(char *arg, int *flag)
{
	if (ft_strequ(arg, "="))
		return (bin_test_get_binary_return(flag, BIN_TEST_STR_EQU));
	if (ft_strequ(arg, "!="))
		return (bin_test_get_binary_return(flag, BIN_TEST_STR_NEQU));
	if (ft_strequ(arg, "-eq"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_EQU));
	if (ft_strequ(arg, "-ne"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_NEQU));
	if (ft_strequ(arg, "-gt"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_GT));
	if (ft_strequ(arg, "-ge"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_GE));
	if (ft_strequ(arg, "-lt"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_LT));
	if (ft_strequ(arg, "-le"))
		return (bin_test_get_binary_return(flag, BIN_TEST_INT_LE));
	return (0);
}
