/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_2_redic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:37:09 by dalves-s          #+#    #+#             */
/*   Updated: 2022/02/01 20:42:01 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Verify pipes valid to allocate memory */
void	count_pipe(t_struct *mode)
{
	mode->count = 0;
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
		if (mode->line_read[mode->count] != '\0')
			mode->count++;
	}
	mode->count = 0;
	if (mode->pipe != 0)
		mode->split_pipe = (char **)ft_calloc((mode->pipe + 2),
				sizeof(char *));
}

/* Deal with some specific errors of usage from builtins */
void	dollar_error(char *name, t_struct *mode, char *builtin)
{
	t_list_env	*temp;
	char		*info;

	info = NULL;
	temp = mode->env;
	while (temp != NULL)
	{
		if (cmp(temp->key, name) == 0)
		{
			info = ft_strdup(temp->value);
			free(name);
			break ;
		}
		temp = temp->next;
	}
	if (info != NULL)
		printf("minishell: %s: `%s': not a valid identifier\n", builtin, info);
	else
		printf("minishell: %s: `%s': not a valid identifier\n", builtin, name);
	free_null(&info);
}

/* Change stdin or stdout according to flags */
void	change_fd(t_struct *mode)
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
	open_files(mode);
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
