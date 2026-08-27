/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seldogan <seldogan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:15:50 by seldogan          #+#    #+#             */
/*   Updated: 2026/08/17 15:15:51 by seldogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		count;
	char	*newstr;

	i = 0;
	j = 0;
	count = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (j >= i && ft_strchr(set, s1[j]))
		j--;
	if (i > j)
		return (ft_strdup(""));
	count = j - i + 1;
	newstr = (char *)malloc(sizeof(char) * (count + 1));
	if (!newstr)
		return (NULL);
	ft_memcpy(newstr, s1 + i, count);
	newstr[count] = '\0';
	return (newstr);
}
