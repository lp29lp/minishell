/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:53:47 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/28 18:55:10 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

/* create a list of environment variable */
void	save_env(t_struct *mode, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		filter_env(env[i], mode);
		i++;
	}
}

/* get size from env and add in stack / Counting '=' but don't save*/
void	filter_env(char *env, t_struct *mode)
{
	int			size_key;
	int			rest;
	t_list_env	*temp;

	rest = -1;
	size_key = 0;
	while (env[rest++] != '=')
		size_key++;
	while (env[rest] != '\0')
		rest++;
	if (mode->size_env == 0)
	{
		mode->env = new_node_env(env, mode, size_key, rest);
		mode->size_env++;
		return ;
	}
	temp = mode->env;
	while (temp->next != NULL)
		temp = temp->next;
	mode->size_env++;
	temp->next = new_node_env(env, mode, size_key, rest);
}

/* Create a node for env */
t_list_env	*new_node_env(char *env, t_struct *mode, int size_key, int rest)
{
	t_list_env	*new;

	new = (t_list_env *)ft_calloc(1, sizeof(t_list_env));
	if (new == NULL)
	{
		free(new);
		do_free(mode);
	}
	new->next = NULL;
	new->key = ft_substr(env, 0, (size_key - 1));
	new->value = ft_substr(env, size_key, (rest - size_key));
	if (new->key == NULL || new->value == NULL)
	{
		free(new->key);
		free(new->value);
		free(new);
		do_free(mode);
	}
	return (new);
}

/* Print the envrionments variables */
void	print_env(t_struct *mode)
{
	t_list_env	*temp;

	g_status = 0;
	if (count_split(mode, 0) != 1)
	{
		g_status = 127;
		ft_putendl_fd("minishell: wrong usage from env command", 1);
		return ;
	}
	temp = mode->env;
	while (temp)
	{
		ft_putstr_fd(temp->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(temp->value, 1);
		temp = temp->next;
	}
	return ;
}
