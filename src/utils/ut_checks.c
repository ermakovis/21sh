#include "msh.h"

int ut_check_execute(char const *path) 
{
    struct stat sb;
    int ret;
    int res;

    ret = 0;
    res = lstat(path, &sb);
    if (res == -1) 
    	ft_dprintf(STDERR_FILENO, "%s: %s: not found\n", g_msh->shell_name, path);
    else if (S_ISDIR(sb.st_mode)) 
        ft_dprintf(STDERR_FILENO, "%s: %s: is a directory\n",\
			g_msh->shell_name, path);
    else if (res == 0 && sb.st_mode & S_IXUSR) 
        ret = 1;
	else 
        ft_dprintf(STDERR_FILENO, "%s: %s: permission denied\n",\
			g_msh->shell_name, path);
    return (ret);
}

int ut_check_write(char const *path) 
{
    struct stat sb;
    int ret;
    int res;

    ret = 0;
    res = lstat(path, &sb);
    if (res == -1) 
    	ft_dprintf(STDERR_FILENO, "%s: %s: not found\n", g_msh->shell_name, path);
	else if (S_ISDIR(sb.st_mode)) 
        dprintf(STDERR_FILENO, "%s: %s: is a directory\n",\
			g_msh->shell_name, path);
	else if (res == 0 && sb.st_mode & S_IWUSR) 
        ret = 1;
	else 
        dprintf(STDERR_FILENO, "%s: %s: permission denied\n",\
			g_msh->shell_name, path);
    return (ret);
}
