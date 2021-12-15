/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:53:47 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/14 22:39:51 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	filter_env(char *env, t_struct *mode)
{
	int			size_key;
	int			rest;
	t_list_env	*temp;

	rest = 0;
	size_key = 0;
	temp = mode->env;
	while (env[++rest] != "=") // naming is correct in `=` ?
		size_key++; // Counting `=` (+1)
	while (env[rest++] != NULL)
	if (mode->size_env == 0)
	{
		mode->env = new_node_env(env, mode, size_key, rest);
		mode->size_env++;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node_env(env, mode, size_key, rest);
	mode->size_env++;
	

}

/* Can have NULL return in strdup need check: deal_error */
//! create deal_error
t_struct	new_node_env(char *env, t_struct *mode, int size_key, int rest)
{
	t_list_env	*new;

	new = (t_list_env *)ft_calloc(1, sizeof(t_list_env))
	if (new == NULL)
		deal_error(1);
	new->key = ft_strdup(env, 0, size_key);
	new->after = ft_strdup(env, size_key, (rest - size_key));
	new->nest = NULL;
	return (new)
}
