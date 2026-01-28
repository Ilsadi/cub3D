/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:56:28 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/04 17:55:27 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
		i++;
	if (i < n)
		return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
	return (0);
}

/*int	main(void)
{
	char buffer1[] = "Salut ca va ?";
	char buffer2[] = "Salut3jrnf ca va ?";
	size_t n = sizeof(buffer1);

	printf("%d\n", ft_memcmp(buffer1, buffer2, n));
	printf("%d\n", memcmp(buffer1, buffer2, n));
	return 0;
}*/
