/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:39:49 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/15 20:05:32 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

extern int	g_status;

typedef struct s_list_env
{
	struct s_list_env	*next;
	char				*key;
	char				*value;
}	t_list_env;

typedef struct s_redic
{
	int	left;
	int	d_left;
	int	right;
	int d_right;
}	t_redic;

typedef struct s_struct
{
	t_redic		*arrow;
	t_list_env	*env;
	int			size_env;
	char		*line_read;
	char		**split_input;
	char		**split_two;
	char		quote;
	char		*left;
	char		*right;
	int			space;
	int			tag;
	int			bkp;

/* redirect session */
	int			redic; //flag
	char		**split_cpy;
	int			fd;
	int			save;
}	t_struct;

#endif
