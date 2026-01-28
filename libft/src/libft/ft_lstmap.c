/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:46:32 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/08 19:11:21 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			if (del)
				del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}

/*void	*ft_newlsttoupper(void *content)
{
	char *str = strdup((char *)content);
	int i = 0;

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

void	del_content(void *content)
{
	free(content);
}

void	print_list(t_list *lst)
{
	t_list *tmp = lst;

	if (!tmp)
	{
		printf("(liste vide)\n");
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
	t_list *node2 = ft_lstnew(strdup("ca va"));
	t_list *node3 = ft_lstnew(strdup("bien ?"));

	node1->next = node2;
	node2->next = node3;

	t_list *new_list = ft_lstmap(node1, ft_newlsttoupper, del_content);

	print_list(node1);
	printf("\n");
	print_list(new_list);
	ft_lstclear(&node1, del_content);
	ft_lstclear(&new_list, del_content);
	return (0);
}*/
