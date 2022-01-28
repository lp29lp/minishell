/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 06:17:25 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/28 18:50:31 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Print the current directory */
void	print_pwd(t_struct *mode)
{
	char	path[3000];
	int		i;

	g_status = 0;
	i = count_split(mode, 0);
	getcwd(path, 3000);
	ft_putendl_fd(path, 1);
}
