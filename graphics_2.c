/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:03:49 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/01 20:50:13 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	draw_rectangle(t_cub *cub, t_line diagonal)
{
	int		x;
	int		y;
	int		x_copy;
	int		y_copy;

	y = 0;
	y_copy = diagonal.y0;
	while (y < (diagonal.y1 - diagonal.y0))
	{
		x = 0;
		x_copy = diagonal.x0;
		while (x < (diagonal.x1 - diagonal.x0))
		{
			mlx_put_pixel(cub, x_copy, y_copy, diagonal.color);
			x_copy++;
			x++;
		}
		y_copy++;
		y++;
	}
}

void	on_screen_minimap(t_cub *cub)
{
	int		i;
	t_point	square;
	int		scale;
	int		x_map_offset;

	scale = WIDTH / cub->x_elem / 5.0;
	x_map_offset = (WIDTH / 2) - (cub->x_elem * scale / 2);
	i = 0;
	while (i < (cub->x_elem * cub->y_elem))
	{
		square.x = (cub->map[i].x / WALL_SIZE * scale) + x_map_offset;
		square.y = (cub->map[i].y / WALL_SIZE * scale) + 10;
		square.color = cub->map[i].color;
		if (square.color != 0)
			draw_square(cub, square, scale - 1);
		i++;
	}
	square.x = ((cub->player.x_pos - (WALL_SIZE / 2)) * scale) / WALL_SIZE;
	square.y = ((cub->player.y_pos - (WALL_SIZE / 2)) * scale) / WALL_SIZE;
	square.x += x_map_offset;
	square.y += 10;
	square.color = 0xFFFFFF;
	draw_square(cub, square, scale / 2);
}
