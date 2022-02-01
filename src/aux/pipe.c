/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:27:39 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/02/01 18:33:26 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Verify if pipe is valid and redirect to execute */
int	do_pipe(t_struct *mode)
{
	while (mode->line_read[mode->count] != '\0')
	{
		if (mode->line_read[mode->count] == '\''
			|| mode->line_read[mode->count] == '\"')
		{
			mode->quote = mode->line_read[mode->count];
			mode->count++;
			while (mode->line_read[mode->count] != '\0')
			{
				if (mode->line_read[mode->count] == mode->quote)
					break ;
				mode->count++;
			}
		}
		if (mode->line_read[mode->count] == '|')
		{
			if (check_pipe_error(mode) == 1)
				return (1);
		}
		mode->count++;
	}
	cut_me_pipe(mode);
	if (exec_pipe(mode) == 1)
		return (1);
	return (0);
}

/* Check if pipe is correct */
int	check_pipe_error(t_struct *mode)
{
	mode->count3 = mode->count + 1;
	while (mode->line_read[mode->count3] != '\0'
		|| mode->line_read[mode->count3] == '\0')
	{
		if (mode->line_read[mode->count3] == '|'
			|| mode->line_read[mode->count3] == '\0')
		{
			free_double(&mode->split_pipe);
			ft_putendl_fd("-minishell: invalid usage of pipe", 2);
			return (1);
		}
		if (ft_isalnum(mode->line_read[mode->count3]) == 1)
			break ;
		mode->count3++;
	}
	cut_me_pipe(mode);
	return (0);
}

/* change files descriptors using pipe and dup and execute */
int	exec_pipe(t_struct *mode)
{
	int	x;

	x = 0;
	mode->count = 0;
	while (mode->split_pipe[x] != NULL)
	{
		free_null(&mode->line_read);
		mode->line_read = ft_strdup(mode->split_pipe[x]);
		if (mode->split_pipe[x + 1] != NULL)
			p_fd(mode, 0);
		else
			p_fd(mode, 2);
		if (command(mode) == 1)
		{
			free_double(&mode->split_pipe);
			return (1);
		}
		if (mode->split_pipe[x + 1] != NULL)
			p_fd(mode, 1);
		x++;
	}
	free_double(&mode->split_pipe);
	reset_fd(mode);
	return (0);
}

/* Use pipe() to create files descriptors and change stdin / stdout */
void	p_fd(t_struct *mode, int flag)
{
	if (flag == 0)
	{
		pipe(mode->p_fd);
		dup2(mode->p_fd[1], 1);
	}
	else if (flag == 1)
	{
		close(mode->p_fd[1]);
		mode->p_in = dup(mode->p_fd[0]);
		close(mode->p_fd[0]);
		dup2(mode->p_in, 0);
	}
	else
	{
		dup2(mode->out, 1);
		close(mode->p_fd[1]);
		close(mode->p_fd[0]);
	}
}

/* Separate a command from the rest/pipe */
void	cut_me_pipe(t_struct *mode)
{
	mode->split_pipe[mode->x] = ft_substr(mode->line_read, mode->bkp,
			(mode->count - mode->bkp));
	mode->bkp = (mode->count + 1);
	mode->x++;
}
