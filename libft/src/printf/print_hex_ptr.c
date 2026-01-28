/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:26:37 by amacaull          #+#    #+#             */
/*   Updated: 2025/12/05 10:09:20 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_hex_lower(va_list *args, t_flags *f)
{
	unsigned int	n;
	int				count;

	n = va_arg(*args, unsigned int);
	count = 0;
	if (f && f->hash && n != 0)
		count += ft_putstr_count("0x");
	if (n == 0)
		return (count + ft_putstr_count("0"));
	return (count + ft_puthex_recursive(n, 0));
}

int	print_hex_upper(va_list *args, t_flags *f)
{
	unsigned int	n;
	int				count;

	n = va_arg(*args, unsigned int);
	count = 0;
	if (f && f->hash && n != 0)
		count += ft_putstr_count("0X");
	if (n == 0)
		return (count + ft_putstr_count("0"));
	return (count + ft_puthex_recursive(n, 1));
}

int	print_pointer(va_list *args)
{
	void	*p;

	p = va_arg(*args, void *);
	if (!p)
		return (ft_putstr_count("(nil)"));
	return (ft_putstr_count("0x") + ft_puthex_recursive((unsigned long)p, 0));
}
