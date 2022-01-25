/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:31:28 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/25 18:22:31 by lpaulo-d         ###   ########.fr       */
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

void	init_struct(t_struct *mode)
{
	mode->space = 0;
	mode->tag = 0;
	mode->tag2 = 0;
	mode->bkp = 0;
	mode->count = 0;
	mode->count2 = 0;
	mode->redic = 0;
	mode->fd2 = 0;
	mode->fd1 = 0;
	mode->size_keywords = 0;
	mode->arrow->twice = 0;
	mode->arrow->once = 0;
	mode->arrow->left = 0;
	mode->arrow->right = 0;
	free_null(&mode->line_read);
	free_null(&mode->rest);
	free_split(mode, 0);
}
