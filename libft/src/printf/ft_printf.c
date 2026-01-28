/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:24:32 by amacaull          #+#    #+#             */
/*   Updated: 2025/12/05 10:09:10 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	handle_conversion(const char **p, va_list *args)
{
	t_flags	f;

	f.plus = 0;
	f.space = 0;
	f.hash = 0;
	f.is_spec_final = 0;
	(*p)++;
	parse_bonus_flags(p, &f);
	f.is_spec_final = (*(*p + 1) == '\0');
	return (dispatcher(**p, args, &f));
}

int	ft_vprintf(const char *format, va_list ap)
{
	va_list		args;
	const char	*p;
	int			total;

	p = format;
	total = 0;
	if (!format)
		return (-1);
	va_copy(args, ap);
	while (*p)
	{
		if ((*p == '%') && *(p + 1))
			total += handle_conversion(&p, &args);
		else
			total += ft_putchar_count(*p);
		p++;
	}
	va_end(args);
	return (total);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}
