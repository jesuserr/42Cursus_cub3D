/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:33:16 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/20 19:41:23 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_pressed(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		close_window(cub, EXIT_SUCCESS);
	else if (keycode == D_KEY)
		cub->key.d_pressed = 1;
	else if (keycode == S_KEY)
		cub->key.s_pressed = 1;
	else if (keycode == A_KEY)
		cub->key.a_pressed = 1;
	else if (keycode == W_KEY)
		cub->key.w_pressed = 1;
	else if (keycode == LEFT_KEY)
		cub->key.left_pressed = 1;
	else if (keycode == RIGHT_KEY)
		cub->key.right_pressed = 1;
	else if (keycode == O_KEY)
		reset_player(cub);
	else if (keycode == SHIFT_KEY)
	{
		cub->key.shift_pressed = 1;
		cub->player.speed = INC_OFFSET * 2;
	}
	else if (keycode == I_KEY)
		cub->key.info_on_screen = !cub->key.info_on_screen;
	return (0);
}

int	key_released(int keycode, t_cub *cub)
{
	if (keycode == D_KEY)
		cub->key.d_pressed = 0;
	else if (keycode == S_KEY)
		cub->key.s_pressed = 0;
	else if (keycode == A_KEY)
		cub->key.a_pressed = 0;
	else if (keycode == W_KEY)
		cub->key.w_pressed = 0;
	else if (keycode == LEFT_KEY)
		cub->key.left_pressed = 0;
	else if (keycode == RIGHT_KEY)
		cub->key.right_pressed = 0;
	else if (keycode == SHIFT_KEY)
	{
		cub->key.shift_pressed = 0;
		cub->player.speed = INC_OFFSET;
	}
	return (0);
}

void	reset_player(t_cub *cub)
{
	cub->player.x_pos = cub->player.orig_x_pos;
	cub->player.y_pos = cub->player.orig_y_pos;
	cub->player.angle = cub->player.orig_angle;
	calc_player_vector(cub);
}
