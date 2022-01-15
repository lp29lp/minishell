/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:39:36 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/15 20:05:43 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Deal with void input or redirect */
void	index_parse(t_struct *mode)
{
	int	i;

	free_split(mode, 0);
	if (cmp(mode->line_read, "") == 0)
	{
		g_status = 0;
		return ;
	}
	i = 0;
	if (mode->line_read[i] == ' ')
	{
		while (mode->line_read[i] == ' ')
			i++;
		cat_jump(mode, i, 0);
		if (cmp(mode->line_read, "") == 0)
		{
			g_status = 0;
			return ;
		}
	}
	parse_input_0(mode);
}

/* See what was the input and redirect */
void	parse_input_0(t_struct *mode)
{
	mode->split_two = ft_split(mode->line_read, ' ');
	treatment(mode);
	find_redirect(mode);
	if (cmp(mode->split_input[0], "cd") == 0)
		cmd_cd(mode);
	else if (cmp(mode->split_input[0], "env") == 0)
		print_env(mode);
	else if (cmp(mode->split_input[0], "pwd") == 0)
		print_pwd(mode);
	else if (cmp(mode->split_input[0], "export") == 0)
		cmd_export(mode);
	else if (cmp(mode->split_input[0], "unset") == 0)
		cmd_unset(mode);
	else if (cmp(mode->split_input[0], "echo") == 0)
		cmd_echo(mode);
	else if (cmp(mode->split_input[0], "exit") == 0)
		do_free(mode);
	else
	{
		if (cmd_execve(mode) == 1)
		{
			g_status = 127;
			printf("minishell: %s: command not found\n", mode->split_two[0]);
		}
	}
}
