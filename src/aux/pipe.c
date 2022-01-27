/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:27:39 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/27 18:40:36 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	do_pipe(t_struct *mode)
{
	mode->count = 0;
	mode->split_pipe = (char **)ft_calloc((mode->pipe + 2), sizeof(char *));
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
			cut_me_pipe(mode);
		mode->count++;
	}
	cut_me_pipe(mode);
	mode->count = 0;
	if (exec_pipe(mode) == 1)
		return (1);
	return (0);
}

int	exec_pipe(t_struct *mode)
{
	int	x;

	x = 0;
	printf("%s\n",mode->line_read);
	while (mode->split_pipe[x] != NULL)
	{
		free_null(&mode->line_read);
		mode->line_read = ft_strdup(mode->split_pipe[x]);
		printf("%s\n",mode->line_read);
		if (command(mode) == 1)
		{
			free_double(&mode->split_pipe);
			return (1);
		}
		x++;
	}
	free_double(&mode->split_pipe);
	return (0);
}

void	cut_me_pipe(t_struct *mode)
{
	mode->split_pipe[mode->x] = ft_substr(mode->line_read, mode->bkp,
		(mode->count - mode->bkp));
	mode->bkp = (mode->count + 1);
	mode->x++;
}

void	count_pipe(t_struct *mode)
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
			mode->pipe++;
		mode->count++;
	}
}
