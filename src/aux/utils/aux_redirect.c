/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:51:54 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/29 21:21:51 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redic_c(t_struct *mode)
{
	g_status = mode->tag;
	mode->temp = strdup(mode->line_read);
	free_null(&mode->line_read);
	mode->line_read = ft_strjoin(mode->temp, mode->rest);
	free_null(&mode->temp);
	change_fd(mode);
}

void	aux_check_arrow(t_struct *mode, int i, int j)
{
	mode->arrow->twice = 0;
	mode->arrow->once = 0;
	if (mode->split_rest[i][j + 1] == '>' || mode->split_rest[i][j + 1] == '<')
		mode->arrow->twice = 1;
	else
		mode->arrow->once = 1;
	mode->arrow->redic = mode->split_rest[i][j];
	do_open(mode, (i + 1));
	if (mode->split_rest[i][j] == '<')
		mode->arrow->left = 1;
	else
		mode->arrow->right = 1;
	if (mode->tag == 1 && mode->size_keywords == 0)
		double_left(mode);
}

void	open_files(t_struct *mode)
{
	if (mode->arrow->redic == '<' && mode->arrow->once == 1)
			mode->fd1 = open(mode->aux, O_RDONLY, 0777);
	if (mode->arrow->redic == '>' && mode->arrow->once == 1)
		mode->fd2 = open(mode->aux, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (mode->arrow->redic == '>' && mode->arrow->twice == 1)
		mode->fd2 = open(mode->aux, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free_null(&mode->aux);
	mode->count2 = 0;
}

void	keywords(t_struct *mode)
{
	mode->i = 0;
	mode->j = 0;
	mode->keywords = (char **)ft_calloc((mode->size_keywords + 1),
			sizeof(char *));
	while (mode->split_rest[mode->i] != NULL)
	{
		if (cmp(mode->split_rest[mode->i], "<<") == 0)
		{
			mode->keywords[mode->j] = ft_strdup(mode->split_rest[mode->i + 1]);
			mode->j++;
		}
		mode->i++;
	}
}

void	fake_aux(t_struct *mode)
{
	if (mode->size_keywords == 1)
	{
		mode->count2 = mode->size_keywords;
		return ;
	}
	while (mode->count2 < mode->size_keywords)
	{
		free_null(&mode->aux);
		mode->aux = readline("> ");
		if (cmp(mode->aux, mode->keywords[mode->count2]) == 0)
		{
			mode->count2++;
			continue ;
		}
		else
			return ;
	}
}
