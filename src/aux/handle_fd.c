/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:52:36 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/15 20:50:29 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* reposicionar dup pois pode ter comando invalido */
void	handle_fd(t_struct *mode)
{
	if (mode->redic == 0)
		return ;
	check_redirect(mode);
	if (mode->arrow->d_right == 1 || mode->arrow->right == 1)
	{
		dup2(mode->fd, STDIN_FILENO);
		dup2(mode->fd, STDOUT_FILENO);
		close(mode->fd);
	}
}

// >
void	check_redirect(t_struct *mode)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (mode->split_cpy[i] != NULL)
	{
		while (mode->split_cpy[i][j] != '\0')
		{
			j = 0;
			if (mode->split_cpy[i][j] == '>')
			{
				memset(&mode->arrow, 0, sizeof(t_redic));
				if (mode->split_cpy[i][j + 1] == '>')
					mode->arrow->d_right = 1;
				else
					mode->arrow->right = 1;
				do_open(mode, (i + 1))
				break ;
			}
			j++;
		}
		i++;
	}
}

void	do_open(t_struct *mode, int i)
{
	char	*dir;
	char	buf[3000];
	char	*temp;

	getcwd(buf, 3000);
	temp = ft_strjoin(buf, "/");
	aux = ft_strjoin(temp, mode->split_cpy[i]);
	free_null(&temp);
	if (mode->arrow->right == 1)
	{
		mode->fd = open(aux, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (mode->split_cpy[i + 1] != NULL)
			close(fd);
	}
	else
	{
		mode->fd = open(aux, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (mode->split_cpy[i + 1] != NULL)
			close(fd);
	}
	free_null(&aux);
}
