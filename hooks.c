/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/01 13:10:51 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_pressed(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		close_window(cub);
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
	return (0);
}
/* Without mlx_destroy_window & free(cub->mlx) there are no leaks either !?? */

int	close_window(t_cub *cub)
{
	free(cub->raw_map);
	free(cub->map);
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	free(cub->mlx);
	exit (EXIT_SUCCESS);
}
