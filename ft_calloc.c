/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seldogan <seldogan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:27:39 by seldogan          #+#    #+#             */
/*   Updated: 2026/08/17 14:27:40 by seldogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	void			*ptr;
	unsigned char	*p;

	if (count != 0 && size > (size_t)-1 / count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < (count * size))
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
