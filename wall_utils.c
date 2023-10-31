/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:13:31 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/31 20:17:55 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceiling(t_cub *cub);
void	rise_walls(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);

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

void	rise_walls(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x)
{
	float	wall_height;
	float	eye_angle;
	t_line	line;

	line.x0 = x;
	line.x1 = x;
	line.color = 0x880808;
	if (vert->ray_length < horz->ray_length)
		wall_height = vert->ray_length;
	else
	{
		wall_height = horz->ray_length;
		line.color = 0xEE4B2B;
	}
	eye_angle = degrees_to_radians(cub->player.angle, 0) - horz->ray_angle;
	wall_height = HEIGHT * WALL_SIZE / (wall_height * cos(eye_angle));
	wall_height *= VERT_SCALE;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	line.y0 = (HEIGHT / 2) - (wall_height / 2);
	line.y1 = (HEIGHT / 2) + (wall_height / 2);
	draw_vert_line(line, cub);
}
