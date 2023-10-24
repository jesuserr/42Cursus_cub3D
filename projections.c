/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/24 10:43:39 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	projection(t_cub *cub)
{
	int		i;
	t_point	square;

	printf("%6.2d %6.2d\n", cub->player.x_pos, cub->player.y_pos);
	i = 0;
	while (i < (cub->x_elem * cub->y_elem))
	{
		square.x = cub->map[i].x;
		square.y = cub->map[i].y;
		square.color = cub->map[i].color;
		if (square.color != 0)
			draw_square(cub, square, WALL_SIZE);
		i++;
	}
	square.x = cub->player.x_pos - WALL_SIZE / 8;
	square.y = cub->player.y_pos - WALL_SIZE / 8;
	square.color = 0xFFFFFF;
	draw_square(cub, square, WALL_SIZE / 4);
	mlx_put_pixel(cub, cub->player.x_pos, cub->player.y_pos, DEF_COLOR);
	draw_pointer(cub);
}
