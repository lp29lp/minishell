/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:05 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/14 20:05:01 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//todo: see how to use readline to wait a input
//* include libft / do Makefile
int	main(int ac, char **av, char **env)
{
	t_struct	mode;

	parse_env(&mode, &env);
}