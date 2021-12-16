/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/16 03:37:08 by lpaulo-d         ###   ########.fr       */
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
		display_prompt(&mode);
	}
	do_free(&mode);
}

/* Prompt session (Should display a prompt while waiting) 
add_history save command sent for use C+p or arrows
todo: Deal with C+d / Clear history maybe don't use readline now just print normal
*/
void	display_prompt(t_struct *mode)
{
	char	buf[3000];
	char	*line_read;
	char	*prompt;

	getcwd(buf, 3000);
	prompt = ft_strjoin(buf, "$ ");
	line_read = readline(prompt);
	if (line_read && *line_read)
		add_history(line_read);
}