/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:23:50 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/17 13:36:11 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_flags
{
	int	plus;
	int	space;
	int	hash;
	int	is_spec_final;
}	t_flags;

int		ft_printf(const char *format, ...);
int		ft_vprintf(const char *format, va_list ap);
void	parse_bonus_flags(const char **fmt, t_flags *f);
int		dispatcher(char spec, va_list *args, t_flags *f);
int		print_char(va_list *args);
int		print_string(va_list *args);
int		print_int(va_list *args, t_flags *f);
int		print_unsigned(va_list *args);
int		print_hex_lower(va_list *args, t_flags *f);
int		print_hex_upper(va_list *args, t_flags *f);
int		print_pointer(va_list *args);
int		ft_putchar_count(char c);
int		ft_putstr_count(const char *s);
int		ft_putnbr_recursive(long n);
int		ft_putunbr_recursive(unsigned int n);
int		ft_puthex_recursive(unsigned long n, int uppercase);
char	*ft_strchr(const char *s, int c);

#endif
