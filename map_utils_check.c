/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:56:56 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/30 15:08:51 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_mapch(char *rmap)
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
			ft_error_handler(ERROR_MAP_F);
		}
		rmap++;
	}
}

void	check_player(char *rmap)
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
		printf("Error\nThe player is missing, you have more than one player or");
		printf(" the map has no area for the player to move around.\n");
		free(tmap);
		ft_error_handler(ERROR_MAP_F);
	}
}
char	**str_to_array(int lx, int ly, char *smap)
{
	int		xl;
	int		x;
	int		y;
	char	**mapa;
	
	mapa = ft_calloc(ly, sizeof(char *));
	if (!mapa)
		ft_error_handler(ERROR_MEM);
	y = 0;
	while (y < ly)
	{
		mapa[y] = ft_calloc(lx, sizeof(char *));
		if (!mapa[y++])
			ft_error_handler(ERROR_MEM);
	}	
	xl = 0;
	x = 0;
	y = 0;
	while (y < ly)
	{
		while (x < lx)
		{
			mapa[y][x] = smap[xl];
			x++;
			xl++;
		}
		x = 0;
		y++;
	}
	return (mapa);	
}

void	check_limits(t_cub *cub)
{
	int x;
	int y;
	char	**mapa;
	
	mapa = str_to_array(cub->x_elem, cub->y_elem, cub->raw_map);	
	x = 0;
	y = 0;
	while (y < cub->y_elem)
	{
		while (x < cub->x_elem)
		{
			printf("%c", mapa[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	
}


int	check_map(t_cub *cub)
{
	check_mapch(cub->raw_map);
	check_player(cub->raw_map);
	check_limits(cub);
	return (0);	
}
