/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/19 01:42:21 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_square(t_fdf *fdf, t_point square, int size);

void	projection(t_fdf *fdf)
{
	int		i;
	t_point	square;

	printf("%6.2f %6.2f\n", fdf->player.x_pos, fdf->player.y_pos);
	i = 0;
	while (i < (fdf->x_elem * fdf->y_elem))
	{
		square.x = fdf->map[i].x;
		square.y = fdf->map[i].y;
		square.color = fdf->map[i].color;
		draw_square(fdf, square, SQUARE_SIZE);
		i++;
	}
	square.x = fdf->player.x_pos - SQUARE_SIZE / 8;
	square.y = fdf->player.y_pos - SQUARE_SIZE / 8;
	square.color = 0xFFFFFF;
	draw_square(fdf, square, SQUARE_SIZE / 4);
	mlx_put_pixel(fdf, fdf->player.x_pos, fdf->player.y_pos, DEF_COLOR);
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
