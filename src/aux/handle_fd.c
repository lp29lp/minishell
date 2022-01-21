/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:50:27 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/20 22:49:35 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* reposicionar dup pois pode ter comando invalido */
int	handle_fd(t_struct *mode)
{
	char	*path;

	if (mode->redic == 0)
		return (0);
	path = create_path(mode);
	if (path == NULL)
		return (0);
	free_null(&path);
	if (check_arrow(mode, count_split(mode, 2)) == 1)
	{
		printf("-minishell No such file or directory\n");
		return (1);
	}
	free_split(mode, 1);
	mode->split_input = ft_split(mode->line_read, ' ');
	if (mode->arrow->right == 1)
	{
		dup2(mode->fd2, STDOUT_FILENO);
		close(mode->fd2);
	}
	if (mode->arrow->left == 1)
	{
		dup2(mode->fd1, STDIN_FILENO);
		close(mode->fd1);
	}
	return (0);
}

// >
int	check_arrow(t_struct *mode, int	size)
{
	int		j;

	mode->count = 0;
	mode->arrow->left = 0;
	mode->arrow->right = 0;
	mode->fd1 = 0;
	mode->fd2 = 0;
	while (mode->count < size)
	{
		j = 0;
		while (mode->split_cpy[mode->count][j] != '\0')
		{
			if (mode->split_cpy[mode->count][j] == '>'
				|| mode->split_cpy[mode->count][j] == '<')
			{
				aux_check_arrow(mode, mode->count, j);
				if (mode->fd1 == -1)
					return (1);
				break ;
			}
			j++;
		}
		mode->count++;
	}
	return (0);
}

void	aux_check_arrow(t_struct *mode, int i, int j)
{
	mode->arrow->twice = 0;
	mode->arrow->once = 0;
	if (mode->split_cpy[i][j + 1] == '>' || mode->split_cpy[i][j + 1] == '<')
		mode->arrow->twice = 1;
	else
		mode->arrow->once  = 1;
	mode->arrow->redic = mode->split_cpy[i][j];
	do_open(mode, (i + 1));
	/* if (mode->tag == 1) */
	/* 	double_left(mode); */
	if (mode->split_cpy[i][j] == '<')
		mode->arrow->left = 1;
	else
		mode->arrow->right = 1;
}

void	do_open(t_struct *mode, int i)
{
	char	buf[3000];

	mode->tag = 0;
	if (mode->arrow->twice == 1 && mode->arrow->redic == '<')
		mode->tag = 1;
	if (mode->tag == 0)
		handle_command(mode);
	getcwd(buf, 3000);
	mode->temp = ft_strjoin(buf, "/");
	mode->aux = ft_strjoin(mode->temp, mode->split_cpy[i]);
	free_null(&mode->temp);
	if (mode->fd2 != 0 && mode->arrow->redic == '>')
		close(mode->fd2);
	if (mode->fd1 != 0 && mode->arrow->redic == '<')
		close(mode->fd1);
	if (mode->arrow->redic == '<' && mode->arrow->once == 1)
			mode->fd1 = open(mode->aux, O_RDONLY, 0777);
	if (mode->arrow->redic == '>' && mode->arrow->once == 1)
		mode->fd2 = open(mode->aux, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (mode->arrow->redic == '>' && mode->arrow->twice == 1)
		mode->fd2 = open(mode->aux, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free_null(&mode->aux);
}

void	double_left(t_struct *mode)
{
	char	buf[3000];

	getcwd(buf, 3000);
	mode->temp = ft_strjoin(buf, "/");
	mode->aux = ft_strjoin(mode->temp, "\"xablau\"");
	free_null(&mode->temp);
	mode->fd1 = open(mode->aux, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free_null(&mode->aux);
}
