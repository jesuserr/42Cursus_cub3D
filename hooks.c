/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:18:03 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/07 21:25:40 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, t_cub *cub)
{
	if (cub->key.mouse_x != 0 && x > -1 && x < WIDTH && y > -1 && y < HEIGHT)
	{
		if (cub->key.mouse_x > x)
		{
			cub->player.angle += ROT_ANG_MOUSE;
			if (cub->player.angle >= 360)
				cub->player.angle = 0;
			calc_player_vector(cub);
		}
		else if (cub->key.mouse_x < x)
		{
			cub->player.angle -= ROT_ANG_MOUSE;
			if (cub->player.angle < 0)
				cub->player.angle = 360 - ROT_ANG_MOUSE;
			calc_player_vector(cub);
		}
		cub->key.mouse_x = x;
	}
	if (!cub->key.mouse_x && x > -1 && x < WIDTH && y > -1 && y < HEIGHT)
		cub->key.mouse_x = x;
	return (0);
}

int	key_pressed(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		close_window(cub, EXIT_SUCCESS);
	else if (keycode == TAB_KEY)
		cub->key.map_on_screen = !cub->key.map_on_screen;
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
	else if (keycode == SHIFT_KEY)
	{
		cub->key.shift_pressed = 1;
		cub->player.speed *= 2;
	}
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
