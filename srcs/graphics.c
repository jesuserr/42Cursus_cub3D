/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/20 20:41:13 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_put_pixel(t_cub *cub, int x, int y, int color);
void	draw_vert_line(t_line line, t_cub *cub);
void	draw_floor_and_ceiling(t_cub *cub);
void	keys_info_on_screen(t_cub *cub);

void	mlx_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->img.addr + ((y * cub->img.len) + (x * (cub->img.bpp / 8)));
	*(unsigned int *)dst = color;
}

void	draw_vert_line(t_line line, t_cub *cub)
{
	char	*dst;
	int		i;

	dst = cub->img.addr + (line.x0 * cub->img.bpp / 8);
	dst = dst + (line.y0 * cub->img.bpp / 8 * WIDTH);
	i = 0;
	while (i < (line.y1 - line.y0))
	{
		*(unsigned int *)dst = line.color;
		dst = dst + (cub->img.bpp / 8 * WIDTH);
		i++;
	}
}

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

void	keys_info_on_screen(t_cub *cub)
{
	mlx_string_put(cub->mlx, cub->mlx_win, 10, 10, DEF_COLOR, "Look:");
	mlx_string_put(cub->mlx, cub->mlx_win, 75, 10, WHITE, \
	"Left/Right Arrow Keys");
	mlx_string_put(cub->mlx, cub->mlx_win, 10, 30, DEF_COLOR, "Move:");
	mlx_string_put(cub->mlx, cub->mlx_win, 75, 30, WHITE, "W/A/S/D Keys");
	mlx_string_put(cub->mlx, cub->mlx_win, 10, 50, DEF_COLOR, "Run:");
	mlx_string_put(cub->mlx, cub->mlx_win, 75, 50, WHITE, "L-Shift Key");
	mlx_string_put(cub->mlx, cub->mlx_win, 10, 70, DEF_COLOR, "Exit:");
	mlx_string_put(cub->mlx, cub->mlx_win, 75, 70, WHITE, "ESC Key");
}
