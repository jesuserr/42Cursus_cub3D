/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:24:03 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/30 10:44:01 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray_casters(t_cub *cub, t_ray_cast *ver, t_ray_cast *hor, float a);
double	degrees_to_radians(int angle_degrees, float inc_angle);
void	draw_shorter_ray(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz);
void	check_first_corner_exception(t_cub *cub, t_ray_cast *v, t_ray_cast *h);
void	rise_walls(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);

void	init_ray_casters(t_cub *cub, t_ray_cast *ver, t_ray_cast *hor, float a)
{
	hor->ray_angle = degrees_to_radians(cub->player.angle, a);
	hor->depth_of_field = 0;
	hor->ray_length = WIDTH * HEIGHT;
	ver->ray_angle = degrees_to_radians(cub->player.angle, a);
	ver->depth_of_field = 0;
	ver->ray_length = WIDTH * HEIGHT;
}

double	degrees_to_radians(int angle_degrees, float inc_angle)
{
	double	angle_radians;

	angle_radians = ((float)angle_degrees + inc_angle) * PI / 180;
	while (angle_radians >= 2 * PI)
		angle_radians -= 2 * PI;
	while (angle_radians < 0)
		angle_radians += 2 * PI;
	return (angle_radians);
}

void	draw_shorter_ray(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz)
{
	t_line	line;

	line.x0 = cub->player.x_pos;
	line.y0 = cub->player.y_pos;
	if (vert->ray_length < horz->ray_length)
	{
		line.x1 = vert->ray_x;
		line.y1 = vert->ray_y;
		line.color = 0xFF00FF;
	}
	else
	{
		line.x1 = horz->ray_x;
		line.y1 = horz->ray_y;
		line.color = 0xFFFF00;
	}
	draw_line(line, cub);
}

void	check_first_corner_exception(t_cub *cub, t_ray_cast *v, t_ray_cast *h)
{
	if (h->ray_length == WIDTH * HEIGHT && v->ray_length == WIDTH * HEIGHT)
	{
		h->ray_length = (cub->player.x_pos - WALL_SIZE) / (cos(PI / 4));
		v->ray_length = h->ray_length;
		h->ray_x = WALL_SIZE;
		h->ray_y = WALL_SIZE;
		v->ray_x = WALL_SIZE;
		v->ray_y = WALL_SIZE;
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
	draw_line(line, cub);
}
