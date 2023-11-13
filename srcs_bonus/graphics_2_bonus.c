/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:03:49 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/13 09:43:50 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_square(t_cub *cub, t_point square, int size);
void	on_screen_minimap(t_cub *cub);

void	draw_square(t_cub *cub, t_point square, int size)
{
	int		x;
	int		y;
	int		x_copy;

	y = 0;
	while (y < size)
	{
		x = 0;
		x_copy = square.x;
		while (x < size)
		{
			mlx_put_pixel(cub, x_copy, square.y, square.color);
			x_copy++;
			x++;
		}
		square.y++;
		y++;
	}
}

void	on_screen_minimap(t_cub *cub)
{
	t_point	square;
	int		i;

	if ((cub->x_elem * WALL_SIZE / cub->key.map_scale > WIDTH) || \
	(cub->y_elem * WALL_SIZE / cub->key.map_scale > HEIGHT))
		return ;
	i = 0;
	while (i < (cub->x_elem * cub->y_elem))
	{
		square.x = (cub->map[i].x / WALL_SIZE * cub->key.map_scale) + \
		cub->key.map_x_offset;
		square.y = (cub->map[i].y / WALL_SIZE * cub->key.map_scale) + 10;
		square.color = cub->map[i].color;
		if (square.color != 0)
			draw_square(cub, square, cub->key.map_scale - 1);
		i++;
	}
	square.x = ((cub->player.x_pos - (WALL_SIZE / 2)) * cub->key.map_scale);
	square.y = ((cub->player.y_pos - (WALL_SIZE / 2)) * cub->key.map_scale);
	square.x = (square.x / WALL_SIZE) + cub->key.map_x_offset;
	square.y = (square.y / WALL_SIZE) + 10;
	square.color = 0xFFFFFF;
	draw_square(cub, square, cub->key.map_scale / 2);
}
