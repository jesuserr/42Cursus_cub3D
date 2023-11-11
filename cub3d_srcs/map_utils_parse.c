/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:42:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/11 11:33:59 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_map_set(t_parse *p, t_cub *cub)
{
	p->map[p->xl].x = p->x * WALL_SIZE;
	p->map[p->xl].y = p->y * WALL_SIZE;
	p->map[p->xl].color = 0;
	if (cub->raw_map[p->xl] == '1')
		p->map[p->xl].color = DEF_COLOR;
	else if (cub->raw_map[p->xl] == 'N'
		|| cub->raw_map[p->xl] == 'S' || cub->raw_map[p->xl] == 'W'
		|| cub->raw_map[p->xl] == 'E')
	{
		cub->player.angle = 0;
		cub->player.x_pos = p->map[p->xl].x + (WALL_SIZE / 2);
		cub->player.y_pos = p->map[p->xl].y + (WALL_SIZE / 2);
		cub->player.orig_x_pos = cub->player.x_pos;
		cub->player.orig_y_pos = cub->player.y_pos;
		if (cub->raw_map[p->xl] == 'N')
			cub->player.angle = 90;
		else if (cub->raw_map[p->xl] == 'S')
			cub->player.angle = 270;
		else if (cub->raw_map[p->xl] == 'W')
			cub->player.angle = 180;
		cub->player.orig_angle = cub->player.angle;
	}
}

t_point	*parse_map(t_cub *cub)
{
	t_parse	p;

	p.x = 0;
	p.y = 0;
	p.xl = 0;
	p.map = ft_calloc(cub->x_elem * cub->y_elem, sizeof(t_point));
	if (!p.map)
		ft_error_handler(ERROR_MEM, cub);
	while (cub->raw_map && cub->raw_map[p.xl])
	{
		parse_map_set(&p, cub);
		p.xl++;
		p.x++;
		if (!(p.xl % cub->x_elem))
		{
			p.y++;
			p.x = 0;
		}
	}
	return (p.map);
}
