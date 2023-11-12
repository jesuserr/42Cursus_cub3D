/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/12 21:51:13 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	mlx_put_pixel(t_cub *cub, int x, int y, int color);
void	draw_line(t_line line, t_cub *cub);
void	line_direction(t_line *line, t_line_aux *line_aux);
void	draw_vert_line(t_line line, t_cub *cub);
void	draw_floor_and_ceiling(t_cub *cub);

void	mlx_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->img.addr + ((y * cub->img.len) + (x * (cub->img.bpp / 8)));
	*(unsigned int *)dst = color;
}

/* Uses Bresenham's line algorithm (extended to work in any octant) */
/* Pixels outside screen boundaries are not printed */

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
