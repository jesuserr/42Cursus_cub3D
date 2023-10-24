/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/24 10:43:39 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->img.addr + ((y * cub->img.len) + (x * (cub->img.bpp / 8)));
	*(unsigned int *)dst = color;
}

/* Uses Bresenham's line algorithm (extended to work in any octant) */
/* Pixels outside screen boundaries (including info bar) are not printed */

void	draw_line(t_line line, t_cub *cub)
{
	t_line_aux	line_aux;

	line_direction (&line, &line_aux);
	line_aux.dx = abs(line.x1 - line.x0);
	line_aux.dy = -abs(line.y1 - line.y0);
	line_aux.error = line_aux.dx + line_aux.dy;
	while (!(line.x0 == line.x1 && line.y0 == line.y1))
	{
		if (line.x0 >= 0 && line.y0 >= 0 && line.x0 < WIDTH && line.y0 < HEIGHT)
			mlx_put_pixel(cub, line.x0, line.y0, line.color);
		if ((2 * line_aux.error) >= line_aux.dy)
		{
			line_aux.error = line_aux.error + line_aux.dy;
			line.x0 = line.x0 + line_aux.sx;
		}
		else
		{
			line_aux.error = line_aux.error + line_aux.dx;
			line.y0 = line.y0 + line_aux.sy;
		}
	}
}

void	line_direction(t_line *line, t_line_aux *line_aux)
{
	if (line->x0 < line->x1)
		line_aux->sx = 1;
	else
		line_aux->sx = -1;
	if (line->y0 < line->y1)
		line_aux->sy = 1;
	else
		line_aux->sy = -1;
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

void	draw_pointer(t_cub *cub)
{
	t_line	line;

	line.x0 = cub->player.x_pos;
	line.y0 = cub->player.y_pos;
	line.x1 = line.x0 + WALL_SIZE / 1.5 * cos(cub->player.angle * PI / 180);
	line.y1 = line.y0 - WALL_SIZE / 1.5 * sin(cub->player.angle * PI / 180);
	line.color = 0xF0F0F0;
	draw_line(line, cub);
}
