/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:55:11 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/13 21:41:30 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		ft_count_args(t_list *toks)
{
	int	ret;

	ret = 0;
	while (toks)
	{
		if (((t_token*)(toks->content))->type == word)
			ret++;
		toks = toks->next;
	}
	return (ret);
}

char	**ft_make_av(t_list *toks)
{
	int		i;
	int		size;
	char	**av;

	i = 0;
	size = ft_count_args(toks) + 1;
	if (!(av = ft_memalloc(size * sizeof(av))))
		return (NULL);
	while (i < size && toks)
	{
		if (((t_token*)(toks->content))->type == word
			&& !(av[i++] = parse_argv(((t_token*)(toks->content))->data.word)))
		{
			ft_strarr_free(av);
			return (NULL);
		}
		toks = toks->next;
	}
	return (av);
}

int		ft_ast_cmd_exec(t_ast *ast)
{
	pid_t	pid;
	int		ret;
	t_cmd	*cmd;
	int		fd[2];

	cmd = ast->cmd;
	if (cnd->next && )
		waitpid(pid, &ret, 0);
	while (cmd)
	{
		if (cmd->next)
			pipe(fd);
				dup2(1, fd[1]);
			}
		if (cmd->next && (pid = fork()))
			waitpid(pid, &ret, 0);
		else
		{
			if (cmd->next)
			{
				pipe(fd);
				dup2(1, fd[1]);
			}
			if (cmd->prev)
			{
				close(fd[1]);
				dup2(0, fd[0]);
			}
			if ((cmd->av = ft_make_av(cmd->toks)))
				ret = ft_exec(cmd->av, NULL);
			cmd->av = NULL;
			cmd = cmd->next;
		}
	}
	return (ret);
}

int		ft_ast_and_exec(t_ast *ast)
{
	int	ret_right;
	int	ret_left;

	if (!(ret_right = ft_ast_exec(ast->right)))
		return ((ret_left = ft_ast_exec(ast->left)));
	else
		return (ret_right);
}

int		ft_ast_or_exec(t_ast *ast)
{
	int	ret_right;
	int	ret_left;

	if (!(ret_right = ft_ast_exec(ast->right)))
		return (ret_right);
	else
		return ((ret_left = ft_ast_exec(ast->left)));
}

int		ft_ast_bg_exec(t_ast *ast)
{
	int	ret_right;
	int	ret_left;

	ret_right = ft_ast_exec(ast->right);
	return ((ret_left = ft_ast_exec(ast->left)));
}

int		ft_ast_smcln_exec(t_ast *ast)
{
	int	ret_right;
	int	ret_left;

	ret_right = ft_ast_exec(ast->right);
	return ((ret_left = ft_ast_exec(ast->left)));
}

int		ft_ast_exec(t_ast *ast)
{
	if (!ast)
		return (-1);
	else if (ast->type == cmd)
		return (ft_ast_cmd_exec(ast));
	else if (ast->type == ast_and)
		return (ft_ast_and_exec(ast));
	else if (ast->type == ast_or)
		return (ft_ast_or_exec(ast));
	else if (ast->type == ast_bg)
		return (ft_ast_bg_exec(ast));
	else if (ast->type == ast_smcln)
		return (ft_ast_smcln_exec(ast));
	else
		return (-1);
}
