/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/24 20:58:36 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_action_1(int keycode, t_cub *cub)
{
	if (keycode == A_KEY)
		cub->player.x_pos -= INC_OFFSET;
	else if (keycode == D_KEY)
		cub->player.x_pos += INC_OFFSET;
	else if (keycode == S_KEY)
		cub->player.y_pos += INC_OFFSET;
	else if (keycode == W_KEY)
		cub->player.y_pos -= INC_OFFSET;
	else if (keycode == LEFT_KEY)
	{
		cub->player.angle += ROT_ANGLE_INC;
		if (cub->player.angle >= 360)
			cub->player.angle = 0;
	}
	else if (keycode == RIGHT_KEY)
	{
		cub->player.angle -= ROT_ANGLE_INC;
		if (cub->player.angle < 0)
			cub->player.angle = 360 - ROT_ANGLE_INC;
	}
	action_aux(cub);
}

/* Erases the image in memory; calculates and writes the new one */

void	action_aux(t_cub *cub)
{
	char	*str;

	ft_bzero(cub->img.addr, WIDTH * HEIGHT * cub->img.bpp / 8);
	projection(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img.img, 0, 0);
	str = ft_itoa(cub->player.x_pos);
	mlx_string_put(cub->mlx, cub->mlx_win, 500, 10, WHITE, str);
	free(str);
	str = ft_itoa(cub->player.y_pos);
	mlx_string_put(cub->mlx, cub->mlx_win, 500, 30, WHITE, str);
	free(str);
	str = ft_itoa(cub->player.angle);
	mlx_string_put(cub->mlx, cub->mlx_win, 500, 50, WHITE, str);
	free(str);
	str = ft_itoa(cub->map[cub->player.x_pos / WALL_SIZE + \
	(cub->player.y_pos / WALL_SIZE * cub->y_elem)].color);
	mlx_string_put(cub->mlx, cub->mlx_win, 500, 70, WHITE, str);
	free(str);
}
