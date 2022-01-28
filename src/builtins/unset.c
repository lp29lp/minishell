/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:00:55 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/28 18:48:18 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Remove one variable from env */
void	cmd_unset(t_struct *mode)
{
	int	i;
	int	j;

	i = 1;
	g_status = 0;
	while (mode->split_input[i] != NULL)
	{
		j = 0;
		while (mode->split_input[i][j] != '\0')
		{
			if (mode->split_input[i][j] == '$'
				|| mode->split_input[i][j] == '\''
				|| mode->split_input[i][j] == '\"')
			{
				g_status = 1;
				dollar_error(mode->split_input[i], mode, "unset");
				return ;
			}
			j++;
		}
		unset_aux(i, mode);
		i++;
	}
}

/* delete one variable in linked list from env */
void	unset_aux(int i, t_struct *mode)
{
	int			posi;
	t_list_env	*temp;

	posi = 0;
	mode->tag = 0;
	temp = mode->env;
	while (temp != NULL)
	{
		if (cmp(temp->key, mode->split_input[i]) == 0)
		{
			mode->tag = 1;
			break ;
		}
		posi++;
		temp = temp->next;
	}
	if (posi == 0 && mode->tag == 1)
		delete_first(mode);
	else if (temp == NULL && mode->tag == 1)
		delete_end(mode);
	else if (mode->tag == 1)
		delete_mid(mode, posi);
}

void	delete_mid(t_struct *mode, int posi)
{
	t_list_env	*temp;
	t_list_env	*aux;
	int			i;

	temp = mode->env;
	i = 0;
	while (i < (posi - 1))
	{
		temp = temp->next;
		i++;
	}
	aux = temp->next;
	temp->next = aux->next;
	free_null(&aux->key);
	free_null(&aux->value);
	free(aux);
	aux = NULL;
}

void	delete_first(t_struct *mode)
{
	t_list_env	*temp;

	temp = mode->env;
	mode->env = mode->env->next;
	free_null(&temp->key);
	free_null(&temp->value);
	free(temp);
	temp = NULL;
}

void	delete_end(t_struct *mode)
{
	t_list_env	*temp;
	t_list_env	*aux;

	temp = mode->env;
	while (temp->next != NULL)
	{
		aux = temp;
		temp = temp->next;
	}
	if (temp == mode->env)
		mode->env = NULL;
	else
		aux->next = NULL;
	free_null(&temp->key);
	free_null(&temp->value);
	free(temp);
	temp = NULL;
}
