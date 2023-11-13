/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:01:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/13 19:04:16 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_doors(t_cub *cub)
{
	int		i;
	int		cont;

	i = 0;
	cont = 0;
	while (i < cub->x_elem * cub->y_elem)
	{
		if (cub->map[i].color == DEF_DOOR)
		{
			cub->doors[cont].map_pos = i;
			cub->doors[cont].start_time = 0;
			cont++;
		}
		i++;
	}
	cub->doors[cont].map_pos = 0;
}

void	detect_door(t_cub *cub)
{
	int	position;
	int	angle;
	int	index;

	index = 0;
	angle = cub->player.angle;
	position = (cub->player.y_pos / WALL_SIZE) * cub->x_elem + \
	(cub->player.x_pos / WALL_SIZE);
	if (cub->map[position + 1].color == DEF_DOOR && (angle <= 45 || \
	angle >= 315))
		index = position + 1;
	else if (cub->map[position - 1].color == DEF_DOOR && (angle >= 135 && \
	angle <= 225))
		index = position - 1;
	else if (cub->map[position + (cub->x_elem)].color == DEF_DOOR && \
	(angle >= 225 && angle <= 315))
		index = position + (cub->x_elem);
	else if (cub->map[position - (cub->x_elem)].color == DEF_DOOR && \
	(angle >= 45 && angle <= 135))
		index = position - (cub->x_elem);
	if (index != 0)
	{
		cub->map[index].color = 0;
		assign_start_time(cub, index);
	}
}

void	assign_start_time(t_cub *cub, int pos)
{
	int	i;

	i = 0;
	while (cub->doors[i].map_pos != 0)
	{
		if (cub->doors[i].map_pos == pos)
		{
			cub->doors[i].start_time = get_time_ms();
			break ;
		}
		i++;
	}
}

long	get_time_ms(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	scan_doors(t_cub *cub)
{
	int		i;

	i = 0;
	while (cub->doors[i].map_pos != 0)
	{
		if (cub->doors[i].start_time != 0)
		{
			if ((get_time_ms() - cub->doors[i].start_time > DOOR_DELAY) && \
			((cub->player.y_pos / WALL_SIZE) * cub->x_elem + \
			(cub->player.x_pos / WALL_SIZE) != cub->doors[i].map_pos))
			{
				cub->map[cub->doors[i].map_pos].color = DEF_DOOR;
				cub->doors[i].start_time = 0;
			}
		}
		i++;
	}
}
