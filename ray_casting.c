/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/03 09:40:49 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ray_casting(t_cub *cub);
void	draw_minimap_and_player(t_cub *cub);
void	check_horizontal_lines(t_ray_cast *horz, t_cub *cub);
void	check_vertical_lines(t_ray_cast *horz, t_cub *cub);
void	check_hit_to_wall(t_cub *cub, t_ray_cast *cast);

int	ray_casting(t_cub *cub)
{
	t_ray_cast	horz;
	t_ray_cast	vert;
	float		ray_angle;
	float		casted_rays;

	casted_rays = 0;
	ray_angle = FOV / 2.0;
	draw_floor_and_ceiling(cub);
	//draw_minimap_and_player(cub);
	while (casted_rays < WIDTH)
	{
		init_ray_casters(cub, &vert, &horz, ray_angle);
		check_horizontal_lines(&horz, cub);
		check_vertical_lines(&vert, cub);
		check_first_corner_exception(cub, &vert, &horz);
		//draw_shorter_ray(cub, &vert, &horz);
		rise_walls(cub, &vert, &horz, casted_rays);
		ray_angle = ray_angle - ((float)FOV / (float)WIDTH);
		casted_rays++;
	}
	if (cub->key.map_on_screen == 1)
		on_screen_minimap(cub);
	//draw_pointer(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img.img, 0, 0);
	key_actions(cub);
	mouse_actions(cub);
	return (0);
}

void	draw_minimap_and_player(t_cub *cub)
{
	int		i;
	t_point	square;

	ft_bzero(cub->img.addr, WIDTH * HEIGHT * cub->img.bpp / 8);
	i = 0;
	while (i < (cub->x_elem * cub->y_elem))
	{
		square.x = cub->map[i].x;
		square.y = cub->map[i].y;
		square.color = cub->map[i].color;
		if (square.color != 0)
			draw_square(cub, square, WALL_SIZE - 1);
		i++;
	}
	square.x = cub->player.x_pos - WALL_SIZE / 8;
	square.y = cub->player.y_pos - WALL_SIZE / 8;
	square.color = 0xFFFFFF;
	draw_square(cub, square, WALL_SIZE / 4);
}

void	check_horizontal_lines(t_ray_cast *horz, t_cub *cub)
{
	horz->depth_of_field_max = cub->y_elem;
	horz->tan = tan((PI / 2) - horz->ray_angle);
	if (horz->ray_angle > 0 && horz->ray_angle < PI)
	{
		horz->ray_y = ((cub->player.y_pos / WALL_SIZE) * WALL_SIZE) - 0.0002;
		horz->ray_x = (cub->player.y_pos - horz->ray_y) * \
		horz->tan + cub->player.x_pos;
		horz->y_offset = -WALL_SIZE;
		horz->x_offset = -horz->y_offset * horz->tan;
	}
	else if (horz->ray_angle > PI && horz->ray_angle < (2 * PI))
	{
		horz->ray_y = ((cub->player.y_pos / WALL_SIZE) * WALL_SIZE) + WALL_SIZE;
		horz->ray_x = (cub->player.y_pos - horz->ray_y) * \
		horz->tan + cub->player.x_pos;
		horz->y_offset = WALL_SIZE;
		horz->x_offset = -horz->y_offset * horz->tan;
	}
	else
	{
		horz->ray_x = cub->player.x_pos;
		horz->ray_y = cub->player.y_pos;
		horz->depth_of_field = horz->depth_of_field_max;
	}
	check_hit_to_wall(cub, horz);
}

void	check_vertical_lines(t_ray_cast *vert, t_cub *cub)
{
	vert->depth_of_field_max = cub->x_elem;
	vert->tan = tan(vert->ray_angle);
	if (vert->ray_angle == PI / 2 || vert->ray_angle == PI * 3 / 2)
	{
		vert->ray_x = cub->player.x_pos;
		vert->ray_y = cub->player.y_pos;
		vert->depth_of_field = vert->depth_of_field_max;
	}
	else if (vert->ray_angle > PI / 2 && vert->ray_angle < PI * 3 / 2)
	{
		vert->ray_x = ((cub->player.x_pos / WALL_SIZE) * WALL_SIZE) - 0.0002;
		vert->ray_y = (cub->player.x_pos - vert->ray_x) * \
		vert->tan + cub->player.y_pos;
		vert->x_offset = -WALL_SIZE;
		vert->y_offset = -vert->x_offset * vert->tan;
	}
	else
	{
		vert->ray_x = ((cub->player.x_pos / WALL_SIZE) * WALL_SIZE) + WALL_SIZE;
		vert->ray_y = (cub->player.x_pos - vert->ray_x) * \
		vert->tan + cub->player.y_pos;
		vert->x_offset = WALL_SIZE;
		vert->y_offset = -vert->x_offset * vert->tan;
	}
	check_hit_to_wall(cub, vert);
}

void	check_hit_to_wall(t_cub *cub, t_ray_cast *cast)
{
	while (cast->depth_of_field < cast->depth_of_field_max)
	{
		cast->map_x = cast->ray_x / WALL_SIZE;
		cast->map_y = cast->ray_y / WALL_SIZE;
		cast->map_pos = cast->map_y * cub->x_elem + cast->map_x;
		if (cast->map_pos > 0 && cast->map_pos < (cub->x_elem * cub->y_elem) \
		&& cub->map[cast->map_pos].color != 0)
		{
			cast->ray_length = cos(cast->ray_angle) * \
			(cast->ray_x - cub->player.x_pos) - sin(cast->ray_angle) * \
			(cast->ray_y - cub->player.y_pos);
			break ;
		}
		else
		{
			cast->ray_x += cast->x_offset;
			cast->ray_y += cast->y_offset;
			cast->depth_of_field++;
		}
	}
}
