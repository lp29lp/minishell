/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:58:39 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/02/01 18:33:41 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prepare to execute execv */
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
	free_null(&path);
	free_double_env(&env, mode->size_env);
	free_double(&arg);
	waitpid(pid, &ret, 0);
	reset_fd(mode);
	g_status = WEXITSTATUS(ret);
	return (0);
}

/* Create path and see if command is valid using stat() */
char	*create_path(t_struct *mode)
{
	struct stat	statbuf;
	char		**path;

	mode->k = 0;
	if (stat(mode->split_input[0], &statbuf) == 0)
	{
		mode->aux = ft_strdup(mode->split_input[0]);
		return (mode->aux);
	}
	path = split_path(mode);
	if (path == NULL)
		return (mode->temp);
	while (path[mode->k] != NULL)
	{
		mode->aux = ft_strjoin(path[mode->k], "/");
		mode->temp = ft_strjoin(mode->aux, mode->split_two[0]);
		free_null(&mode->aux);
		if (stat(mode->temp, &statbuf) != 0)
			free_null(&mode->temp);
		else
			break ;
		mode->k++;
	}
	free_double(&path);
	return (mode->temp);
}

/* Create arg for execv */
char	**create_arg(t_struct *mode)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char **)ft_calloc((count_split(mode, 1) + 1), sizeof(char *));
	while (mode->split_input[i] != NULL)
	{
		ret[i] = (char *)ft_strdup(mode->split_input[i]);
		i++;
	}
	return (ret);
}

/* Create a double pointer from env list for execv */
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
