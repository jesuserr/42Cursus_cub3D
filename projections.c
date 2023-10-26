/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:43:38 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/26 10:59:41 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap_and_player(t_cub *cub);
void	ray_casting(t_cub *cub);
void	check_horizontal_lines(t_ray_cast *horz, t_cub *cub);
void	check_vertical_lines(t_ray_cast *horz, t_cub *cub);

void	projection(t_cub *cub)
{
	draw_minimap_and_player(cub);
	ray_casting(cub);
}

void	draw_minimap_and_player(t_cub *cub)
{
	int		i;
	t_point	square;

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
	//draw_pointer(cub);
	//mlx_put_pixel(cub, cub->player.x_pos, cub->player.y_pos, DEF_COLOR);
}

void	ray_casting(t_cub *cub)
{
	t_ray_cast	horz;
	t_ray_cast	vert;
	t_line		line;
	
	check_horizontal_lines(&horz, cub);
	printf("HIT_H: %f %f %f\n", horz.ray_x, horz.ray_y, horz.ray_length);
	check_vertical_lines(&vert, cub);
	printf("HIT_V: %f %f %f\n", vert.ray_x, vert.ray_y, vert.ray_length);
	line.x0 = cub->player.x_pos;
	line.y0 = cub->player.y_pos;
	if (vert.ray_length < horz.ray_length)
	{
		line.x1 = vert.ray_x;
		line.y1 = vert.ray_y;
		line.color = 0xFF00FF;
	}
	else
	{
		line.x1 = horz.ray_x;
		line.y1 = horz.ray_y;
		line.color = 0xFFFF00;
	}
	draw_line(line, cub);
}

void	check_horizontal_lines(t_ray_cast *horz, t_cub *cub)
{
	horz->ray_angle = cub->player.angle * PI / 180;
	horz->ray_number = 0;
	horz->ray_length = WIDTH * HEIGHT;
	while (horz->ray_number < 1)
	{
		horz->depth_of_field = 0;
		horz->arc_tan = 1 / tan(horz->ray_angle);
		if (horz->ray_angle > 0 && horz->ray_angle < PI)
		{
			horz->ray_y = ((cub->player.y_pos / WALL_SIZE) * WALL_SIZE) - 1;
			horz->ray_x = (cub->player.y_pos - horz->ray_y) * horz->arc_tan + cub->player.x_pos;
			horz->y_offset = -WALL_SIZE;
			horz->x_offset = -horz->y_offset * horz->arc_tan;
		}
		else if (horz->ray_angle > PI && horz->ray_angle < (2 * PI))
		{
			horz->ray_y = ((cub->player.y_pos / WALL_SIZE) * WALL_SIZE) + WALL_SIZE;
			horz->ray_x = (cub->player.y_pos - horz->ray_y) * horz->arc_tan + cub->player.x_pos;
			horz->y_offset = WALL_SIZE;
			horz->x_offset = -horz->y_offset * horz->arc_tan;
		}
		else
		{
			horz->ray_x = cub->player.x_pos;
			horz->ray_y = cub->player.y_pos;
			horz->depth_of_field = DEPTH_OF_FIELD;
		}
		while (horz->depth_of_field < DEPTH_OF_FIELD)
		{
			horz->map_x = horz->ray_x / WALL_SIZE;
			horz->map_y = horz->ray_y / WALL_SIZE;
			horz->map_pos = horz->map_y * cub->x_elem + horz->map_x;
			if (horz->map_pos > 0 && horz->map_pos < (cub->x_elem * cub->y_elem) && cub->map[horz->map_pos].color != 0)
			{
				horz->ray_length = cos(horz->ray_angle)*(horz->ray_x - cub->player.x_pos) - sin(horz->ray_angle)*(horz->ray_y - cub->player.y_pos);
				break ;
			}
			else
			{
				horz->ray_x += horz->x_offset;
				horz->ray_y += horz->y_offset;
				horz->depth_of_field++;
			}
		}
		horz->ray_number++;
	}
}

void	check_vertical_lines(t_ray_cast *vert, t_cub *cub)
{
	vert->ray_angle = cub->player.angle * PI / 180;
	vert->ray_number = 0;
	vert->ray_length = WIDTH * HEIGHT;
	while (vert->ray_number < 1)
	{
		vert->depth_of_field = 0;
		vert->tan = tan(vert->ray_angle);
		if (vert->ray_angle == PI / 2 || vert->ray_angle == PI * 3 / 2)
		{
			vert->ray_x = cub->player.x_pos;
			vert->ray_y = cub->player.y_pos;
			vert->depth_of_field = DEPTH_OF_FIELD;
		}
		else if (vert->ray_angle > PI / 2 && vert->ray_angle < PI * 3 / 2)
		{
			vert->ray_x = ((cub->player.x_pos / WALL_SIZE) * WALL_SIZE) - 1;
			vert->ray_y = (cub->player.x_pos - vert->ray_x) * vert->tan + cub->player.y_pos;
			vert->x_offset = -WALL_SIZE;
			vert->y_offset = -vert->x_offset * vert->tan;
		}
		else
		{
			vert->ray_x = ((cub->player.x_pos / WALL_SIZE) * WALL_SIZE) + WALL_SIZE;
			vert->ray_y = (cub->player.x_pos - vert->ray_x) * vert->tan + cub->player.y_pos;
			vert->x_offset = WALL_SIZE;
			vert->y_offset = -vert->x_offset * vert->tan;
		}
		while (vert->depth_of_field < DEPTH_OF_FIELD)
		{
			vert->map_x = vert->ray_x / WALL_SIZE;
			vert->map_y = vert->ray_y / WALL_SIZE;
			vert->map_pos = vert->map_y * cub->x_elem + vert->map_x;
			if (vert->map_pos > 0 && vert->map_pos < (cub->x_elem * cub->y_elem) && cub->map[vert->map_pos].color != 0)
			{
				vert->ray_length = cos(vert->ray_angle)*(vert->ray_x - cub->player.x_pos) - sin(vert->ray_angle)*(vert->ray_y - cub->player.y_pos);
				break ;
			}
			else
			{
				vert->ray_x += vert->x_offset;
				vert->ray_y += vert->y_offset;
				vert->depth_of_field++;
			}
		}
		vert->ray_number++;
	}
}
