/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:30:28 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/28 19:00:48 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* remove space out of quotes and just leaves only one space or no space */
int	jump_space(t_struct *mode, int i, char **str)
{
	while (str[0][i] == ' ')
	{
		cat_jump(mode, i, 1, str);
	}
	if (str[0][i] == '\0')
	{
		cat_jump(mode, (i - 1), 1, str);
		return (i -= 2);
	}
	return (i);
}

/* Count spaces */
void	get_space(t_struct *mode, int i, char *str)
{
	if (mode->tag == 1)
	{
		while (str[i] == ' ')
		{
			i++;
			mode->space++;
		}
		mode->tag = 0;
	}
	return ;
}

/* Tag != 1 when need remove space from beginning
if 1 will remove one character in specific in the string */
void	cat_jump(t_struct *mode, int i, int tag, char **str)
{
	if (tag == 1)
	{
		mode->left = ft_substr(*str, 0, i);
		mode->right = ft_substr(*str, (i + 1),
				ft_strlen(*str));
		free_null(&*str);
		*str = ft_strjoin(mode->left, mode->right);
		free_null(&mode->left);
		free_null(&mode->right);
	}
	else
	{
		mode->right = ft_substr(*str, i, ft_strlen(*str));
		free_null(&*str);
		*str = ft_strdup(mode->right);
		free_null(&mode->right);
	}
	return ;
}
