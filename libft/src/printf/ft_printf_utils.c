/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:31:29 by amacaull          #+#    #+#             */
/*   Updated: 2025/12/05 10:09:07 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putchar_count(char c)
{
	return ((int)write(1, &c, 1));
}

int	ft_putstr_count(const char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		count += ft_putchar_count(*s);
		s++;
	}
	return (count);
}

int	ft_putnbr_recursive(long n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_recursive(n / 10);
	count += ft_putchar_count((char)((n % 10) + '0'));
	return (count);
}

int	ft_putunbr_recursive(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putunbr_recursive(n / 10);
	count += ft_putchar_count((char)((n % 10) + '0'));
	return (count);
}

int	ft_puthex_recursive(unsigned long n, int uppercase)
{
	int			count;
	const char	*base;

	count = 0;
	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		count += ft_puthex_recursive(n / 16, uppercase);
	count += ft_putchar_count(base[n % 16]);
	return (count);
}
