/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:56:54 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/16 22:58:23 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* aux to compare 2 string; maybe const char */
int	cmp(const void *string1, const void *string2)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	if (!string1 || !string2)
		return (-1);
	s1 = (unsigned char *)string1;
	s2 = (unsigned char *)string2;
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (1);//can conflit with the other return NEED TEST
}

int	count_split(t_struct *mode)
{

}