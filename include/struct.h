/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:39:49 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/22 17:01:37 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "ansi_color.h"
extern int	g_status;

typedef struct s_list_env
{
	struct s_list_env	*next;
	char				*key;
	char				*value;
}	t_list_env;

typedef struct s_redic
{
	int		twice;
	int		once;
	int		left;
	int		right;
	char	redic;
}	t_redic;

typedef struct s_struct
{
	t_redic		*arrow;
	t_list_env	*env;
	int			size_env;
	char		*line_read;
	char		**split_input;
	char		**split_two;
	char		**keywords;
	char		quote;
	char		*left;
	char		*right;
	int			space;
	int			tag;
	int			bkp;
	int			count;
	int			count2;
	char		*temp;
	char		*aux;
	int			in;
	int			out;
/* redirect session */
	int			redic; //flag
	char		**split_cpy;
	int			fd2;
	int			fd1;
	int			tag2;
	int			size_keywords;
	char		*xablau;
}	t_struct;

#endif
