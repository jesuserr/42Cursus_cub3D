/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/13 22:31:48 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	key_actions(t_cub *cub);
void	key_a_pressed(t_cub *cub);
void	key_d_pressed(t_cub *cub);
void	key_w_pressed(t_cub *cub);
void	key_s_pressed(t_cub *cub);

void	key_actions(t_cub *cub)
{
	if (cub->key.a_pressed == 1)
		key_a_pressed(cub);
	if (cub->key.d_pressed == 1)
		key_d_pressed(cub);
	if (cub->key.w_pressed == 1)
		key_w_pressed(cub);
	if (cub->key.s_pressed == 1)
		key_s_pressed(cub);
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

void	key_a_pressed(t_cub *cub)
{
	int		x_pos_temp;
	int		y_pos_temp;
	float	shift_offset;

	shift_offset = 1;
	if (cub->key.shift_pressed == 1)
		shift_offset = 0.5;
	x_pos_temp = cub->player.x_pos + ((cub->player.y_vector + \
	cub->player.offset_y * shift_offset) * cub->player.speed);
	y_pos_temp = cub->player.y_pos - ((cub->player.x_vector + \
	cub->player.offset_x * shift_offset) * cub->player.speed);
	if (cub->map[(x_pos_temp / WALL_SIZE) + (cub->player.y_pos / WALL_SIZE \
	* cub->x_elem)].color == 0)
		cub->player.x_pos += cub->player.y_vector * cub->player.speed;
	if (cub->map[(cub->player.x_pos / WALL_SIZE) + (y_pos_temp / WALL_SIZE \
	* cub->x_elem)].color == 0)
		cub->player.y_pos -= cub->player.x_vector * cub->player.speed;
}

void	key_d_pressed(t_cub *cub)
{
	int		x_pos_temp;
	int		y_pos_temp;
	float	shift_offset;

	shift_offset = 1;
	if (cub->key.shift_pressed == 1)
		shift_offset = 0.5;
	x_pos_temp = cub->player.x_pos - ((cub->player.y_vector + \
	cub->player.offset_y * shift_offset) * cub->player.speed);
	y_pos_temp = cub->player.y_pos + ((cub->player.x_vector + \
	cub->player.offset_x * shift_offset) * cub->player.speed);
	if (cub->map[(x_pos_temp / WALL_SIZE) + (cub->player.y_pos / WALL_SIZE \
	* cub->x_elem)].color == 0)
		cub->player.x_pos -= cub->player.y_vector * cub->player.speed;
	if (cub->map[(cub->player.x_pos / WALL_SIZE) + (y_pos_temp / WALL_SIZE \
	* cub->x_elem)].color == 0)
		cub->player.y_pos += cub->player.x_vector * cub->player.speed;
}

void	key_w_pressed(t_cub *cub)
{
	int		x_pos_temp;
	int		y_pos_temp;
	float	shift_offset;

	shift_offset = 1;
	if (cub->key.shift_pressed == 1)
		shift_offset = 0.5;
	x_pos_temp = cub->player.x_pos + ((cub->player.x_vector + \
	cub->player.offset_x * shift_offset) * cub->player.speed);
	y_pos_temp = cub->player.y_pos + ((cub->player.y_vector + \
	cub->player.offset_y * shift_offset) * cub->player.speed);
	if (cub->map[(x_pos_temp / WALL_SIZE) + (cub->player.y_pos / WALL_SIZE \
	* cub->x_elem)].color == 0)
		cub->player.x_pos += cub->player.x_vector * cub->player.speed;
	if (cub->map[(cub->player.x_pos / WALL_SIZE) + (y_pos_temp / WALL_SIZE \
	* cub->x_elem)].color == 0)
		cub->player.y_pos += cub->player.y_vector * cub->player.speed;
}

void	key_s_pressed(t_cub *cub)
{
	int		x_pos_temp;
	int		y_pos_temp;
	float	shift_offset;

	shift_offset = 1;
	if (cub->key.shift_pressed == 1)
		shift_offset = 0.5;
	x_pos_temp = cub->player.x_pos - ((cub->player.x_vector + \
	cub->player.offset_x * shift_offset) * cub->player.speed);
	y_pos_temp = cub->player.y_pos - ((cub->player.y_vector + \
	cub->player.offset_y * shift_offset) * cub->player.speed);
	if (cub->map[(x_pos_temp / WALL_SIZE) + (cub->player.y_pos / WALL_SIZE \
	* cub->x_elem)].color == 0)
		cub->player.x_pos -= cub->player.x_vector * cub->player.speed;
	if (cub->map[(cub->player.x_pos / WALL_SIZE) + (y_pos_temp / WALL_SIZE \
	* cub->x_elem)].color == 0)
		cub->player.y_pos -= cub->player.y_vector * cub->player.speed;
}
