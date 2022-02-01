/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:21:00 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/02/01 15:16:30 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

/* Add a specific handler to struct sigaction and send to sigaction function */
void	jump_sig(int sig, void (*handler)(int), struct sigaction *sa)
{
	sa->sa_handler = handler;
	sigaction(sig, sa, NULL);
}

/* Deal with C+c and redisplay the prompt */
void	handle_sigint(int num)
{
	(void)num;
	ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

/* Deal with C+c and display a new line when is in heredoc
and set status to C+c(130) */
void	handle_redic(int num)
{
	(void)num;
	unlink("xablau");
	ft_putendl_fd("", 1);
	exit(130);
}

/* Deal with C+c and set status to C+c(130) */
void	handle_exec(int num)
{
	(void)num;
	ft_putendl_fd("", 1);
	g_status = 130;
}
