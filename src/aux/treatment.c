/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:13:41 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/02/01 21:30:28 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Do a treatment on string from input, dealing with quote and dollar sing and
 * space for echo */
void	treatment(t_struct *mode, char **str)
{
	int	i;

	i = 0;
	mode->space = 0;
	mode->tag = 1;
	mode->quote = '1';
	while (str[0][i + 1] != '\0')
	{
		if (str[0][i] == '\'' || str[0][i] == '\"')
		{
			get_space(mode, (i + 1), *str);
			mode->quote = str[0][i];
			i = d_quotes(mode, i, str);
		}
		else if (str[0][i] == '$' && mode->quote == '1')
			convert_dollar(mode, i, str);
		else
			i++;
		if (str[0][i] == ' ' && mode->quote == '1')
			i = jump_space(mode, (i + 1), str);
		if (str[0][0] == '\0')
			return ;
		else if (str[0][i] == '\0')
			return ;
	}
}

/* Convert the dollar sign variable into the value stored in linked list */
void	convert_dollar(t_struct *mode, int i, char **str)
{
	char	*name;
	char	*temp;

	name = NULL;
	cat_jump(mode, i, 1, str);
	mode->bkp = i;
	while (str[0][i] != 32 && str[0][i] != 34
		&& str[0][i] != 39 && str[0][i] != '\0')
				i++;
	name = ft_substr(*str, mode->bkp, (i - mode->bkp));
	temp = fix_dollar(mode, name);
	free_null(&name);
	mode->left = ft_substr(*str, 0, mode->bkp);
	name = ft_strjoin(mode->left, temp);
	free_null(&mode->left);
	free_null(&temp);
	mode->right = ft_substr(*str, i, ft_strlen(*str));
	free_null(str);
	*str = ft_strjoin(name, mode->right);
	free_null(&name);
	free_null(&mode->right);
}

/* get value from key but if doesn't exist return void string but this
condition just exist when the previous position is double quote or nothing*/
char	*fix_dollar(t_struct *mode, char *name)
{
	t_list_env	*temp;
	char		*info;
	int			tag;

	tag = 0;
	temp = mode->env;
	if (cmp(name, "?") == 0)
		return (ft_itoa(g_status));
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

/* Treatment when a quote is open */
int	d_quotes(t_struct *mode, int i, char **str)
{
	mode->bkp = i;
	cat_jump(mode, i, 1, str);
	if (mode->quote == '\'' && str[0][i] == '$'
		&& str[0][i + 1] != '\0')
	{
		while (str[0][i] != mode->quote
			&& str[0][i + 1] != '\0')
			i++;
	}
	i = d_quote_cont(mode, i, str);
	if (str[0][i + 1] == '\0' && str[0][i] == mode->quote
		&& i == 0)
	{
		free(*str);
		*str = ft_strdup("");
		i = 0;
	}
	else if (str[0][i] == mode->quote)
		cat_jump(mode, i, 1, str);
	mode->quote = '1';
	return (i);
}

int	d_quote_cont(t_struct *mode, int i, char **str)
{
	while (str[0][i] != mode->quote && str[0][i + 1] != '\0')
	{
		if (mode->quote == '\"' && str[0][i] == '$'
			&& str[0][i + 1] != ' '
			&& str[0][i + 1] != mode->quote)
			convert_dollar(mode, i, str);
		else
			i++;
	}
	return (i);
}
