/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:26:34 by amacaull          #+#    #+#             */
/*   Updated: 2025/12/05 10:09:16 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_char(va_list *args)
{
	char	c;

	c = (char)va_arg(*args, int);
	return (ft_putchar_count(c));
}

int	print_string(va_list *args)
{
	char	*s;

	s = va_arg(*args, char *);
	if (!s)
		return (ft_putstr_count("(null)"));
	return (ft_putstr_count(s));
}
