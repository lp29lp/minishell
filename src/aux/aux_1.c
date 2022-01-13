/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:31:28 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/13 06:42:18 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(t_struct *mode)
{
	t_list_env	*temp;
	char		*aux;
	char		**path;

	temp = mode->env;
	aux = NULL;
	while (temp)
	{
		if (cmp(temp->key, "PATH") == 0)
		{
			aux = ft_strdup(temp->value);
			break ;
		}
		temp = temp->next;
	}
	path = ft_split(aux, ':');
	free_null(&aux);
	return (path);
}
