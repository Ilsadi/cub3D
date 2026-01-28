/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:09:11 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/05 14:44:07 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	int		number = 42;
	char	*text = "Salut ca va ?";

	node1 = ft_lstnew(&number);
	if (!node1)
		return (1);
	printf("%d\n", *(int *)node1->content);
	printf("%p\n", (void *)node1->next);
	node2 = ft_lstnew(text);
	if (!node2)
	{
		free(node1);
		return (1);
	}
	printf("%s\n", (char *)node2->content);
	printf("%p\n", (void *)node2->next);
	free(node1);
	free(node2);
	return (0);
}*/
