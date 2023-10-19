/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/19 00:10:20 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Rotations and arrow keys movements */

void	key_action_1(int keycode, t_fdf *fdf)
{
	if (keycode == LEFT_KEY)
		fdf->offset_x += INC_OFFSET;
	else if (keycode == RIGHT_KEY)
		fdf->offset_x -= INC_OFFSET;
	else if (keycode == DOWN_KEY)
		fdf->offset_y -= INC_OFFSET;
	else if (keycode == UP_KEY)
		fdf->offset_y += INC_OFFSET;
	action_aux(fdf);
}

/* Erases the image in memory; calculates and writes the new one */
/* Keeps angles always between 0-359 degrees and prints info bar */
/* if screen is big enough */

void	action_aux(t_fdf *fdf)
{
	ft_bzero(fdf->img.addr, WIDTH * HEIGHT * fdf->img.bpp / 8);
	projection(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img.img, 0, 0);	
}
