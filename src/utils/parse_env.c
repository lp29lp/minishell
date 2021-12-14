/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:53:47 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/14 20:28:38 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_env(t_struct *mode, char **env)
{
	//TODO: --------------cut all env and put in stack--------------------------
	int			i;
	t_list_env	temp;

	temp = mode->env;
	i = 0;
	while (env[i] != NULL)
	{
		filter_env(env[i], mode);
		i++;
	}
}

void	filter_env(char *env, t_struct *mode)
{
	int		size_key;
	int		i;

	size_key = 0;
	i = 0;
	while (env[i++] != "=") // \n
		size_key++;
	i += 1;
	while (env[i++] != NULL)

	
}
