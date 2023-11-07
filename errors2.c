/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:51:22 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/07 20:53:12 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_dellsti(void *img)
{
	if (((t_txt *)img)->img.img)
		mlx_destroy_image(((t_txt *)img)->img.mlx, ((t_txt *)img)->img.img);
	if (((t_txt *)img))
		free(((t_img *)img));
}

void	free_sprites(t_cub *cub)
{
	if (cub->enemy && cub->enemy->sprites)
	{
		ft_lstclear(cub->enemy->sprites, ft_dellsti);
		free(cub->enemy->sprites);
	}
	if (cub->enemy)
		free(cub->enemy);
}
