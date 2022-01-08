/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:42:51 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/08 18:31:46 by lpaulo-d         ###   ########.fr       */
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
	cat_jump(mode, i, 0);
	if (n == 1)
		ft_putstr_fd(mode->line_read, 1);
	else
		ft_putendl_fd(mode->line_read, 1);
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

