/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:54:51 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/04 16:33:51 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && 'z' >= c)
		return (c - 'a' + 'A');
	return (c);
}

/*int main(void)
{
	int test = 97;

	printf("%d\n", ft_toupper(test));
	printf("%d\n", toupper(test));
	return 0;
}*/
