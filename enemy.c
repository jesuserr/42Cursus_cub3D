/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:41:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/09 17:48:57 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		ft_loadimgs(cub->cmap->s_enemy, cub->enemy->sprites, cub);
		cub->enemy->current = (*cub->enemy->sprites)->content;
	}
	ft_printf("OK!\n");
}
