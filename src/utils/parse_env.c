/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:53:47 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/14 18:06:35 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_env(t_mode *mode, char **env)
{
	//TODO: --------------cut all env and put in stack--------------------------
	t_list	temp;

	if (size_env == 0)
		new_node_env(NULL, mode) //!WORKS??????
	while (*env != NULL)
	{
		new_node_env(env, mode);
		size_env++;
	}
}