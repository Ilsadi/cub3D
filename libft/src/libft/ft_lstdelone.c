/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:19:59 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/06 11:37:47 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}

/*void	del_content(void *content)
{
	free(content);
}

void	print_list(t_list *head)
{
	t_list *tmp = head;

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
	char	*data1 = strdup("Salut");
	char	*data2 = strdup("ca va ?");
	t_list	*node1 = ft_lstnew(data1);
	t_list	*node2 = ft_lstnew(data2);

	if (!data1 || !data2)
		return (1);
	node1->next = node2;
	print_list(node1);
	node1->next = NULL; //dangling
	ft_lstdelone(node2, del_content);
	printf("\n");
	print_list(node1);
	ft_lstdelone(node1, del_content);
	return (0);
}*/
