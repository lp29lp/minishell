/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:30:28 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/10 14:34:11 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* remove space out of quotes and just leaves only one space or no space */
int	jump_space(t_struct *mode, int i)
{
	while (mode->line_read[i] == ' ')
	{
		cat_jump(mode, i, 1);
	}
	if (mode->line_read[i] == '\0')
	{
		cat_jump(mode, (i - 1), 1);
		return (i -= 2);
	}
	return (i);
}

void	get_space(t_struct *mode, int i)
{
	if (mode->tag == 1)
	{
		while (mode->line_read[i] == ' ')
		{
			i++;
			mode->space++;
		}
		mode->tag = 0;
	}
	return ;
}

/* Tag != 1 when need remove space from beginning
 * if 1 will remove one character in specific in the string */
void	cat_jump(t_struct *mode, int i, int tag)
{
	if (tag == 1)
	{
		mode->left = ft_substr(mode->line_read, 0, i);
		mode->right = ft_substr(mode->line_read, (i + 1),
				ft_strlen(mode->line_read));
		free_null(&mode->line_read);
		mode->line_read = ft_strjoin(mode->left, mode->right);
		free_null(&mode->left);
		free_null(&mode->right);
	}
	else
	{
		mode->right = ft_substr(mode->line_read, i,
				ft_strlen(mode->line_read));
		free_null(&mode->line_read);
		mode->line_read = ft_strdup(mode->right);
		free_null(&mode->right);
	}
	return ;
}
