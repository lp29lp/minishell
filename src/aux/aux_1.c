/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:13:41 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/08 07:15:50 by lpaulo-d         ###   ########.fr       */
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

/* Do a treatment on string input dealing with quote and dollar sing */
void	treatment(t_struct *mode)
{
	int		i;

	i = 0;
	if (mode->line_read[i] == ' ')
	{
		while (mode->line_read[i] == ' ')
			i++;
		cat_jump(mode, i, 0);
	}
	i = 0;
	mode->quote = '1';
	while (mode->line_read[i + 1] != '\0')
	{
		if (mode->line_read[i] == '\'' || mode->line_read[i] == '\"')
		{
			mode->quote = mode->line_read[i];
			i = d_quotes(mode, i);
		}
		else if (mode->line_read[i] == '$' && mode->quote == '1')
				convert_dollar(mode, i);
		else
			i++;
	}
}

/* Conver the dollar sign variable into the value stored in linked list */
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

/* Treatment when one quote is open */
int	d_quotes(t_struct *mode, int i)
{
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
	if (mode->line_read[i + 1] != '\0')
		cat_jump(mode, i, 1);
	mode->quote = '1';
	return (i);
}

/* Tag != 1 when need remove space from beginning
 * if one will remove one character in specific in the string */
void	cat_jump(t_struct *mode, int i, int tag)
{

	if (tag == 1)
	{
		mode->left = ft_substr(mode->line_read, 0, i);
		mode->right = ft_substr(mode->line_read, (i+1), ft_strlen(mode->line_read));
		free_null(&mode->line_read);
		mode->line_read = ft_strjoin(mode->left, mode->right);
		free_null(&mode->left);
		free_null(&mode->right);
		return ;
	}
	else
	{
		mode->right = ft_substr(mode->line_read, i, ft_strlen(mode->line_read));
		free_null(&mode->line_read);
		mode->line_read = ft_strdup(mode->right);
		free_null(&mode->right);
		return ;
	}
}

