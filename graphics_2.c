/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:03:49 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/24 20:04:44 by jesuserr         ###   ########.fr       */
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
