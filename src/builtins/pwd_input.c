/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 06:17:25 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/03 05:53:10 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_pwd(t_struct *mode)
{
	char	path[3000];
	int		i;

	i = count_split(mode);
	if (i == 1)
	{
		getcwd(path, 3000);
		ft_putendl_fd(path, 1);
	}
}
