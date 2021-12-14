/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:39:49 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/14 20:05:51 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_list_env
{
	struct s_list_env	next;
	char			*before; //antes
	char			*after; //depois
}	t_list_env;

typedef struct	s_struct
{
	t_list_env	*env;
	int		size_env;
}	t_struct;

#endif