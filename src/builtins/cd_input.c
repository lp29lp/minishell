/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:50:10 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/17 23:06:41 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_cd(t_struct *mode)
{
	int	size_split_input;

	size_split_input = count_split(mode);
	if (size_split_input > 2)
	{
		ft_putendl_fd("minishell: cd: Too many arguments", 1);
		return ;
	}
	if (size_split_input == 1 || cmp(mode->split_input[1], "~") == 0)
	{
		cd_home(mode);
		return ;
	}
	if (cmp(mode->split_input[1], "-") == 0)
	{
		cd_oldpwd(mode);
		return ;
	}
	else
		cd_normal(mode);
	return ;
}

/* go to a certain directory */
void	cd_normal(t_struct	*mode)
{
	char	old[3000];
	char	new[3000];

	getcwd(old, 3000);
	if (chdir(mode->split_input[1]) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n",
				mode->split_input[1]);
		return ;
	}
	else
	{
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
