/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:24:03 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/11 20:57:37 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray_casters(t_cub *cub, t_ray_cast *ver, t_ray_cast *hor, float a);
double	degrees_to_radians(int angle_degrees, float inc_angle);
void	check_first_corner_exception(t_cub *cub, t_ray_cast *v, t_ray_cast *h);
void	calc_player_vector(t_cub *cub);

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

void	calc_player_vector(t_cub *cub)
{
	cub->player.x_vector = cos(degrees_to_radians(cub->player.angle, 0));
	cub->player.y_vector = -sin(degrees_to_radians(cub->player.angle, 0));
	if (cub->player.x_vector > 0)
		cub->player.offset_x = DIST_TO_WALL;
	else
		cub->player.offset_x = -DIST_TO_WALL;
	if (cub->player.y_vector > 0)
		cub->player.offset_y = DIST_TO_WALL;
	else
		cub->player.offset_y = -DIST_TO_WALL;
}
