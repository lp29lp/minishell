/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:50:10 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/28 18:58:22 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

/* Jump to a directory */
void	cmd_cd(t_struct *mode)
{
	int	size_split_input;

	g_status = 0;
	size_split_input = count_split(mode, 0);
	if (size_split_input > 2)
	{
		g_status = 1;
		ft_putendl_fd("minishell: cd: Too many arguments", 1);
		return ;
	}
	else if (size_split_input == 1 || cmp(mode->split_input[1], "~") == 0)
	{
		cd_home(mode);
		return ;
	}
	else if (cmp(mode->split_input[1], "-") == 0)
	{
		cd_oldpwd(mode);
		return ;
	}
	else if (mode->split_input[1] != NULL)
		cd_normal(mode);
	return ;
}

/* go to a certain directory */
void	cd_normal(t_struct *mode)
{
	char	old[3000];
	char	new[3000];
	char	*c_temp;
	char	*c_aux;

	c_temp = ft_strtrim(mode->split_input[1], "\'");
	c_aux = ft_strtrim(c_temp, "\"");
	free_null(&c_temp);
	getcwd(old, 3000);
	if (chdir(c_aux) != 0)
	{
		g_status = 1;
		printf("minishell: cd: %s: No such file or directory\n",
			mode->split_input[1]);
		free_null(&c_aux);
		return ;
	}
	else
	{
		free_null(&c_aux);
		getcwd(new, 3000);
		env_change_value(mode, "OLDPWD", old);
		env_change_value(mode, "PWD", new);
	}
}

/* move to old directory and change the value from env_stack */
void	cd_oldpwd(t_struct *mode)
{
	char		old[3000];
	char		*new;
	t_list_env	*temp;

	temp = mode->env;
	new = NULL;
	while (temp)
	{
		if (cmp(temp->key, "OLDPWD") == 0)
		{
			new = ft_strdup(temp->value);
			break ;
		}
		temp = temp->next;
	}
	getcwd(old, 3000);
	chdir(new);
	env_change_value(mode, "OLDPWD", old);
	env_change_value(mode, "PWD", new);
	ft_putendl_fd(new, 1);
	free(new);
}

/* move to home and change the value from env_stack */
void	cd_home(t_struct *mode)
{
	char		old[3000];
	char		*home;
	t_list_env	*temp;

	temp = mode->env;
	home = NULL;
	while (temp)
	{
		if (cmp(temp->key, "HOME") == 0)
		{
			home = ft_strdup(temp->value);
			break ;
		}
		temp = temp->next;
	}
	getcwd(old, 3000);
	chdir(home);
	env_change_value(mode, "OLDPWD", old);
	env_change_value(mode, "PWD", home);
	free(home);
}
