/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 10:51:41 by amacaull          #+#    #+#             */
/*   Updated: 2025/12/05 10:09:14 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	parse_bonus_flags(const char **fmt, t_flags *f)
{
	if (!fmt || !*fmt || !f)
		return ;
	f->plus = 0;
	f->space = 0;
	f->hash = 0;
	while (**fmt == '+' || **fmt == ' ' || **fmt == '#')
	{
		if (**fmt == '+')
			f->plus = 1;
		else if (**fmt == ' ')
			f->space = 1;
		else if (**fmt == '#')
			f->hash = 1;
		(*fmt)++;
	}
	if (f->plus)
		f->space = 0;
}
