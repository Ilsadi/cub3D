/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:39:06 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/20 22:38:50 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	if (size != 0 && total_size / size != count)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
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
	size_t nmemb = 10;
	size_t size = sizeof(int);

	int *a = ft_calloc(nmemb, size);
	int *b = calloc(nmemb, size);
	if (!a || !b)
	{
		free(a);
		free(b);
		return (1);
	}
	print_bytes(a, nmemb * size);
	print_bytes(b, nmemb * size);
	free(a);
	free(b);
	return (0);
}*/
