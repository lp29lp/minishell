/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:58:39 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/19 15:29:42 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_execve(t_struct *mode)
{
	char	*path;
	char	**env;
	char	**arg;
	int		pid;
	int		ret;

	path = create_path(mode);
	if (path == NULL)
	{
		free_null(&path);
		return (1);
	}
	env = pointer_env(mode);
	arg = create_arg(mode);
	pid = fork();
	if (pid == 0)
		execve(path, arg, env);
	reset_fd(mode);
	free_null(&path);
	free_double(env);
	free_double(arg);
	waitpid(pid, &ret, 0);
	g_status = WEXITSTATUS(ret);
	return (0);
}

char	*create_path(t_struct *mode)
{
	struct	stat	statbuf;
	char			**path;
	char			*temp;
	char			*aux;
	int				i;

	i = 0;
	path = split_path(mode);
	while (path[i] != NULL)
	{
		aux = ft_strjoin(path[i],"/");
		temp = ft_strjoin(aux, mode->split_two[0]);
		free_null(&aux);
		if (stat(temp, &statbuf) != 0)
			free_null(&temp);
		else
			break ;
		i++;
	}
	free_double(path);
	return (temp);
}

char	**create_arg(t_struct *mode)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char **)ft_calloc((count_split(mode, 1) + 1), sizeof(char*));
	while (mode->split_input[i] != NULL)
	{
		ret[i] = (char *)ft_strdup(mode->split_input[i]);
		i++;
	}
	return (ret);
}

char	**pointer_env(t_struct *mode)
{
	t_list_env	*temp;
	char		**ret;
	char		*fix;
	char		*aux;
	int			i;

	i = 0;
	temp = mode->env;
	ret = (char **)ft_calloc((mode->size_env + 1), sizeof(char *));
	while (temp != NULL)
	{
		aux = ft_strjoin(temp->key, "=");
		fix = ft_strjoin(aux, temp->value);
		free_null(&aux);
		ret[i] = ft_strdup(fix);
		free_null(&fix);
		temp = temp->next;
		i++;
	}
	return (ret);
}
