/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:13:41 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/09 18:33:54 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Do a treatment on string input dealing with quote and dollar sing and space
 * for echo */
void	treatment(t_struct *mode)
{
	int	i;

	i = 0;
	mode->space = 0;
	mode->tag = 1;
	mode->quote = '1';
	while (mode->line_read[i + 1] != '\0')
	{
		if (mode->line_read[i] == '\'' || mode->line_read[i] == '\"')
		{
			get_space(mode, (i + 1));
			mode->quote = mode->line_read[i];
			i = d_quotes(mode, i);
		}
		else if (mode->line_read[i] == '$' && mode->quote == '1')
				convert_dollar(mode, i);
		else
			i++;
		if (mode->line_read[i] == ' ' && mode->quote == '1')
			i = jump_space(mode, i + 1);
		if (mode->line_read[0] == '\0')
			return ;
		else if (mode->line_read[i] == '\0')
			return ;
	}
}

/* remove space out of quotes and just leaves only one space or no space */
int	jump_space(t_struct *mode, int i)
{
	while (mode->line_read[i] == ' ')
	{
		cat_jump(mode, i, 1);
	}
	if (mode->line_read[i] == '\0')
	{
		cat_jump(mode, (i - 1), 1);
		return (i -= 2);
	}
	return (i);
}

/* Convert the dollar sign variable into the value stored in linked list */
void	convert_dollar(t_struct *mode, int i)
{
	int		bkp;
	char	*name;
	char	*temp;

	name = NULL;
	cat_jump(mode, i, 1);
	bkp = i;
	while (mode->line_read[i] != 32 && mode->line_read[i] != 34
			&& mode->line_read[i] != 39 && mode->line_read[i] != '\0')
				i++;
	name = ft_substr(mode->line_read, bkp, (i - bkp));
	temp = fix_dollar(mode, name);
	free_null(&name);
	mode->left = ft_substr(mode->line_read, 0, bkp);
	name = ft_strjoin(mode->left, temp);
	free_null(&mode->left);
	free_null(&temp);
	mode->right = ft_substr(mode->line_read, i, ft_strlen(mode->line_read));
	free_null(&mode->line_read);
	mode->line_read = ft_strjoin(name, mode->right);
	free_null(&name);
	free_null(&mode->right);
}

/* get value from key but if doesn't exist return void string but this
 * condition just exist when the previous position is double quote or nothing*/
char	*fix_dollar(t_struct *mode, char *name)
{
	t_list_env	*temp;
	char		*info;
	int			tag;

	tag = 0;
	temp = mode->env;
	while (temp != NULL)
	{
		if (cmp(temp->key, name) == 0)
		{
			info = ft_strdup(temp->value);
			return (info);
		}
		temp = temp->next;
	}
	info = ft_strdup("");
	return (info);
}

void	get_space(t_struct *mode, int i)
{
	if (mode->tag == 1)
	{
		while (mode->line_read[i] == ' ')
		{
			i++;
			mode->space++;
		}
		mode->tag = 0;
	}
	return ;
}

/* Treatment when one quote is open */
int	d_quotes(t_struct *mode, int i)
{
	int bkp;
	bkp = i;
	cat_jump(mode, i, 1);
	if (mode->quote == '\'' && mode->line_read[i] == '$')
	{
		while (mode->line_read[i] != mode->quote)
			i++;
	}
	while (mode->line_read[i] != mode->quote && mode->line_read[i + 1] != '\0')
	{
		if (mode->quote == '\"' && mode->line_read[i] == '$')
			convert_dollar(mode, i);
		else if (mode->line_read[i] == '$' && mode->line_read[i - 1] != '\''
				&& mode->line_read[i - 1] != '\"')
			convert_dollar(mode, i);
		else
			i++;
	}
	if (mode->line_read[i + 1] == '\0' &&	mode->line_read[i] == mode->quote
		&& bkp == i)
	{
		free(mode->line_read);
		mode->line_read = ft_strdup("");
		i = 0;
	}
	else if (mode->line_read[i] == mode->quote)
		cat_jump(mode, i, 1);
	mode->quote = '1';
	return (i);
}

