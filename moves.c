/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/19 15:54:04 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Rotations and arrow keys movements */

void	key_action_1(int keycode, t_fdf *fdf)
{
	if (keycode == A_KEY)
		fdf->player.x_pos -= INC_OFFSET;
	else if (keycode == D_KEY)
		fdf->player.x_pos += INC_OFFSET;
	else if (keycode == S_KEY)
		fdf->player.y_pos += INC_OFFSET;
	else if (keycode == W_KEY)
		fdf->player.y_pos -= INC_OFFSET;
	else if (keycode == LEFT_KEY)
	{
		fdf->player.angle += ROT_ANGLE_INC;
		if (fdf->player.angle >= 360)
			fdf->player.angle = 0;
	}
	else if (keycode == RIGHT_KEY)
	{
		fdf->player.angle -= ROT_ANGLE_INC;
		if (fdf->player.angle < 0)
			fdf->player.angle = 360 - ROT_ANGLE_INC;
	}
	action_aux(fdf);
}

/* Erases the image in memory; calculates and writes the new one */
/* Keeps angles always between 0-359 degrees and prints info bar */
/* if screen is big enough */

void	action_aux(t_fdf *fdf)
{
	char	*str;

	ft_bzero(fdf->img.addr, WIDTH * HEIGHT * fdf->img.bpp / 8);
	projection(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);
	str = ft_itoa((int)fdf->player.x_pos);
	mlx_string_put(fdf->mlx, fdf->mlx_win, 500, 10, WHITE, str);
	free(str);
	str = ft_itoa((int)fdf->player.y_pos);
	mlx_string_put(fdf->mlx, fdf->mlx_win, 500, 30, WHITE, str);
	free(str);
	str = ft_itoa((int)fdf->player.angle);
	mlx_string_put(fdf->mlx, fdf->mlx_win, 500, 50, WHITE, str);
	free(str);
}
