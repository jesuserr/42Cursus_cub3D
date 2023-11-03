/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:53:34 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/03 12:25:18 by jesuserr         ###   ########.fr       */
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

int	close_window(t_cub *cub)
{
	close_cmaps(cub);
	if (cub->raw_map)
		free(cub->raw_map);
	if (cub->map)
		free(cub->map);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->mlx_win)
	{
		mlx_clear_window(cub->mlx, cub->mlx_win);
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	}
	if (cub->mlx)
	{
		mlx_destroy_image(cub->mlx, ((mlx_ptr_t *)cub->mlx)->img_list);
		free(((mlx_ptr_t *)cub->mlx)->img_list);
		free(cub->mlx);
	}
	exit (EXIT_SUCCESS);
}

void	close_cmaps(t_cub *cub)
{
	if (cub->cmap && cub->cmap->t_so)
		free(cub->cmap->t_so);
	if (cub->cmap && cub->cmap->t_we)
		free(cub->cmap->t_we);
	if (cub->cmap && cub->cmap->t_no)
		free(cub->cmap->t_no);
	if (cub->cmap && cub->cmap->t_ea)
		free(cub->cmap->t_ea);
	if (cub->cmap)
		free(cub->cmap);
}
