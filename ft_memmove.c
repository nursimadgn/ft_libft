/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seldogan <seldogan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:12:01 by seldogan          #+#    #+#             */
/*   Updated: 2026/08/17 15:12:02 by seldogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	const unsigned char	*p_src;

	p_dest = (unsigned char *)dest;
	p_src = (const unsigned char *)src;
	if (p_dest == p_src || n == 0)
		return (dest);
	if (p_dest < p_src)
	{
		while (n--)
			*p_dest++ = *p_src++;
	}
	else
	{
		while (n--)
			p_dest[n] = p_src[n];
	}
	return (dest);
}
