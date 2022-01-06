/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:39:36 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/04 20:25:19 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* See what was the input and redirect */
void	parse_input_0(t_struct *mode)
{
	if (cmp(mode->split_input[0], "cd") == 0)
		cmd_cd(mode);
	if (cmp(mode->split_input[0], "env") == 0)
		print_env(mode);
	if (cmp(mode->split_input[0], "pwd") == 0)
		print_pwd(mode);
	if (cmp(mode->split_input[0], "export") == 0)
		cmd_export(mode);
	if (cmp(mode->split_input[0], "unset") == 0)
		cmd_unset(mode);
}

