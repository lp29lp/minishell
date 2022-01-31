/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:39:49 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/31 03:30:38 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "ansi_color.h"

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
	int			space;
	int			tag;
	int			tag1;
	int			bkp;
	int			count;
	int			count2;
	int			in;
	int			out;
	int			k;
	int			l;
	char		*line_read;
	char		*rest;
	char		**split_input;
	char		**split_two;
	char		**keywords;
	char		quote;
	char		*left;
	char		*right;
	char		*temp;
	char		*aux;

	int			redic;
	int			fd2;
	int			fd1;
	int			tag2;
	int			pid;
	int			size_keywords;
	int			i;
	int			j;
	char		**split_rest;
	char		*xablau;

	int			q_info;
	int			count3;
	int			pipe;
	int			x;
	int			p_fd[2];
	int			p_in;
	char		**split_pipe;

}	t_struct;

#endif
