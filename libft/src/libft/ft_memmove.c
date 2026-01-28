/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:54:12 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/10 11:49:15 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest1;
	unsigned char	*src1;

	if (!dest && !src)
		return (NULL);
	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	if (src1 < dest1)
	{
		i = n;
		while (i-- > 0)
			dest1[i] = src1[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest1[i] = src1[i];
			i++;
		}
	}
	return (dest);
}

/*int	main(void)
{
	char buffer1[30] = "Salut ca va ?";
	char buffer2[30] = "Salut ca va ?";
	char buffer3[30] = "Salut ca va ?";
	char buffer4[30] = "Salut ca va ?";

	ft_memmove(buffer1 + 4, buffer1, 10);
	memmove(buffer2 + 4, buffer2, 10);
	printf("%s\n", buffer1);
	printf("%s\n", buffer2);
	ft_memmove(buffer3, buffer3 + 4, 10);
	memmove(buffer4, buffer4 + 4, 10);
	printf("%s\n", buffer3);
	printf("%s\n", buffer4);
	return 0;
}*/
