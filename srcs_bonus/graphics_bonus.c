/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/13 22:23:22 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	mlx_put_pixel(t_cub *cub, int x, int y, int color);
void	draw_vert_line(t_line line, t_cub *cub);
void	draw_floor_and_ceiling(t_cub *cub);
void	draw_square(t_cub *cub, t_point square, int size);
void	on_screen_minimap(t_cub *cub);

void	mlx_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->img.addr + ((y * cub->img.len) + (x * (cub->img.bpp / 8)));
	*(unsigned int *)dst = color;
}

/* Optimized version of funct. draw_line for lines that are totally vertical */
/* as the ones used to draw solid walls. Since it doesn't need complex */
/* calculations the color can be written directly in the memory just */
/* incrementing the memory position by a constant number. */

void	draw_vert_line(t_line line, t_cub *cub)
{
	char	*dst;
	int		i;

	dst = cub->img.addr + (line.x0 * cub->img.bpp / 8);
	dst = dst + (line.y0 * cub->img.bpp / 8 * WIDTH);
	i = 0;
	while (i < (line.y1 - line.y0))
	{
		*(unsigned int *)dst = line.color;
		dst = dst + (cub->img.bpp / 8 * WIDTH);
		i++;
	}
}

void	draw_floor_and_ceiling(t_cub *cub)
{
	char	*dst;
	int		i;

	dst = cub->img.addr;
	i = 0;
	while (i < WIDTH * HEIGHT / 2)
	{
		*(unsigned int *)dst = cub->cmap->c_c;
		dst = dst + cub->img.bpp / 8;
		i++;
	}
	while (i < WIDTH * HEIGHT)
	{
		*(unsigned int *)dst = cub->cmap->c_f;
		dst = dst + cub->img.bpp / 8;
		i++;
	}
}

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
