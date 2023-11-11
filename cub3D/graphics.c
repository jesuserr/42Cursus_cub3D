/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/11 20:58:25 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_put_pixel(t_cub *cub, int x, int y, int color);
void	draw_vert_line(t_line line, t_cub *cub);

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
