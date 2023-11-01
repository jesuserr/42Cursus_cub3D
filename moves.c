/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/01 13:41:15 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_actions(t_cub *cub)
{
	if (cub->key.a_pressed == 1)
	{
		cub->player.x_pos = cub->player.x_pos + (cub->player.y_vector * INC_OFFSET);
		cub->player.y_pos = cub->player.y_pos - (cub->player.x_vector * INC_OFFSET);
	}
	if (cub->key.d_pressed == 1)
	{
		cub->player.x_pos = cub->player.x_pos - (cub->player.y_vector * INC_OFFSET);
		cub->player.y_pos = cub->player.y_pos + (cub->player.x_vector * INC_OFFSET);
	}
	if (cub->key.w_pressed == 1)
	{
		cub->player.x_pos = cub->player.x_pos + (cub->player.x_vector * INC_OFFSET);
		cub->player.y_pos = cub->player.y_pos + (cub->player.y_vector * INC_OFFSET);
	}
	if (cub->key.s_pressed == 1)
	{
		cub->player.x_pos = cub->player.x_pos - (cub->player.x_vector * INC_OFFSET);
		cub->player.y_pos = cub->player.y_pos - (cub->player.y_vector * INC_OFFSET);
	}
	key_actions_2(cub);
}

void	key_actions_2(t_cub *cub)
{
	if (cub->key.left_pressed == 1)
	{
		cub->player.angle += ROT_ANGLE_INC;
		if (cub->player.angle >= 360)
			cub->player.angle = 0;
		calc_player_vector(cub);
	}
	else if (cub->key.right_pressed == 1)
	{
		cub->player.angle -= ROT_ANGLE_INC;
		if (cub->player.angle < 0)
			cub->player.angle = 360 - ROT_ANGLE_INC;
		calc_player_vector(cub);
	}
}

int	check_collision(int keycode, t_cub *cub)
{
	int	dist_to_wall;

	dist_to_wall = INC_OFFSET * 1.5;
	if (keycode == A_KEY && (cub->map[(cub->player.x_pos - (dist_to_wall)) / \
	WALL_SIZE + (cub->player.y_pos / WALL_SIZE * cub->x_elem)].color == 0))
		return (INC_OFFSET);
	if (keycode == D_KEY && (cub->map[(cub->player.x_pos + (dist_to_wall)) / \
	WALL_SIZE + (cub->player.y_pos / WALL_SIZE * cub->x_elem)].color == 0))
		return (INC_OFFSET);
	if (keycode == S_KEY && (cub->map[(cub->player.x_pos / WALL_SIZE + \
	(cub->player.y_pos + (dist_to_wall)) / WALL_SIZE * cub->x_elem)].color \
	== 0))
		return (INC_OFFSET);
	if (keycode == W_KEY && (cub->map[(cub->player.x_pos / WALL_SIZE + \
	(cub->player.y_pos - (dist_to_wall)) / WALL_SIZE * cub->x_elem)].color \
	== 0))
		return (INC_OFFSET);
	return (0);
}

/* Stuff for debugging
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
(cub->player.y_pos / WALL_SIZE * cub->x_elem)].color);
mlx_string_put(cub->mlx, cub->mlx_win, 500, 70, WHITE, str);
free(str);
printf("%d %d %d %f %f\n", cub->player.x_pos, cub->player.y_pos, \
cub->player.angle, cub->player.x_vector, cub->player.y_vector);
*/