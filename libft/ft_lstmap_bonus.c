/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:57:41 by mquero            #+#    #+#             */
/*   Updated: 2024/11/05 14:58:04 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*newlist;
	t_list	*check;
	t_list	*content;

	temp = lst;
	newlist = NULL;
	while (temp != NULL)
	{
		content = ((f)(temp->content));
		check = ft_lstnew(content);
		if (check == NULL)
		{
			del(content);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&newlist, check);
		}
		temp = temp->next;
	}
	return (newlist);
}
