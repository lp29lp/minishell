/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:50:27 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/19 15:28:15 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* reposicionar dup pois pode ter comando invalido */
void	handle_fd(t_struct *mode)
{
	char	*path;

	if (mode->redic == 0)
		return ;
	mode->fd = 0;
	path = create_path(mode);
	if (path == NULL)
		return ;
	free_null(&path);
	check_right(mode);
	free_split(mode, 1);
	mode->split_input = ft_split(mode->line_read, ' ');
	if (mode->arrow->d_right == 1 || mode->arrow->right == 1)
	{
		dup2(mode->fd, STDOUT_FILENO);
		close(mode->fd);
	}
}

// >
void	check_right(t_struct *mode)
{
	int		i;
	int		j;

	i = 0;
	while (mode->split_cpy[i] != NULL)
	{
		j = 0;
		while (mode->split_cpy[i][j] != '\0')
		{
			if (mode->split_cpy[i][j] == '>')
			{
				mode->arrow->d_right = 0;
				mode->arrow->right = 0;
				if (mode->split_cpy[i][j + 1] == '>')
					mode->arrow->d_right = 1;
				else
					mode->arrow->right = 1;
				do_open(mode, (i + 1));
				break ;
			}
			j++;
		}
		i++;
	}
}

void	do_open(t_struct *mode, int i)
{
	char	buf[3000];
	char	*temp;
	char	*aux;

	handle_command(mode);
	getcwd(buf, 3000);
	temp = ft_strjoin(buf, "/");
	aux = ft_strjoin(temp, mode->split_cpy[i]);
	free_null(&temp);
	if (mode->fd != 0)
		close(mode->fd);
	if (mode->arrow->right == 1)
		mode->fd = open(aux, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		mode->fd = open(aux, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free_null(&aux);
}
