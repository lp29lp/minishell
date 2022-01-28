/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:39:36 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/28 18:06:29 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Deal with void input or redirect */
void	index_parse(t_struct *mode)
{

	if (cmp(mode->line_read, "") == 0)
	{
		g_status = 0;
		return ;
	}
	mode->count = 0;
	if (mode->line_read[mode->count] == ' ')
	{
		while (mode->line_read[mode->count] == ' ')
			mode->count++;
		cat_jump(mode, mode->count, 0, &mode->line_read);
		if (cmp(mode->line_read, "") == 0)
		{
			g_status = 0;
			return ;
		}
	}
	mode->pipe = 0;
	count_pipe(mode);
	if (mode->pipe != 0)
	{
		if (do_pipe(mode) == 1)
			return ;
	}
	else if (command(mode) == 1)
		return ;
}

int	command(t_struct *mode)
{
	struct sigaction	sb;

	mode->split_two = ft_split(mode->line_read, ' ');
	mode->count = 0;
	check_redirect(mode);
	if (mode->redic == 1)
	{
		mode->count = 0;
		if (handle_fd(mode) == 1)
			return (1);
	}
	ft_memset(&sb, 0, sizeof(sb));
	jump_sig(SIGINT, handle_exec, &sb);
	jump_sig(SIGQUIT, handle_exec, &sb);
	mode->split_input = ft_split(mode->line_read, ' ');
	parse_input_0(mode);
	init_struct(mode);
	return (0);
}

/* See what was the input and redirect */
void	parse_input_0(t_struct *mode)
{
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
	if (mode->pipe != 0)
		reset_fd(mode, 0);
}
