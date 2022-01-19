/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:48:13 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/19 16:14:48 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(const char *s, char c)
{
	size_t	i;
	size_t	wrd;

	wrd = 0;
	i = 0;
	while (*s && *s == c)
		s++;
	while (s[i])
	{
		if (i == 0)
			wrd++;
		else if (s[i - 1] == c && s[i] != c)
			wrd++;
		i++;
	}
	return (wrd);
}

static size_t	ft_lenwrd(char const *s, char c)
{
	size_t		size;

	size = 0;
	while (s[size] != '\0' && s[size] != c)
		size++;
	return (size);
}

static char	**ft_free(char **tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	wrd;
	size_t	i;
	size_t	size;

	i = 0;
	wrd = ft_countword(s, c);
	tab = (char **)ft_calloc((wrd + 1), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < wrd)
	{
		while (*s != '\0' && *s == c)
			s++;
		size = ft_lenwrd(s, c);
		tab[i] = ft_substr(s, 0, size);
		if (!tab[i])
			return (ft_free(tab, i));
		s += (size + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
