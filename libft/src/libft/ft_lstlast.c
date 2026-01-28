/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:50:34 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/05 15:59:39 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*int	main(void)
{
	t_list	*node1 = ft_lstnew("1");
	t_list	*node2 = ft_lstnew("2");
	t_list	*node3 = ft_lstnew("3");
	t_list	*last;

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	last = ft_lstlast(node1);
	printf("%s\n", (char *)last->content);
	last = ft_lstlast(NULL);
	if (!last)
		printf("NULL");
	free(node1);
	free(node2);
	free(node3);
	return (0);
}*/
