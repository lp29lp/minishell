/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:53:47 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/16 01:42:57 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* get size from env and add in stack 
**Avoding alloc memory in temp LOL*/
void	filter_env(char *env, t_struct *mode)
{
	int			size_key;
	int			rest;
	t_list_env	*temp;
	t_list_env	*aux;

	rest = -1;
	size_key = 0;
	while (env[rest++] != '=')
		size_key++; // Counting `=` (+1)
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
	temp->next = new_node_env(env, mode, size_key, rest);
}

/* Can have NULL return in strdup need check: deal_error */
t_list_env	*new_node_env(char *env, t_struct *mode, int size_key, int rest)
{
	t_list_env	*new;

	new = (t_list_env *)ft_calloc(1, sizeof(t_list_env));
	if (new == NULL)
	{
		free(new);
		deal_error(mode);
	}
	new->next = NULL;
	new->key = ft_substr(env, 0, size_key);
	new->after = ft_substr(env, size_key, (rest - size_key));
	if (new->key == NULL || new->after == NULL)
	{
		free(new);
		deal_error(mode);
	}
	return (new);
}
