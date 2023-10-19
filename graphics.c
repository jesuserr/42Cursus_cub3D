/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/19 12:44:00 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->img.addr + ((y * fdf->img.len) + (x * (fdf->img.bpp / 8)));
	*(unsigned int *)dst = color;
}

/* Uses Bresenham's line algorithm (extended to work in any octant) */
/* Pixels outside screen boundaries (including info bar) are not printed */

void	draw_line(t_line line, t_fdf *fdf)
{
	t_line_aux	line_aux;

	line_direction (&line, &line_aux);
	line_aux.dx = abs(line.x1 - line.x0);
	line_aux.dy = -abs(line.y1 - line.y0);
	line_aux.error = line_aux.dx + line_aux.dy;
	while (!(line.x0 == line.x1 && line.y0 == line.y1))
	{
		if (line.x0 >= 0 && line.y0 >= 0 && line.x0 < WIDTH && line.y0 < HEIGHT)
			mlx_put_pixel(fdf, line.x0, line.y0, line.color);
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

void	draw_square(t_fdf *fdf, t_point square, int size)
{
	int		i;
	t_line	line;

	i = 0;
	line.x0 = square.x;
	line.y0 = square.y;
	line.x1 = square.x + size;
	line.y1 = line.y0;
	line.color = square.color;
	while (i < size)
	{
		draw_line(line, fdf);
		line.y0++;
		line.y1++;
		i++;
	}
}
