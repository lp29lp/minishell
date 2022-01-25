/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/25 18:21:07 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	main(int ac, char **av, char **env)
{
	t_struct			mode;
	struct sigaction	sa;

	g_status = 0;
	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&mode, 0, sizeof(mode));
	mode.arrow = ft_calloc(1, sizeof(t_redic));
	mode.in = dup(0);
	mode.out = dup(1);
	if (ac != 1 || av[1])
		return (0);
	save_env(&mode, env);
	while (1)
	{
		jump_sig(SIGINT, handle_sigint, &sa);
		jump_sig(SIGQUIT, SIG_IGN, &sa);
		display_prompt(&mode);
	}
}

/* Display the prompt get input and send to parse */
void	display_prompt(t_struct *mode)
{
	char	path[3000];
	char	*temp;
	char	*aux;
	char	*aux1;

	init_struct(mode);
	getcwd(path, 3000);
	aux = ft_strdup("\033[0;32mmini\033[0;37m@\033[0;32mshell\033[0;37m:");
	aux1 = ft_strjoin("\033[0;31m", path);
	temp = ft_strjoin(aux, aux1);
	free_null(&aux);
	free_null(&aux1);
	aux = ft_strjoin(temp, "\033[0;37m$\033[0m ");
	free_null(&temp);
	mode->line_read = (char *)readline(aux);
	free_null(&aux);
	if (mode->line_read == NULL)
	{
		ft_putchar_fd('\n', 1);
		do_free(mode);
	}
	if (mode->line_read && *mode->line_read)
		add_history(mode->line_read);
	index_parse(mode);
}
