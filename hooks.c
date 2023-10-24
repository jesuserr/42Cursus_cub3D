/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/24 10:43:39 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_pressed(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		close_window(cub);
	else if (keycode == D_KEY || keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == Z_KEY || keycode == X_KEY
		|| keycode == LEFT_KEY || keycode == RIGHT_KEY || keycode == DOWN_KEY
		|| keycode == UP_KEY)
		key_action_1(keycode, cub);
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
