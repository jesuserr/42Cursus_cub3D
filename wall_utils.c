/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:13:31 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/07 23:03:45 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceiling(t_cub *cub);
void	rise_walls(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);
void	draw_texture(t_line line, t_cub *cub, t_txt *txt, float wall_height);

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
	line.color = 0x0000FC;
	if (vert->ray_length < horz->ray_length)
		wall_height = vert->ray_length;
	else
	{
		wall_height = horz->ray_length;
		line.color = 0x0000A4;
	}
	eye_angle = degrees_to_radians(cub->player.angle, 0) - horz->ray_angle;
	wall_height = HEIGHT * WALL_SIZE / (wall_height * cos(eye_angle));
	if (cub->txt_ea && cub->txt_no && cub->txt_we && cub->txt_so)
		draw_texture(line, cub, cub->txt_no, wall_height);
	else
		draw_vert_line(line, cub, wall_height);
}

void	draw_texture(t_line line, t_cub *cub, t_txt *txt, float wall_height)
{
	char		*dst;
	char		*texture;
	int			i;
	float		scale;
	float		cont;
	float		txt_offset = 0;

	wall_height *= VERT_SCALE;
	scale = (float)txt->h / wall_height;
	if (wall_height > HEIGHT)
	{
		txt_offset = ((wall_height) - HEIGHT) / 2.0;
		wall_height = HEIGHT;
	}
	line.y0 = (HEIGHT / 2) - (wall_height / 2);
	line.y1 = (HEIGHT / 2) + (wall_height / 2);
	cont = scale * txt_offset;
	texture = txt->img.addr;
	dst = cub->img.addr + (line.x0 * cub->img.bpp / 8);
	dst = dst + (line.y0 * cub->img.bpp / 8 * WIDTH);
	i = 0;
	while (i < (line.y1 - line.y0))
	{
		*(unsigned int *)dst = *(unsigned int *)texture;
		dst = dst + (cub->img.bpp / 8 * WIDTH);
		i++;
		cont = cont + scale;
		while (cont >= 1)
		{
			texture = texture + (txt->img.bpp / 8 * txt->w);
			cont--;
		}
	}
}
