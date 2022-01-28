/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:50:27 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/28 19:13:01 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Guide to redirect */
int	handle_fd(t_struct *mode)
{
	mode->split_rest = ft_split(mode->rest, ' ');
	mode->temp = create_path(mode);
	if (mode->temp == NULL)
		return (0);
	free_null(&mode->temp);
	if (check_redic_error(mode, count_split(mode, 2)) == 1)
	{
		g_status = 2;
		return (1);
	}
	if (check_arrow(mode, count_split(mode, 2)) == 1)
		return (1);
	if (mode->tag2 == 1)
	{
		if (do_heredoc(mode) == 1)
		{
			g_status= mode->tag;
			free_null(&mode->xablau);
			return (1);
		}
	}
	g_status= mode->tag;
	mode->temp = strdup(mode->line_read);
	free_null(&mode->line_read);
	mode->line_read = ft_strjoin(mode->temp, mode->rest);
	free_null(&mode->temp);
	change_fd(mode);
	return (0);
}

/* Verify if redirect is valid */
int	check_redic_error(t_struct *mode, int size)
{
	while (mode->count < size)
	{
		if (mode->split_rest[mode->count][0] == '<'
			|| mode->split_rest[mode->count][0] == '>')
		{
			mode->count++;
			if (mode->split_rest[mode->count] == NULL)
			{
				ft_putendl_fd("minishell: syntax error", 2);
				return (1);
			}
			mode->tag = 0;
			while (mode->split_rest[mode->count][mode->tag] != '\0')
			{
				if (mode->split_rest[mode->count][mode->tag] == '<'
						|| mode->split_rest[mode->count][mode->tag] == '>')
				{
					ft_putendl_fd("minishell: syntax error", 2);
					return (1);
				}
				mode->tag++;
			}
		}
		mode->count++;
	}
	return (0);
}

/* Start check redirect and sent to execute it */
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
				{
					printf("-minishell No such file or directory\n");
					return (1);
				}
				break ;
			}
			j++;
		}
		mode->count++;
	}
	return (0);
}

/*  */
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

/* Fix the redirect while open files if necessary and creates files
descriptors */
void	do_open(t_struct *mode, int i)
{
	char	buf[3000];

	mode->tag = 0;
	if (mode->arrow->twice == 1 && mode->arrow->redic == '<')
	{
		mode->tag = 1;
		mode->tag1 = 1;
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
	{
		mode->tag1 = 0;
		close(mode->fd1);
	}
	if (mode->arrow->redic == '<' && mode->arrow->once == 1)
			mode->fd1 = open(mode->aux, O_RDONLY, 0777);
	if (mode->arrow->redic == '>' && mode->arrow->once == 1)
		mode->fd2 = open(mode->aux, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (mode->arrow->redic == '>' && mode->arrow->twice == 1)
		mode->fd2 = open(mode->aux, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free_null(&mode->aux);
	mode->count2 = 0;
}

/* Change stdin or stdout according to flags */
void change_fd(t_struct *mode)
{
	if (mode->tag1 == 1)
		mode->fd1 = open(mode->xablau, O_RDONLY, 0777);
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
	free_null(&mode->xablau);
}

/* Prepare heredoc creating the list to exit and open file descriptors */
void	double_left(t_struct *mode)
{
	char	buf[3000];
	int		i;
	int		j;

	j = 0;
	i = 0;
	getcwd(buf, 3000);
	mode->temp = ft_strjoin(buf, "/");
	mode->xablau = ft_strjoin(mode->temp, "xablau");
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

/* Execute heredoc in child process */
int	do_heredoc(t_struct *mode)
{
	int	pid;
	int	test;
	struct sigaction sb;

	test = 0;
	ft_memset(&sb, 0, sizeof(sb));
	jump_sig(SIGINT, SIG_IGN, &sb);
	mode->tag = 0;
	pid = fork();
	g_status = 0;
	if (pid == 0)
	{
		dup2(mode->out, 1);
		jump_sig(SIGINT, handle_redic, &sb);
		while (1)
		{
			if (fake_heredoc(mode) == 1)
				break ;
		}
		exit(0);
	}
	waitpid(pid, &mode->count, 0);
	g_status = WEXITSTATUS(mode->count);
	free_double(&mode->keywords);
	if (g_status == 130)
	{
		return (1);
	}
	return (0);
}

/* Execute and "open" mini-prompt to heredoc */
int	fake_heredoc(t_struct *mode)
{
	mode->aux = readline("> ");
	if (cmp(mode->aux, mode->keywords[mode->count2]) == 0)
	{
		mode->count2++;
		fake_aux(mode);
	}
	if (mode->aux != NULL && mode->count2 < mode->size_keywords)
		ft_putendl_fd(mode->aux, mode->fd1);
	else if (mode->aux == NULL && mode->count2 < mode->size_keywords)
	{
		printf("-MiniShell: warning: here-document delimited by"
				"end-of-file (wanted `%s')\n", mode->keywords[mode->count2]);
		mode->count2++;
		if (mode->count2 == mode->size_keywords)
			return (1);
	}
	else
	{
		mode->count2 = mode->size_keywords;
		free_null(&mode->aux);
		return (1);
	}
	free_null(&mode->aux);
	return (0);
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
