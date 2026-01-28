/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:56:18 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/04 20:08:34 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char buffer[] = "Salut ca va ?";
	int c = '&';
	size_t n = sizeof(buffer);

	void *res1 = ft_memchr(buffer, c, n);
	void *res2 = memchr(buffer, c, n);
	printf("%ld\n", (char *)res1 - buffer);
	printf("%ld\n", (char *)res2 - buffer);
	return 0;
}*/
