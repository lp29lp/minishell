/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/18 22:24:11 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *todo:	Need deal with close launch to start debug; signal to close could need do another things first;
*/

int	main(int ac, char ** av, char **env)
{
	t_struct			mode;
	struct sigaction	sa; 

	if (ac != 1 || av[1])
		return (0);
	init_struct(&mode);
	save_env(&mode, env);
	test_sig(SIGINT, handle_sigint, &sa);
	//test_sig(SIGTSTP, SIG_IGN, &sa);
	while (1)//could be a global when need close use 0 and send to do_free
	{
		display_prompt(&mode);
	}
	do_free(&mode);
}

/* Prompt session (Should display a prompt while waiting) 
add_history save command sent for use C+p or arrows */
void	display_prompt(t_struct *mode)
{
	char	*path;

	path = put_some_colors(mode);
	mode->line_read = readline(path); //need free line
	if (mode->line_read)
		add_history(mode->line_read);//need clear history
	mode->split_input = ft_split(mode->line_read, ' ');//check if null free
	parse_input_0(mode);
	free(mode->line_read);
	free(path);
}

/* Get logname, path and put colors */
char	*put_some_colors(t_struct *mode)
{
	t_list_env	*temp;
	char		*logname;
	char		path[3000];
	char		*aux;

	temp = mode->env;
	logname = NULL;
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
	aux = ft_strjoin(YEL, logname);
	aux = ft_strjoin(aux, "\033[0;37m@\033[0;32mminishell\033[0;37m:");
	logname = ft_strjoin(BRED, path);
	aux = ft_strjoin(aux, logname);
	aux = ft_strjoin(aux, "\033[0;37m$ \033[0m");
	free(logname);
	return (aux);
}
