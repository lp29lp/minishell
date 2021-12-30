/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/30 18:42:45 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *todo:	Need deal with close launch to start debug; signal to close could need do another things first;
 *!logname wasn't working i think now don't have leak only in readline but 'split' and 'join' can have some leak
*/

int	main(int ac, char ** av, char **env)
{
	t_struct			mode;
	struct sigaction	sa;

	if (ac != 1 || av[1])
		return (0);
	init_struct(&mode);
	save_env(&mode, env);

	/* Tem alguma magica nesses sinais q funfa usando a mesma variavel */
	test_sig(SIGINT, handle_sigint, &sa);
	test_sig(SIGKILL, SIG_IGN, &sa);
	test_sig(SIGQUIT, SIG_IGN, &sa);
	test_sig(SIGTSTP, SIG_IGN, &sa);
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
	char	path[3000];
	char	*temp;
	char	*aux;
	char	*aux1;

	getcwd(path, 3000);
	aux = ft_strdup("\033[0;32mmini\033[0;37m@\033[0;32mshell\033[0;37m:");
	aux1 = ft_strjoin("\033[0;31m", path);
	temp = ft_strjoin(aux, aux1);
	free(aux);
	free(aux1);
	aux = ft_strjoin(temp, "\033[0;37m$\033[0m ");
	free(temp);
	mode->line_read = (char *)readline(aux);
	free(aux);
	if (mode->line_read == NULL)
	{
		ft_putchar_fd('\n', 1);
		do_free(mode);
	}
	if (mode->line_read)
		add_history(mode->line_read);
	// if (mode->split_input != NULL)
	free_split(mode);
	mode->split_input = ft_split(mode->line_read, ' ');
	free(mode->line_read);
	parse_input_0(mode);
}


