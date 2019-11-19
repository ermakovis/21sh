#include "msh.h"

static int	bin_test_one_arg(char **tokens, int i)
{
	if (tokens[i])
		return (bin_test_return(0, &tokens));
	return (bin_test_return(1, &tokens));
}

static int	bin_test_two_arg(char **tokens, int i)
{
	int	flag;
	int	ret;

	flag = 0;
	if (ft_strequ(tokens[i], "!") && i)
		return (bin_test_error("", BIN_TEST_ERR_TM, &tokens));
	if (ft_strequ(tokens[i], "!"))
		return (!bin_test_one_arg(tokens, 1));
	if (bin_test_get_unary(tokens[i], &flag))
	{
		ret = bin_test_unary(tokens[i + 1], flag);
		return (bin_test_return(ret, &tokens));
	}
	return (bin_test_error(tokens[i + 1], BIN_TEST_ERR_UN, &tokens));
}

static int	bin_test_three_arg(char **tokens, int i)
{
	int	flag;
	int	ret;

	flag = 0;
	if (bin_test_get_binary(tokens[i + 1], &flag))
	{
		ret = bin_test_binary(tokens[i], tokens[i + 2], flag);
		return (bin_test_return(ret, &tokens));
	}
	if (ft_strequ(tokens[i], "!") && i)
		return (bin_test_error("", BIN_TEST_ERR_TM, &tokens));
	if (ft_strequ(tokens[i], "!"))
		return (!bin_test_two_arg(tokens, 1));
	return (bin_test_error(tokens[i + 1], BIN_TEST_ERR_BIN, &tokens));
}

static int	bin_test_four_arg(char **tokens)
{
	if (ft_strequ(tokens[0], "!"))
		return (!bin_test_three_arg(tokens, 1));
	return (bin_test_error("", BIN_TEST_ERR_TM, &tokens));
}

int		bin_test(t_list *list)
{
	char	**tokens;
	int		count;

	if (!list || !list->next)
		return (1);
	ex_tokens(&tokens, list->next);	
	count = ft_table_size(tokens);
	if (count == 1)
		return (bin_test_one_arg(tokens, 0));
	if (count == 2)
		return (bin_test_two_arg(tokens, 0));
	if (count == 3)
		return (bin_test_three_arg(tokens, 0));
	if (count == 4)
		return (bin_test_four_arg(tokens));
	return (bin_test_error("", BIN_TEST_ERR_TM, &tokens));
}
