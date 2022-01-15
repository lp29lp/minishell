/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:40:28 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/15 20:00:24 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_redirect(t_struct *mode)
{
	int	i;

	mode->split_input = ft_split(mode->line_read, ' ');
	mode->split_cpy = ft_split(mode->line_read, ' ');
	mode->redic = 0;
	i = 0;
	while (mode->line_read[i] != '\0')
	{
		if (mode->line_read[i] == '>'
				|| mode->line_read[i] == '<')
		{
			mode->redic = 1;
			break ;
		}
		i++;
	}
	if (mode->redic == 1)
		create_var(mode);
}

void	create_var(t_struct *mode)
{
	int		i;
	char	*cpy;

	i = 0;
	while (mode->line_read[i] != '\0')
	{
		if (mode->line_read[i] == '>' || mode->line_read[i] == '<')
		{
			cpy = ft_substr(mode->line_read, 0, (i - 1));
			free_null(&mode->line_read);
			mode->line_read = ft_strdup(cpy);
			free_null(&cpy);
			break ;
		}
		i++;
	}
	free_split(mode, 1);
	mode->split_input = ft_split(mode->line_read, ' ');
}
