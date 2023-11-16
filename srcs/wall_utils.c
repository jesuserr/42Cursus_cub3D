/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:21:31 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/16 23:06:49 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);
int		choose_texture(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz);
void	calc_line_height(t_line *line, t_cub *cub, t_txt *txt);
float	wall_height_and_color(t_line *line, t_cub *cub);
void	draw_texture(t_line line, t_cub *cub, t_txt *txt, float offset);

void	draw_wall(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float ray)
{
	t_line	line;
	int		index;

	line.x0 = ray;
	line.x1 = ray;
	index = choose_texture(cub, vert, horz);
	calc_line_height(&line, cub, cub->textures[index]);
	if (index == 0 || index == 2)
		draw_texture(line, cub, cub->textures[index], vert->ray_y);
	else if (index == 1 || index == 3)
		draw_texture(line, cub, cub->textures[index], horz->ray_x);
	else
		draw_vert_line(line, cub);
}

int	choose_texture(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz)
{
	float	v_vs_h;

	v_vs_h = vert->ray_length - horz->ray_length;
	if (vert->ray_angle >= 0 && vert->ray_angle < (PI / 2) && v_vs_h <= 0 && \
	cub->textures[0])
		return (0);
	else if (vert->ray_angle > 0 && vert->ray_angle < PI && v_vs_h >= 0 && \
	cub->textures[1])
		return (1);
	else if (vert->ray_angle > (PI / 2) && vert->ray_angle < (3 * PI / 2) && \
	v_vs_h <= 0 && cub->textures[2])
		return (2);
	else if (vert->ray_angle > (PI) && vert->ray_angle < (2 * PI) && \
	v_vs_h >= 0 && cub->textures[3])
		return (3);
	else if (vert->ray_angle > (3 * PI / 2) && vert->ray_angle < (2 * PI) && \
	v_vs_h <= 0 && cub->textures[0])
		return (0);
	return (4);
}

void	calc_line_height(t_line *line, t_cub *cub, t_txt *txt)
{
	float	wall_height;
	float	eye_angle;

	wall_height = wall_height_and_color(line, cub);
	eye_angle = degrees_to_radians(cub->player.angle, 0) - cub->horz.ray_angle;
	wall_height = HEIGHT * WALL_SIZE / (wall_height * cos(eye_angle));
	wall_height *= cub->aspect_ratio;
	if (txt)
	{
		txt->offset = 0;
		txt->scale = (float)txt->h / wall_height;
	}
	if (wall_height > HEIGHT)
	{
		if (txt)
			txt->offset = ((wall_height) - HEIGHT) / 2.0;
		wall_height = HEIGHT;
	}
	line->y0 = (HEIGHT / 2) - (wall_height / 2);
	line->y1 = (HEIGHT / 2) + (wall_height / 2);
}

float	wall_height_and_color(t_line *line, t_cub *cub)
{
	float	wall_height;

	if (cub->vert.ray_length < cub->horz.ray_length)
	{
		wall_height = cub->vert.ray_length;
		line->color = 0x0000FC;
		if (cub->vert.ray_angle > (PI / 2) && cub->vert.ray_angle < (1.5 * PI))
			line->color = 0x0368AC;
	}
	else
	{
		wall_height = cub->horz.ray_length;
		line->color = 0x0000A4;
		if (cub->horz.ray_angle > PI && cub->horz.ray_angle < (2 * PI))
			line->color = 0x0098FD;
	}
	return (wall_height);
}

void	draw_texture(t_line line, t_cub *cub, t_txt *txt, float offset)
{
	char	*canvas;
	char	*texture;
	float	step;
	int		i;

	canvas = cub->img.addr + (line.x0 * cub->img.bpp / 8);
	canvas = canvas + (line.y0 * cub->img.bpp / 8 * WIDTH);
	texture = txt->img.addr + (txt->img.bpp / 8 * ((int)(offset) % WALL_SIZE) \
	* txt->w / WALL_SIZE);
	if ((float)txt->w / (float)WALL_SIZE < 1)
		texture = txt->img.addr + (txt->img.bpp / 8 * (((int)(offset) % \
		WALL_SIZE) / (WALL_SIZE / txt->w)));
	step = txt->scale * txt->offset;
	i = 0;
	while (i++ < (line.y1 - line.y0))
	{
		*(unsigned int *)canvas = *(unsigned int *)texture;
		canvas = canvas + (cub->img.bpp / 8 * WIDTH);
		step = step + txt->scale;
		while (step >= 1)
		{
			texture = texture + (txt->img.bpp / 8 * txt->w);
			step--;
		}
	}
}
