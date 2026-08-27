/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seldogan <seldogan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:15:54 by seldogan          #+#    #+#             */
/*   Updated: 2026/08/18 16:06:26 by seldogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	i;
	char	*ptr_s;

	i = 0;
	len_s = 0;
	if (!s)
		return (NULL);
	while (s[len_s])
		len_s++;
	if (len > (len_s - start))
		len = len_s - start;
	if (start > len_s + 1)
		len = 0;
	ptr_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr_s)
		return (NULL);
	while (len > 0)
	{
		ptr_s[i] = s[start + i];
		i++;
		len--;
	}
	ptr_s[i] = '\0';
	return (ptr_s);
}
