/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seldogan <seldogan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:29:09 by seldogan          #+#    #+#             */
/*   Updated: 2026/08/17 16:38:08 by seldogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	find_digit(long int n)
{
	int	res;

	res = 0;
	if (n <= 0)
	{
		n = -n;
		res++;
	}
	while (n > 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	long int	number;
	long int	digit_num;
	char		*str;

	number = n;
	digit_num = 0;
	digit_num = find_digit(number);
	str = (char *)malloc(sizeof(char) * (digit_num + 1));
	if (!str)
		return (NULL);
	str[digit_num] = '\0';
	if (number == 0)
		str[0] = '0';
	if (number < 0)
	{
		str[0] = '-';
		number = -number;
	}
	while (number > 0)
	{
		str[--digit_num] = (number % 10) + 48;
		number /= 10;
	}
	return (str);
}
