/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:27:15 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/21 20:14:23 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int	ft_exec_builtin(char **cmd)
{
	int						i;
	const static t_builtins	builtins[] = {
		{"echo", &ft_echo},
		{"cd", &ft_cd},
		{"setenv", &ft_setenv_builtin},
		{"unsetenv", &ft_unsetenv_builtin},
		{"env", &ft_env},
		{"exit", &ft_exit},
		{NULL, NULL}
	};

	i = 0;
	while (builtins[i].cmd && ft_strcmp(cmd[0], builtins[i].cmd))
		i++;
	return (builtins[i].cmd ? builtins[i].ft_builtin(cmd + 1) : -1);
}

static int	ft_exec_bypath(char **cmd, char *path)
{
	struct stat	tmp;

	if (path && !access(path, X_OK))
	{
		if (!get_environ()->pid && (get_environ()->pid = fork()))
		{
			return (get_environ()->pid > 0 ? 0
					: ft_dprintf(2, "21sh: fork error\n"));
		}
		execve(path, cmd, get_environ()->env);
		if (stat(path, &tmp) || !S_ISREG(tmp.st_mode)
			|| dup2(open(path, O_RDONLY), 0) == -1)
			exit(ft_dprintf(2, "%s: permission denied\n", *cmd) ? -2 : 0);
		else
			return (main_loop());
	}
	ft_dprintf(2, "%s: command not found or permission denied\n", *cmd);
	return (-1);
}

static char	**ft_get_path(const char *altpath)
{
	char	pwd[MAXPATHLEN];

	if (!altpath)
	{
		altpath = ft_getenv("PATH");
		if (!altpath || !*altpath)
			altpath = getcwd(pwd, MAXPATHLEN);
	}
	return (ft_strsplit(altpath, ':'));
}

static char	*ft_search_bin(char *bin_name, const char *altpath)
{
	int				i;
	char			*exec_path;
	char			**path;

	i = 0;
	exec_path = NULL;
	if (!(path = ft_get_path(altpath)))
		return (NULL);
	while (path[i])
	{
		if (!(exec_path = malloc(ft_strlen(path[i]) + ft_strlen(bin_name) + 2)))
			return (NULL);
		ft_strcpy(exec_path, path[i]);
		ft_strcat(exec_path, "/");
		ft_strcat(exec_path, bin_name);
		if (!access(exec_path, X_OK))
			break ;
		ft_memdel((void**)&exec_path);
		free(path[i++]);
	}
	while (path[i])
		free(path[i++]);
	free(path);
	return (exec_path);
}

int			ft_argv_exec(char **cmd, char *altpath)
{
	char	*bin_path;
	int		st;

	bin_path = NULL;
	if (!cmd || !*cmd)
		return (0);
	if (ft_strchr(*cmd, '/'))
		st = ft_exec_bypath(cmd, *cmd);
	else if ((st = ft_exec_builtin(cmd)) == -1)
	{
		bin_path = ft_search_bin(*cmd, altpath);
		st = ft_exec_bypath(cmd, bin_path);
	}
	free(bin_path);
	return (st);
}