/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:13:31 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/08 16:12:08 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceiling(t_cub *cub);
void	rise_walls(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);
void	draw_texture(t_line line, t_cub *cub, t_txt *txt);
float	line_height(t_line *line, t_cub *cub, t_txt *txt, float ray);

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

void	rise_walls(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float ray)
{
	float	wall_height;
	t_line	line;

	(void)vert;
	(void)horz;
	line.color = 0x0000FC;
	wall_height = line_height(&line, cub, cub->txt_no, ray);
	if (cub->txt_ea && cub->txt_no && cub->txt_we && cub->txt_so)
		draw_texture(line, cub, cub->txt_no);
	else
		draw_vert_line(line, cub);
}

void	draw_texture(t_line line, t_cub *cub, t_txt *txt)
{
	char	*canvas;
	char	*texture;
	float	step;
	int		i;

	canvas = cub->img.addr + (line.x0 * cub->img.bpp / 8);
	canvas = canvas + (line.y0 * cub->img.bpp / 8 * WIDTH);
	texture = txt->img.addr + (txt->img.bpp / 8 * ((int)(cub->vert.ray_y) \
	% WALL_SIZE));
	step = txt->scale * txt->offset;
	i = 0;
	while (i < (line.y1 - line.y0))
	{
		*(unsigned int *)canvas = *(unsigned int *)texture;
		canvas = canvas + (cub->img.bpp / 8 * WIDTH);
		step = step + txt->scale;
		while (step >= 1)
		{
			texture = texture + (txt->img.bpp / 8 * txt->w);
			step--;
		}
		i++;
	}
}

float	line_height(t_line *line, t_cub *cub, t_txt *txt, float ray)
{
	float	wall_height;
	float	eye_angle;

	line->x0 = ray;
	line->x1 = ray;
	txt->offset = 0;
	if (cub->vert.ray_length < cub->horz.ray_length)
		wall_height = cub->vert.ray_length;
	else
	{
		wall_height = cub->horz.ray_length;
		line->color = 0x0000A4;
	}
	eye_angle = degrees_to_radians(cub->player.angle, 0) - cub->horz.ray_angle;
	wall_height = HEIGHT * WALL_SIZE / (wall_height * cos(eye_angle));
	wall_height *= VERT_SCALE;
	txt->scale = (float)txt->h / wall_height;
	if (wall_height > HEIGHT)
	{
		txt->offset = ((wall_height) - HEIGHT) / 2.0;
		wall_height = HEIGHT;
	}
	line->y0 = (HEIGHT / 2) - (wall_height / 2);
	line->y1 = (HEIGHT / 2) + (wall_height / 2);
	return (wall_height);
}
