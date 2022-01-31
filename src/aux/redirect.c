/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-s <dalves-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:50:27 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/31 17:39:06 by dalves-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Guide to redirect */
int	redirect(t_struct *mode)
{
	mode->split_rest = ft_split(mode->rest, ' ');
	mode->temp = create_path(mode);
	if (mode->temp == NULL)
		return (0);
	free_null(&mode->temp);
	if (check_redic_error(mode, count_split(mode, 2)) == 1)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		g_status = 2;
		return (1);
	}
	if (check_arrow(mode, count_split(mode, 2)) == 1)
		return (1);
	if (mode->tag2 == 1)
	{
		dup2(mode->in, 0);
		if (do_heredoc(mode) == 1)
		{
			g_status = mode->tag;
			free_null(&mode->xablau);
			return (1);
		}
	}
	redic_c(mode);
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
				return (1);
			mode->tag = 0;
			while (mode->split_rest[mode->count][mode->tag] != '\0')
			{
				if (mode->split_rest[mode->count][mode->tag] == '<'
						|| mode->split_rest[mode->count][mode->tag] == '>')
					return (1);
				mode->tag++;
			}
		}
		mode->count++;
	}
	return (0);
}

/* Start check redirect and sent to execute it */
int	check_arrow(t_struct *mode, int size)
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

/* Prepare heredoc creating the list to exit and open file descriptors */
void	double_left(t_struct *mode)
{
	char	buf[3000];

	getcwd(buf, 3000);
	mode->temp = ft_strjoin(buf, "/");
	mode->xablau = ft_strjoin(mode->temp, "xablau");
	free_null(&mode->temp);
	if (mode->fd1 != 0)
		close(mode->fd1);
	mode->fd1 = open(mode->xablau, O_WRONLY | O_CREAT | O_APPEND, 0777);
	while (mode->split_rest[mode->i] != NULL)
	{
		if (cmp(mode->split_rest[mode->i], "<<") == 0)
			mode->size_keywords++;
		mode->i++;
	}
	keywords(mode);
}

/* Execute heredoc in child process */
int	do_heredoc(t_struct *mode)
{
	struct sigaction	sb;

	ft_memset(&sb, 0, sizeof(sb));
	jump_sig(SIGINT, SIG_IGN, &sb);
	mode->tag = 0;
	g_status = 0;
	mode->pid = fork();
	if (mode->pid == 0)
	{
		dup2(mode->out, 1);
		jump_sig(SIGQUIT, handle_redic, &sb);
		jump_sig(SIGINT, handle_redic, &sb);
		while (1)
		{
			if (fake_heredoc(mode) == 1)
				break ;
		}
		do_free_heredoc(mode);
		exit(0);
	}
	waitpid(mode->pid, &mode->count, 0);
	g_status = WEXITSTATUS(mode->count);
	if (g_status == 130)
		return (1);
	return (0);
}
