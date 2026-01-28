/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:04:11 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/05 16:19:22 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

/*int	main(void)
{
	t_list	*node1 = ft_lstnew("1");
	t_list	*node2 = ft_lstnew("2");
	t_list	*node3 = ft_lstnew("3");
	t_list	*new_node = ft_lstnew("4");
	t_list	*head = node1;
	t_list	*tmp;
	t_list *empty = NULL;
	t_list *node1bis = ft_lstnew("1");

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	tmp = head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
	ft_lstadd_back(&head, new_node);
	tmp = head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
	if (empty == NULL)
		printf("NULL\n");
	printf("\n");
	ft_lstadd_back(&empty, node1bis);
	printf("%s\n", (char *)empty->content);
	free(node1);
	free(node2);
	free(node3);
	free(new_node);
	free(node1bis);

	return (0);
}*/
