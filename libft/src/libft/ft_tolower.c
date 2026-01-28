/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:55:17 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/04 16:33:03 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && 'Z' >= c)
		return (c + 'a' - 'A');
	return (c);
}

/*int main(void)
{
	int test = 85;

	printf("%d\n", ft_tolower(test));
	printf("%d\n", tolower(test));
	return 0;
}*/
