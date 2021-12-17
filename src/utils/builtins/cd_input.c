/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:50:10 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/17 03:14:06 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* need deal with ~ - .. ../../ */
void	cmd_cd(t_struct *mode)
{
	char	path[3000];

	if (chdir("..") != 0)
		printf("minishell: cd: %s: No such file or directory\n",
				mode->split_input[1]);

}