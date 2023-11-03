/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:56:56 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/03 16:27:46 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_mapch(char *rmap, t_cub *cub)
{
	char	*tmap;

	tmap = rmap;
	while (*rmap)
	{
		if (*rmap != '0' && *rmap != '1' && *rmap != 'N' && *rmap != 'S'
			&& *rmap != 'E' && *rmap != 'W' && *rmap != ' ' && *rmap != 'P')
		{
			printf("Error\nIllegal character %c detected on map.\n", *rmap);
			free(tmap);
			ft_error_handler(ERROR_MAP_F, cub);
		}
		rmap++;
	}
}

void	check_player(char *rmap, t_cub *cub)
{
	char	*tmap;
	int		player;
	int		cero;

	player = 0;
	cero = 0;
	tmap = rmap;
	while (*rmap)
	{
		if (*rmap == 'N' || *rmap == 'S' || *rmap == 'E'
			|| *rmap == 'W' || *rmap == 'P')
			player++;
		if (*rmap == '0')
			cero++;
		rmap++;
	}
	if (!player || player > 1 || !cero)
	{
		printf("Error\nThe player is missing, you have more than one player");
		printf(" or the map has no area for the player to move around.\n");
		free(tmap);
		ft_error_handler(ERROR_MAP_F, cub);
	}
}

void	str_to_array2(t_parse *p, int lx, int ly, char *smap)
{
	p->xl = 0;
	p->x = 0;
	p->y = 0;
	while (p->y < ly)
	{
		while (p->x < lx)
		{
			p->mapa[p->y][p->x] = smap[p->xl];
			p->x++;
			p->xl++;
		}
		p->x = 0;
		p->y++;
	}
}

char	**str_to_array(int lx, int ly, char *smap, t_cub *cub)
{
	t_parse	p;

	p.mapa = ft_calloc(ly, sizeof(char *));
	if (!p.mapa)
		ft_error_handler(ERROR_MEM, cub);
	p.y = 0;
	while (p.y < ly)
	{
		p.mapa[p.y] = ft_calloc(lx, sizeof(char *));
		if (!p.mapa[p.y++])
			ft_error_handler(ERROR_MEM, cub);
	}
	str_to_array2(&p, lx, ly, smap);
	return (p.mapa);
}

int	check_map(t_cub *cub)
{
	check_mapch(cub->raw_map, cub);
	check_player(cub->raw_map, cub);
	check_limits(cub);
	return (0);
}
