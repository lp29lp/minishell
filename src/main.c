/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/16 22:46:54 by lpaulo-d         ###   ########.fr       */
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
todo: Deal with C+d c exit/ Clear history; free line_read; maybe don't use readline now just print normal
*/
void	display_prompt(t_struct *mode)
{
	char	path[3000];
	char	*prompt;
	char	*input;

	getcwd(path, 3000);
	prompt = ft_strjoin(path, "$ "); //use malloc
	prompt = ft_strjoin("minishell:", prompt); //use malloc
	mode->line_read = readline(prompt); //need free line
	if (mode->line_read && mode->*line_read)
		add_history(mode->line_read);//need clear history
	mode->split_input = ft_split(mode->line_read, ' ');
	parse_input_0(mode);
	//free(line_read);
	//free(prompt);when c+d duplicate the path
}
/* Use readline to avoid blank path by influence from history (arrows) */