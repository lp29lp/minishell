/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:40:28 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/31 19:54:35 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* find command and parameters to separate from redirect if exist*/
void	check_redirect(t_struct *mode)
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
		if (mode->line_read[mode->count] == '>'
			|| mode->line_read[mode->count] == '<')
		{
			mode->redic = 1;
			cut_me(mode);
			break ;
		}
		if (mode->line_read[mode->count] != '\0')
			mode->count++;
	}
	treatment(mode, &mode->line_read);
}

/* Separete command and parameters from redirect */
void	cut_me(t_struct *mode)
{
	mode->temp = ft_substr(mode->line_read, 0, (mode->count - 1));
	mode->rest = ft_substr(mode->line_read, mode->count,
			ft_strlen(mode->line_read));
	free_null(&mode->line_read);
	mode->line_read = ft_strdup(mode->temp);
	free_null(&mode->temp);
	treatment(mode, &mode->rest);
	mode->temp = strdup(mode->rest);
	free_null(&mode->rest);
	mode->rest = ft_strjoin(" ", mode->temp);
	free_null(&mode->temp);
}

/* Fix string removing unnecessary words to create the command */
void	handle_command(t_struct *mode)
{
	mode->bkp = 0;
	while (mode->rest[mode->count2] != '\0')
	{
		if (mode->rest[mode->count2] == '>' || mode->rest[mode->count2] == '<')
		{
			mode->bkp = mode->count2;
			while (ft_isalnum(mode->rest[mode->count2]) != 1
				&& mode->rest[mode->count2] != '\0')
				mode->count2++;
			while (mode->rest[mode->count2] != ' '
				&& mode->rest[mode->count2] != '\0')
				mode->count2++;
		}
		if (mode->bkp != 0)
			break ;
		mode->count2++;
	}
	mode->temp = ft_substr(mode->rest, 0, (mode->bkp - 1));
	mode->aux = ft_substr(mode->rest, mode->count2, ft_strlen(mode->rest));
	free_null(&mode->rest);
	mode->rest = ft_strjoin(mode->temp, mode->aux);
	free_null(&mode->temp);
	free_null(&mode->aux);
}

/* Reset file descriptors, remove temp files and reset redic struct */
void	reset_fd(t_struct *mode)
{
	dup2(mode->in, 0);
	dup2(mode->out, 1);
	if (mode->tag2 == 1)
		unlink("xablau");
	free(mode->arrow);
	mode->arrow = ft_calloc(1, sizeof(t_redic));
}
