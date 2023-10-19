/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/19 12:44:03 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
