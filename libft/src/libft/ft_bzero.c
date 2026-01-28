/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:38:40 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/05 14:45:52 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

/*void	print_bytes(const void *s, size_t n)
{
	const unsigned char *p = s;
	size_t i = 0;

	while (i < n)
	{
		printf("%02X ", p[i]);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	char buffer1[10] = "123456789";
	char buffer2[10] = "123456789";

	print_bytes(buffer1, 10);
	print_bytes(buffer2, 10);
	ft_bzero(buffer1, 6);
	bzero(buffer2, 6);
	print_bytes(buffer1, 10);
	print_bytes(buffer2, 10);
	return 0;
}*/
