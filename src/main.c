/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/13 17:16:31 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	main(int ac, char **av, char **env)
{
	t_struct			mode;
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&mode, 0, sizeof(mode));
	if (ac != 1 || av[1])
		return (0);
	init_struct(&mode);
	save_env(&mode, env);
	jump_sig(SIGINT, handle_sigint, &sa);
	/* jump_sig(SIGQUIT, SIG_IGN, &sa); */
	while (1)
	{
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

	getcwd(path, 3000);
	aux = ft_strdup("\033[0;32mmini\033[0;37m@\033[0;32mshell\033[0;37m:");
	aux1 = ft_strjoin("\033[0;31m", path);
	temp = ft_strjoin(aux, aux1);
	free(aux);
	free(aux1);
	aux = ft_strjoin(temp, "\033[0;37m$\033[0m ");
	free(temp);
	free_null(&mode->line_read);
	mode->line_read = (char *)readline(aux);
	free(aux);
	if (mode->line_read == NULL)
	{
		ft_putchar_fd('\n', 1);
		do_free(mode);
	}
	if (mode->line_read)
		add_history(mode->line_read);
	index_parse(mode);
}
