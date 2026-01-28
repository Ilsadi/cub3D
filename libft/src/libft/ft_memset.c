/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:53:06 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/06 12:11:55 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char) c;
		i++;
	}
	return (b);
}

/*int	main(void)
{
	char buf1[20] = "Salut ca va ?";
	char buf2[20] = "Salut ca va ?";
	size_t n = 5;
	int c = '*';

	ft_memset(buf1, c, n);
	memset(buf2, c, n);
	printf("%s\n", buf1);
	printf("%s\n", buf2);
	return 0;
}*/
