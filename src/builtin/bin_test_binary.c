#include "msh.h"

static int	bin_test_binary_checkint(char *arg)
{
	if (ft_isnumber(arg))
		return (1);
	ft_dprintf(2, "%s: test: %s: %s\n",\
		g_msh->shell_name, arg, BIN_TEST_ERR_INT);
	return (0);
}

static int	bin_test_binary_int(int num1, int num2, int flag)
{
	if (flag & BIN_TEST_INT_EQU)
		return (!(num1 == num2));
	if (flag & BIN_TEST_INT_NEQU)
		return (!(num1 != num2));
	if (flag & BIN_TEST_INT_GT)
		return (!(num1 > num2));
	if (flag & BIN_TEST_INT_GE)
		return (!(num1 >= num2));
	if (flag & BIN_TEST_INT_LT)
		return (!(num1 < num2));
	if (flag & BIN_TEST_INT_LE)
		return (!(num1 <= num2));
	return (1);
}

int		bin_test_binary(char *arg1, char *arg2, int flag)
{
	int	num1;
	int num2;

	if (flag & BIN_TEST_STR_EQU)
		return (!ft_strcmp(arg1, arg2) ? 0 : 1);
	if (flag & BIN_TEST_STR_NEQU)
		return (!ft_strcmp(arg1, arg2) ? 1 : 0);
	if (!bin_test_binary_checkint(arg1))
		return (2);
	if (!bin_test_binary_checkint(arg2))
		return (2);
	num1 = ft_atoi(arg1);
	num2 = ft_atoi(arg2);
	return (bin_test_binary_int(num1, num2, flag));
}
