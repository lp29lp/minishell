/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:28:16 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/02/01 20:29:53 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_env(char ***str, int x)
{
	if (str[0] != NULL)
	{
		while (x >= 0)
		{
			free(str[0][x]);
			str[0][x] = NULL;
			x--;
		}
		free(*str);
		*str = NULL;
	}
}

void	do_free_heredoc(t_struct *mode)
{
	free_null(&mode->line_read);
	free_null(&mode->rest);
	free_null(&mode->xablau);
	free_double(&mode->keywords);
	if (mode->size_env > 0)
		free_env(mode);
	free_split(mode, 0);
	if (mode->arrow != NULL)
		free(mode->arrow);
}
