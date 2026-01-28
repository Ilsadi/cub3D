/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:39:39 by amacaull          #+#    #+#             */
/*   Updated: 2025/11/06 11:51:35 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}

/*void	ft_lsttoupper(void *content)
{
	char *str = (char *)content;
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
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
	t_list *node2 = ft_lstnew(strdup("ca va"));
	t_list *node3 = ft_lstnew(strdup("bien ?"));

	node1->next = node2;
	node2->next = node3;
	print_list(node1);
	printf("\n");
	ft_lstiter(node1, ft_lsttoupper);
	print_list(node1);
	ft_lstclear(&node1, del_content);
	return (0);
}*/
