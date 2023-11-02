/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/02 10:27:07 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_pressed(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		close_window(cub);
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
/* Without mlx_destroy_window & free(cub->mlx) there are no leaks either !?? */

int	close_window(t_cub *cub)
{
	if (cub->cmap->t_so)
		free(cub->cmap->t_so);
	if (cub->cmap->t_we)
		free(cub->cmap->t_we);
	if (cub->cmap->t_no)
		free(cub->cmap->t_no);
	if (cub->cmap->t_ea)
		free(cub->cmap->t_ea);
	if (cub->cmap)
		free(cub->cmap);
	free(cub->raw_map);
	free(cub->map);
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	free(cub->mlx);
	exit (EXIT_SUCCESS);
}
