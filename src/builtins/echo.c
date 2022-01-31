/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 03:31:42 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/31 03:32:04 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print the parameters */
void	cmd_echo(t_struct *mode)
{
	int		i;
	int		n;

	n = 0;
	g_status = 0;
	if (cmp(mode->split_input[1], "-n") == 0)
		n = 1;
	i = count_split(mode, 1);
	if (i == 2 && n == 1 && mode->space == 0)
		return ;
	if (i == 1 && n == 0 && mode->space == 0)
	{
		ft_putendl_fd("", 1);
		return ;
	}
	if (echo_check(mode, i, n) == 1)
		return ;
	if (n == 1)
		i = find_start(mode, 1);
	else
		i = find_start(mode, 0);
	cat_jump(mode, i, 0, &mode->line_read);
	echo_print(mode, n);
}

/* Deal with empty/spaces parameters */
int	echo_check(t_struct *mode, int i, int n)
{
	if ((i == 2 && n == 1 && mode->space != 0) || (i == 1 && n == 0
			&& mode->space != 0))
	{
		free_null(&mode->line_read);
		mode->line_read = ft_strdup("");
		echo_print(mode, n);
		return (1);
	}
	else
		return (0);
}

/* Print echo but deal with space when is printable */
void	echo_print(t_struct *mode, int n)
{
	if (n == 1)
	{
		if (mode->split_two[2][0] == '\'' || mode->split_two[2][0] == '\"')
		{
			while (mode->space-- > 0)
				ft_putchar_fd(' ', 1);
			ft_putstr_fd(mode->line_read, 1);
		}
		else
			ft_putstr_fd(mode->line_read, 1);
	}
	else
	{
		if (mode->split_two[1][0] == '\'' || mode->split_two[1][0] == '\"')
		{
			while (mode->space-- > 0)
				ft_putchar_fd(' ', 1);
			ft_putendl_fd(mode->line_read, 1);
		}
		else
			ft_putendl_fd(mode->line_read, 1);
	}
}

/* find where the print start removing echo and -n if exist */
int	find_start(t_struct *mode, int tag)
{
	int	i;
	int	posi;
	int	j;

	posi = 1;
	if (tag == 1)
		posi = 2;
	i = 0;
	while (mode->line_read[i] != '\0')
	{
		j = 0;
		if (mode->line_read[i] == mode->split_input[posi][j])
		{
			mode->bkp = i;
			while (mode->line_read[mode->bkp] == mode->split_input[posi][j])
			{
				if (mode->split_input[posi][j + 1] == '\0')
					return (i);
				mode->bkp++;
				j++;
			}
		}
		i++;
	}
	return (0);
}
