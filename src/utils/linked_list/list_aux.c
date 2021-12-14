/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:56:25 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/14 18:08:42 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_mode	new_node_env(char *env, t_mode *mode)
{
	t_list	*new;

	new = (t_list *)ft_calloc(ft_strlen(env), sizeof(t_list)) //!strlen maybe use when cut the words
}

void	init_struct(t_mode *mode)
{
	mode->size_env = 0;
}