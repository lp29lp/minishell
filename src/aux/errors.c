/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:51:54 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/08 16:52:54 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Deal with some specific errors of usage from builtins */
void	dollar_error(char *var, t_struct *mode, char *builtin)
{
	t_list_env	*temp;
	char		*name;
	char		*info;

	info = NULL;
	name = ft_strtrim(var, "$");
	free_null(&var);
	temp = mode->env;
	while (temp != NULL)
	{
		if (cmp(temp->key, name) == 0)
		{
			info = ft_strdup(temp->value);
			free(name);
			break;
		}
		temp = temp->next;
	}
	printf("minishell: %s: `%s': not a valid identifier", builtin, info);
	free_null(&info);
}
