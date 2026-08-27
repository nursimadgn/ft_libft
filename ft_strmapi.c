/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seldogan <seldogan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:15:09 by seldogan          #+#    #+#             */
/*   Updated: 2026/08/17 15:15:23 by seldogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str_new;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str_new = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_new)
		return (NULL);
	while (s[i])
	{
		str_new[i] = f(i, s[i]);
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
