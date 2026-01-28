/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:34:50 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/06 11:57:09 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*current;

	if (lst && del)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			del(current->content);
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}

/*void	del_content(void *content)
{
	free(content);
}

void	print_list(t_list *lst)
{
	t_list *tmp = lst;
	if (!tmp)
	{
		printf("liste vide\n");
		return;
	}
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

int	main(void)
{
	t_list *node1 = ft_lstnew(strdup("Salut"));
	t_list *node2 = ft_lstnew(strdup("ça va"));
	t_list *node3 = ft_lstnew(strdup("bien ?"));

	node1->next = node2;
	node2->next = node3;
	print_list(node1);
	ft_lstclear(&node2, del_content);
	printf("\n");
	print_list(node1);

	return (0);
}*/
