/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:50:27 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/25 18:48:06 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* reposicionar dup pois pode ter comando invalido */
int	handle_fd(t_struct *mode)
{
	mode->split_rest = ft_split(mode->rest, ' ');
	mode->temp = create_path(mode);
	if (mode->temp == NULL)
		return (0);
	free_null(&mode->temp);
	if (check_arrow(mode, count_split(mode, 2)) == 1)
	{
		printf("-minishell No such file or directory\n");
		return (1);
	}
	free_split(mode, 1);
	mode->split_input = ft_split(mode->line_read, ' ');
	if (do_heredoc(mode) == 1)
	{
		free_null(&mode->xablau);
		return (1);
	}
	mode->temp = strdup(mode->line_read);
	free_null(&mode->line_read);
	mode->line_read = ft_strjoin(mode->temp, mode->rest);
	printf("ficou: %s\n", mode->line_read);
	free_null(&mode->temp);
	change_fd(mode);
	return (0);
}

int	do_heredoc(t_struct *mode)
{
	if (mode->tag2 == 1)
	{
		/* mode->tag2 = fork(); */
		/* if (mode->tag2 == 0) */
		/* { */
			if (fake_heredoc(mode) == 1)
			{
				free_double(&mode->keywords);
				return (1);
			}
			free_double(&mode->keywords);
			/* exit(0); */
		/* } */
	}
	return (0);
}

// >
int	check_arrow(t_struct *mode, int	size)
{
	int		j;

	mode->count = 0;
	while (mode->count < size)
	{
		j = 0;
		while (mode->split_rest[mode->count][j] != '\0')
		{
			if (mode->split_rest[mode->count][j] == '>'
				|| mode->split_rest[mode->count][j] == '<')
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
	if (mode->split_rest[i][j + 1] == '>' || mode->split_rest[i][j + 1] == '<')
		mode->arrow->twice = 1;
	else
		mode->arrow->once  = 1;
	mode->arrow->redic = mode->split_rest[i][j];
	do_open(mode, (i + 1));
	if (mode->split_rest[i][j] == '<')
		mode->arrow->left = 1;
	else
		mode->arrow->right = 1;
	if (mode->tag == 1 && mode->size_keywords == 0)
		double_left(mode);
}

void	do_open(t_struct *mode, int i)
{
	char	buf[3000];

	mode->tag = 0;
	if (mode->arrow->twice == 1 && mode->arrow->redic == '<')
	{
		mode->tag = 1;
		mode->tag2 = 1;
	}
	handle_command(mode);
	getcwd(buf, 3000);
	mode->temp = ft_strjoin(buf, "/");
	mode->aux = ft_strjoin(mode->temp, mode->split_rest[i]);
	free_null(&mode->temp);
	if (mode->fd2 != 0 && mode->arrow->redic == '>')
		close(mode->fd2);
	if (mode->fd1 != 0 && mode->arrow->redic == '<' && mode->arrow->once == 1)
		close(mode->fd1);
	if (mode->arrow->redic == '<' && mode->arrow->once == 1)
			mode->fd1 = open(mode->aux, O_RDONLY, 0777);
	if (mode->arrow->redic == '>' && mode->arrow->once == 1)
		mode->fd2 = open(mode->aux, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (mode->arrow->redic == '>' && mode->arrow->twice == 1)
		mode->fd2 = open(mode->aux, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free_null(&mode->aux);
	mode->count2 = 0;
}

void change_fd(t_struct *mode)
{
	if (mode->tag2 == 1)
	{
		mode->fd1 = open(mode->xablau, O_RDONLY | O_CREAT | O_APPEND, 0777);
		free_null(&mode->xablau);
	}
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
}

void	double_left(t_struct *mode)
{
	char	buf[3000];
	int		i;
	int		j;

	j = 0;
	i = 0;
	getcwd(buf, 3000);
	mode->temp = ft_strjoin(buf, "/");
	mode->xablau = ft_strjoin(mode->temp, ".xablau");
	free_null(&mode->temp);
	if (mode->fd1 != 0)
		close(mode->fd1);
	mode->fd1 = open(mode->xablau, O_WRONLY | O_CREAT | O_APPEND, 0777);
	while (mode->split_rest[i] != NULL)
	{
		if (cmp(mode->split_rest[i], "<<") == 0)
			mode->size_keywords++;
		i++;
	}
	i = 0;
	mode->keywords = (char **)ft_calloc((mode->size_keywords + 1), sizeof(char *));
	while (mode->split_rest[i] != NULL)
	{
		if (cmp(mode->split_rest[i], "<<") == 0)
		{
			mode->keywords[j] = ft_strdup(mode->split_rest[i + 1]);
			j++;
		}
		i++;
	}
}

int	fake_heredoc(t_struct *mode)
{
	while (1)
	{
		mode->aux = readline("> ");
		if (cmp(mode->aux, mode->keywords[mode->count2]) == 0)
		{
			mode->count2++;
			fake_aux(mode);
		}
		if (mode->aux != NULL && mode->count2 < mode->size_keywords)
			ft_putendl_fd(mode->aux, mode->fd1);
		else
		{
			ft_putendl_fd("", 1);
			mode->count2 = mode->size_keywords;
			break ;
		}
		free_null(&mode->aux);
	}
	free_null(&mode->aux);
	if (mode->count2 == mode->size_keywords)
		return (0);
	else
		return (1);
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
	close(mode->fd1);
}
