/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/17 08:39:31 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *todo:	Need deal with close launch to start debug; Start print env
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
add_history save command sent for use C+p or arrows */
void	display_prompt(t_struct *mode)
{
	char	path[3000];
	char	*prompt;
	char	*input;

	put_some_colors(mode);
	mode->line_read = readline(""); //need free line
	if (mode->line_read)
		add_history(mode->line_read);//need clear history
	mode->split_input = ft_split(mode->line_read, ' ');
	parse_input_0(mode);
	free(mode->line_read);
}

/* Get logname and print the path */
void	put_some_colors(t_struct *mode)
{
	t_list_env	*temp;
	char		*logname;
	char		path[3000];

	temp = mode->env;
	while (temp)
	{
		if (cmp(temp->key, "LOGNAME") == 0)
		{
			logname = ft_strdup(temp->value);
			break ;
		}
		temp = temp->next;
	}
	getcwd(path, 3000);
	printf(YEL "%s" WHT "@" GRN "minishell" WHT ":" BRED "%s" WHT " $ "
			reset, logname, path);
	free(logname);
}