/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:42:33 by yparthen          #+#    #+#             */
/*   Updated: 2024/06/08 18:28:55 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Returns the length of a list	*/
int	ft_lstsize(t_list *lst)
{
	int	k;

	k = 0;
	while (lst != NULL)
	{
		k++;
		lst = lst->next;
	}
	return (k);
}
