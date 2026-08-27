/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seldogan <seldogan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:15:30 by seldogan          #+#    #+#             */
/*   Updated: 2026/08/17 19:05:27 by seldogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	new_len;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	new_len = ft_strlen(little);
	while (i + new_len <= len && big[i])
	{
		j = 0;
		while (big[i + j] && little[j] && (i + j) < len && big[i
				+ j] == little[j])
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
