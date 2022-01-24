/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:40:28 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/24 16:20:19 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_redirect(t_struct *mode)
{
	struct sigaction	sb;

	mode->split_cpy = ft_split(mode->line_read, ' ');
	mode->split_input = ft_split(mode->line_read, ' ');
	mode->redic = 0;
	mode->count = 0;
	while (mode->line_read[mode->count] != '\0')
	{
		if (mode->line_read[mode->count] == '\''
		|| mode->line_read[mode->count] == '\"')
			mode->tag2 = 1;
		if (mode->line_read[mode->count] == '>'
		&& mode->tag2 != 1 ||mode->tag2 != 1
		&& mode->line_read[mode->count] == '<')
		{
			mode->redic = 1;
			break ;
		}
		mode->count++;
		mode->tag2 = 0;
	}
	ft_memset(&sb, 0, sizeof(sb));
	jump_sig(SIGINT, handle_exec, &sb);
	jump_sig(SIGQUIT, handle_exec, &sb);
	if (mode->redic == 1)
	{
		if (handle_fd(mode) == 1)
			return (1);
	}
	return (0);
}

/* Fix string removing unnecessary words to create the command */
void	handle_command(t_struct *mode)
{
	mode->bkp = 0;
	while (mode->line_read[mode->count2] != '\0')
	{
		if (mode->line_read[mode->count2] == '>'
			|| mode->line_read[mode->count2] == '<')
		{
			mode->bkp = mode->count2;
			while (ft_isalnum(mode->line_read[mode->count2]) != 1
				&& mode->line_read[mode->count2] != '\0')
				mode->count2++;
			while (mode->line_read[mode->count2] != ' '
				&& mode->line_read[mode->count2] != '\0')
				mode->count2++;
		}
		if (mode->bkp != 0)
			break ;
		mode->count2++;
	}
	mode->temp = ft_substr(mode->line_read, 0, (mode->bkp - 1));
	mode->aux = ft_substr(mode->line_read, mode->count2, ft_strlen(mode->line_read));
	free_null(&mode->line_read);
	mode->line_read = ft_strjoin(mode->temp, mode->aux);
	free_null(&mode->temp);
	free_null(&mode->aux);
}

void	reset_fd(t_struct *mode)
{
	dup2(mode->in, 0);
	dup2(mode->out, 1);
	if (mode->tag2 == 1)
		unlink(".xablau");
	free(mode->arrow);
	mode->arrow = ft_calloc(1, sizeof(t_redic));
}
