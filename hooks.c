/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:26 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/19 00:10:12 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		close_window(fdf);
	else if (keycode == Q_KEY || keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == Z_KEY || keycode == X_KEY
		|| keycode == LEFT_KEY || keycode == RIGHT_KEY || keycode == DOWN_KEY
		|| keycode == UP_KEY)
		key_action_1(keycode, fdf);
	return (0);
}

/* Without mlx_destroy_window & free(fdf->mlx) there are no leaks either !?? */

int	close_window(t_fdf *fdf)
{
	free(fdf->raw_map);
	free(fdf->map);
	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	free(fdf->mlx);
	exit (EXIT_SUCCESS);
}
