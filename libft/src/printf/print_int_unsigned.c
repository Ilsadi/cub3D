/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:26:39 by amacaull          #+#    #+#             */
/*   Updated: 2025/12/05 10:09:22 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_int(va_list *args, t_flags *f)
{
	int		n;
	long	nb;
	int		count;

	n = va_arg(*args, int);
	nb = (long)n;
	count = 0;
	if (nb < 0)
	{
		count += ft_putchar_count('-');
		nb = -nb;
	}
	else
	{
		if (f && f->plus)
			count += ft_putchar_count('+');
		else if (f && f->space)
			count += ft_putchar_count(' ');
	}
	count += ft_putnbr_recursive(nb);
	return (count);
}

int	print_unsigned(va_list *args)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	return (ft_putunbr_recursive(n));
}
