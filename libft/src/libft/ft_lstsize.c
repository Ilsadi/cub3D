/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:43:56 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/05 15:47:03 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/*int	main(void)
{
	t_list	*node1 = ft_lstnew("1");
	t_list	*node2 = ft_lstnew("2");
	t_list	*node3 = ft_lstnew("3");
	t_list	*head;
	int		size;

	head = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	size = ft_lstsize(head);
	printf("%d\n", size);
	free(node1);
	free(node2);
	free(node3);
	return (0);
}*/
