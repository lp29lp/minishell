/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/17 19:16:42 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *todo:	Need deal with close launch to start debug; Start print env
*/

int	main(int ac, char ** av, char **env)
{
	t_struct	mode;

	if (ac != 1 || av[1])
		return (0);
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

/* Get logname and print the path */
char	*put_some_colors(t_struct *mode)
{
	t_list_env	*temp;
	char		*logname;
	char		path[3000];
	char		*aux;
	char		*aux1;

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
	aux1 = ft_strjoin(WHT, "@");
	aux = ft_strjoin(aux, aux1);
	aux1 = ft_strjoin(GRN, "minishell");
	aux = ft_strjoin(aux, aux1);
	aux1 = ft_strjoin(WHT, ":");
	aux = ft_strjoin(aux, aux1);
	aux1 = ft_strjoin(BRED, path);
	aux = ft_strjoin(aux, aux1);
	aux1 = ft_strjoin(WHT, "$ ");
	aux = ft_strjoin(aux, aux1);
	aux = ft_strjoin(aux, reset);
	free(logname);
	return (aux);
}

/* need break line printf can be erased */