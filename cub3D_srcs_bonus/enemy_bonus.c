/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:41:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/11 21:45:12 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	load_enemy(t_cub *cub)
{
	ft_printf("Loading enemy...... ");
	if (cub->cmap->s_enemy)
	{
		cub->enemy = ft_calloc(1, sizeof(t_enemy));
		if (!cub->enemy)
			ft_error_handler(ERROR_MEM, cub);
		cub->enemy->sprites = ft_calloc(1, sizeof(t_list **));
		if (!cub->enemy->sprites)
			ft_error_handler(ERROR_MEM, cub);
		ft_loadimgs(cub->cmap->s_enemy, cub->enemy->sprites, 1, cub);
		cub->enemy->current = (*cub->enemy->sprites)->content;
	}
	ft_printf("OK!\n");
}

void	move_enemy(t_enemy *enemy, t_cub *cub)
{
	t_list	*lst;

	if (enemy)
	{
		lst = *enemy->sprites;
		while (lst)
		{
			if (cub->enemy->current == lst->content)
			{
				if (lst->next)
					cub->enemy->current = lst->next->content;
				else
					cub->enemy->current = 0;
				break ;
			}
			lst = lst->next;
		}
		if (!cub->enemy->current || !lst)
			cub->enemy->current = ((t_list *)*cub->enemy->sprites)->content;
	}
}
