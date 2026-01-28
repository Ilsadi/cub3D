/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:59:30 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/05 13:06:24 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*int	main(void)
{
	int	fd;

	ft_putchar_fd('A', 1);
	ft_putchar_fd('\n', 1);
	fd = open("test_putchar.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	ft_putchar_fd('S', fd);
	ft_putchar_fd('a', fd);
	ft_putchar_fd('l', fd);
	ft_putchar_fd('u', fd);
	ft_putchar_fd('t', fd);
	ft_putchar_fd('\n', fd);
	close(fd);

	return (0);
}*/
