/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:39:49 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/09 18:23:55 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_list_env
{
	struct s_list_env	*next;
	char				*key; //antes
	char				*value; //depois
}	t_list_env;

typedef struct	s_struct
{
	t_list_env	*env;
	int			size_env;
	char		*line_read;//need free
	char		**split_input;//need free
	char		quote;
	char		*left;
	char		*right;
	int			space;
	int			tag;
	char		**split_two;
}	t_struct;

#endif


