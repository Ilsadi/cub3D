/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:47:15 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/04 16:11:10 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/*int main(int ac, char **av)
{
	char *dest = av[2];
	size_t testsize = 8;
	(void)ac;

	ft_strlcpy(dest, av[1], testsize);
	printf("%zu\n", ft_strlcpy(dest, av[1], testsize));
	printf("%s\n", dest);
	return 0;
}*/
