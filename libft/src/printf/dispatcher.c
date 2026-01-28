/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:25:27 by amacaull          #+#    #+#             */
/*   Updated: 2025/12/05 10:09:04 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	handle_invalid(char spec, t_flags *f)
{
	int	count;
	int	has_flag;

	(void)spec;
	count = 0;
	has_flag = (f->hash || f->plus || f->space);
	if (f->is_spec_final)
		return (0);
	if (!has_flag)
		return (0);
	count += ft_putchar_count('%');
	if (f->hash)
		count += ft_putchar_count('#');
	if (f->plus)
		count += ft_putchar_count('+');
	if (f->space)
		count += ft_putchar_count(' ');
	return (count);
}

int	dispatcher(char spec, va_list *args, t_flags *f)
{
	if (spec != 'c' && spec != 's' && spec != 'p'
		&& spec != 'd' && spec != 'i' && spec != 'u'
		&& spec != 'x' && spec != 'X' && spec != '%')
		return (handle_invalid(spec, f));
	if (spec == 'c')
		return (print_char(args));
	if (spec == 's')
		return (print_string(args));
	if (spec == 'd' || spec == 'i')
		return (print_int(args, f));
	if (spec == 'u')
		return (print_unsigned(args));
	if (spec == 'x')
		return (print_hex_lower(args, f));
	if (spec == 'X')
		return (print_hex_upper(args, f));
	if (spec == 'p')
		return (print_pointer(args));
	if (spec == '%')
		return (ft_putchar_count('%'));
	return (ft_putchar_count(spec));
}
