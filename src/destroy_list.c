/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yparthen <yparthen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:32:58 by yparthen          #+#    #+#             */
/*   Updated: 2024/05/18 18:56:31 by yparthen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void destroy_list(t_pipex *p)
{
    int k;
    if (p->cmd_1)
    {
        if (p->cmd_1->args)
        {
            k = 0;
            while (p->cmd_1->args[k])
            {
                free(p->cmd_1->args[k]);
                k++;
            }
             free(p->cmd_1->args);
        }
		//  if (p->cmd_1->pathname)
		// 	 free(p->cmd_1->pathname);
        free(p->cmd_1);
    }
    if (p->cmd_2)
    {
        if (p->cmd_2->args)
        {
            k = 0;
            while (p->cmd_2->args[k])
            {
                free(p->cmd_2->args[k]);
				//ft_printf("free cmd_2 ok\n");
                k++;
            }
            free(p->cmd_2->args);
        }
		//  if (p->cmd_2->pathname)
        //  	free(p->cmd_2->pathname);
        free(p->cmd_2);
    }

    if (p->env_path)
    {
        k = 0;
        while (p->env_path[k])
        {
            free(p->env_path[k]);
            k++;
        }
        free(p->env_path);
    }
}