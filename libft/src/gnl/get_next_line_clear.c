/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_clear.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:00:26 by amacaull          #+#    #+#             */
/*   Updated: 2025/12/09 14:47:50 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_clear(int fd)
{
	char	**stash;

	if (fd < 0 || fd >= MAX_FD)
		return ;
	stash = gnl_stash_ptr();
	if (stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
}
