/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:56:25 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/14 20:29:26 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* MEMCCPY */

t_struct	new_node_env(char *env, t_struct *mode, int size_key)
{
	t_list_env	*new;

	new = (t_list_env *)ft_calloc(1, sizeof(t_list_env))
	if (new == NULL)
		deal_error(1);
	new->before = (char *)ft_calloc(size_key, sizeof(char));
	if (new->before == NULL)
		deal_error(1);
	ft_memcpy(new->before, env, size_key); //maybe (size_key + 1)
	
}

void	init_struct(t_struct *mode)
{
	mode->size_env = 0;
}