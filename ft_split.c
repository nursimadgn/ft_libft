/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seldogan <seldogan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:13:23 by seldogan          #+#    #+#             */
/*   Updated: 2026/08/17 15:13:24 by seldogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_word_number(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	*free_all(char **array2d, int j)
{
	while (j >= 0)
	{
		free(array2d[j]);
		j--;
	}
	free(array2d);
	return (NULL);
}

static char	**fill_split(char **array2d, char const *s, char c, int words)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		array2d[j] = ft_substr(s, start, i - start);
		if (!array2d[j])
			return (free_all(array2d, j));
		j++;
	}
	array2d[j] = NULL;
	return (array2d);
}

char	**ft_split(char const *s, char c)
{
	char	**array2d;
	int		word_number;

	if (!s)
		return (NULL);
	word_number = find_word_number(s, c);
	array2d = (char **)malloc(sizeof(char *) * (word_number + 1));
	if (!array2d)
		return (NULL);
	return (fill_split(array2d, s, c, word_number));
}
