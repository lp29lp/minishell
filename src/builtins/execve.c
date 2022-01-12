/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:58:39 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/12 17:54:41 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_execve(t_struct *mode)
{
	char	*path;
	/* char	**env; */
	char	**arg;
	int		pid;

	path = create_path(mode);
	/* env = pointer_env(mode); */
	arg = create_arg(mode);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, arg, NULL) == -1)
			printf("minishell: %s: command not found\n", mode->split_two[0]);
	}
	free_null(&path);
	/* free_null(env); */
	free_null(arg);
	waitpid(pid, &g_status, 0);
}

char	**create_arg(t_struct *mode)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	while (mode->split_input[i] != NULL)
	{
		ret[i] = ft_strdup(mode->split_input[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*create_path(t_struct *mode)
{
	struct	stat	statbuf;
	char			**path;
	char			*temp;
	char			*aux;
	int				i;

	i = 0;
	path = NULL;
	path = split_path(mode);
	while (path[i] != NULL)
	{
		aux = ft_strjoin(path[i],"/");
		temp = ft_strjoin(aux, mode->split_input[0]);
		free_null(&aux);
		if (stat(temp, &statbuf) != 0)
			free_null(&temp);
		else
			break ;
		i++;
	}
	return (temp);
}

/* Sempre vai ser a lista ou pode ser sempre null? */
char	**pointer_env(t_struct *mode)
{
	t_list_env	*temp;
	char		**ret;
	char		*fix;
	char		*aux;
	int			i;

	i = 0;
	ret = NULL;
	temp = mode->env;
	while (temp->next != NULL)
	{
		aux = ft_strjoin(temp->key, "=");
		fix = ft_strjoin(aux, temp->value);
		free_null(&aux);
		ret[i] = ft_strdup(fix);
		free_null(&fix);
		temp = temp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
