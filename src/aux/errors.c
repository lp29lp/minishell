/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:51:54 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/11 16:26:41 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Deal with some specific errors of usage from builtins */
void	dollar_error(char *name, t_struct *mode, char *builtin)
{
	t_list_env	*temp;
	char		*info;

	info = NULL;
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
	if (info != NULL)
		printf("minishell: %s: `%s': not a valid identifier\n", builtin, info);
	else
		printf("minishell: %s: `%s': not a valid identifier\n", builtin, name);
	free_null(&info);
}
