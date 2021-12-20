/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:21:00 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/20 03:53:00 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Need test if work with more than one sigaction using the same struct in while or out
		===WORKS WITH MULTIPLE DECLARATION IN THE SAME STRUCT  */
void	test_sig(int sig, void (*handler)(int), struct sigaction *sa)
{
	sa->sa_handler = handler;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(sig, sa, NULL);
}

void	handle_sigint(int num)
{
	(void)num;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);//clear the line if something was write previous
	rl_on_new_line();//put the line when c+c was pressed in the line again (need 2 c+c to redisplay)
	rl_redisplay();//do on_new_line appear instantaneously
}
