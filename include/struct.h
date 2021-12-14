/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:39:49 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/14 18:03:24 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_list
{
	struct s_list	next;
	char			*before; //antes
	char			*after; //depois
}	t_list;

typedef struct	s_mode
{
	t_list	*env;
	int		size_env;
}	t_mode;

#endif