/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/16 02:10:03 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *todo:	see how to use readline to wait a input
*/

int	main(int ac, char ** av, char **env)
{
	t_struct	mode;
	char		*line;

	init_struct(&mode);
	save_env(&mode, env);
	while (1)
	{
		line = readline("oq isso faz?");
	}
	deal_error(&mode);
}