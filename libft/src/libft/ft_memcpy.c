/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:53:35 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/06 11:58:44 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
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
	char src[] = "Salut";
	char dst1[10];
	char dst2[10];
	size_t n = 10;

	memset(dst1, 'A', sizeof(dst1));
	memset(dst2, 'A', sizeof(dst2));
	print_bytes(src, sizeof(src));
	print_bytes(dst1, sizeof(dst1));
	print_bytes(dst2, sizeof(dst2));
	ft_memcpy(dst1, src, n);
	memcpy(dst2, src, n);
	printf("\n");
	print_bytes(dst1, sizeof(dst1));
	print_bytes(dst2, sizeof(dst2));
	return 0;
}*/
