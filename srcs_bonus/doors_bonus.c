/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:01:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/13 10:04:12 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	detect_door(t_cub *cub)
{
	int	position;
	int	angle;

	angle = cub->player.angle;
	position = (cub->player.y_pos / WALL_SIZE) * cub->x_elem + \
	(cub->player.x_pos / WALL_SIZE);
	if (cub->map[position + 1].color == DEF_DOOR && (angle <= 30 || \
	angle >= 330))
		cub->map[position + 1].color = 0;
	else if (cub->map[position - 1].color == DEF_DOOR && (angle >= 150 && \
	angle <= 210))
		cub->map[position - 1].color = 0;
	else if (cub->map[position + (cub->x_elem)].color == DEF_DOOR && \
	(angle >= 240 && angle <= 300))
		cub->map[position + (cub->x_elem)].color = 0;
	else if (cub->map[position - (cub->x_elem)].color == DEF_DOOR && \
	(angle >= 60 && angle <= 120))
		cub->map[position - (cub->x_elem)].color = 0;
}
