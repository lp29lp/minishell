/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:42:51 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/08 06:57:54 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(t_struct *mode)
{
	int		i;
	int		n;

	n = 0;
	if (cmp(mode->split_input[1], "-n") == 0)
		n = 1;
	if (n == 1)
		i = find_start(mode, 1);
	else
		i = find_start(mode, 0);
	fix_print(mode, i);
	if (n == 1)
		ft_putstr_fd(mode->line_read, 1);
	else
		ft_putendl_fd(mode->line_read, 1);
}

/* remove echo and -n and space from start and end */
void	fix_print(t_struct *mode, int start)
{
	int	i;

	i = 0;
	cat_jump(mode, start, 0);
	if (mode->line_read[i] == ' ')
	{
		while (mode->line_read[i] == ' ')
			i++;
		cat_jump(mode, i, 0);
	}
	trim_back(mode);
	return ;
}

/* find where the print start removing echo and -n if exist */
int	find_start(t_struct *mode, int tag)
{
	int	i;
	int	posi;
	int	j;
	int	bkp;

	posi = 1;
	if (tag == 1)
		posi = 2;
	i = 0;
	while (mode->line_read[i] != '\0')
	{
		j = 0;
		if (mode->line_read[i] == mode->split_input[posi][j])
		{
			bkp = i;
			while (mode->line_read[bkp] == mode->split_input[posi][j])
			{
				if (mode->split_input[posi][j + 1] == '\0')//j+1
					return (i);
				bkp++;
				j++;
			}
		}
		i++;
	}
	return (0);
}

/* remove space from the end of the string */
void	trim_back(t_struct *mode)
{
	int	size;

	size = ft_strlen(mode->line_read);
	while (mode->line_read[size] == ' ')
		size--;
	mode->right = ft_substr(mode->line_read, 0, size);
	free_null(&mode->line_read);
	mode->line_read = ft_strdup(mode->right);
	free_null(&mode->right);
}

