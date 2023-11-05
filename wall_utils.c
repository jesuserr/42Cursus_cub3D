/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:13:31 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/05 12:03:23 by jesuserr         ###   ########.fr       */
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
	wall_height *= VERT_SCALE;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	line.y0 = (HEIGHT / 2) - (wall_height / 2);
	line.y1 = (HEIGHT / 2) + (wall_height / 2);
	draw_vert_line(line, cub);
}

void	draw_texture(t_cub *cub, t_txt *txt, int x, int y)
{
	int		i;
	int		temp_x;
	int		temp_y;
	int		color;
	char	*temp;

	temp = txt->img.addr;
	i = 0;
	temp_x = x;
	temp_y = y;
	while (i < txt->h * txt->w)
	{
		color = *(unsigned int *)temp;
		mlx_put_pixel(cub, temp_x, temp_y, color);
		temp += txt->img.bpp / 8;
		if (i % txt->w == 0)
		{
			temp_x = x;
			temp_y++;
		}
		i++;
		temp_x++;
	}
}

void	hexdump(const void *data, size_t length)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *)data;
	for (size_t i = 0; i < length; i++)
	{
		printf("%02X ", ptr[i]);
		if ((i + 1) % 16 == 0 || i == length - 1)
		{
			printf(" ");
			for (size_t j = i - (i % 16); j <= i; j++)
			{
				if (j == i / 2)
					printf(" ");
				if (j >= length)
					printf("   ");
				else if (ptr[j] >= 32 && ptr[j] <= 126)
					printf("%c ", ptr[j]);
				else
					printf(". ");
			}
			printf("\n");
		}
	}
}
