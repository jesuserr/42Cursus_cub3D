/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_check2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:36:37 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/15 13:34:28 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	freearray(char **mapa, int y)
{
	int	count;

	count = 0;
	while (count < y)
		free(mapa[count++]);
	free(mapa);
}

void	ft_checkmapclose(char **mapa, int y, int x, t_cub *cub)
{
	if (x < 0 || x >= cub->x_elem || y < 0
		|| y >= cub->y_elem || mapa[y][x] == ' ')
	{
		cub->mapconsistency++;
		return ;
	}
	if (mapa[y][x] == '1')
		return ;
	mapa[y][x] = '1';
	ft_checkmapclose(mapa, y - 1, x, cub);
	ft_checkmapclose(mapa, y + 1, x, cub);
	ft_checkmapclose(mapa, y, x - 1, cub);
	ft_checkmapclose(mapa, y, x + 1, cub);
}

void	check_limits(t_cub *cub)
{
	char	**mapa;
	int		count;

	count = 0;
	cub->mapconsistency = 0;
	while (cub->raw_map[count])
	{
		if (cub->raw_map[count] == 'P' || cub->raw_map[count] == 'S'
			|| cub->raw_map[count] == 'N' || cub->raw_map[count] == 'E'
			|| cub->raw_map[count] == 'W' || cub->raw_map[count] == '0')
		{
			mapa = str_to_array(cub->x_elem, cub->y_elem, cub->raw_map, cub);
			ft_checkmapclose(mapa, count / cub->x_elem,
				(count % cub->x_elem), cub);
			freearray(mapa, cub->y_elem);
			if (cub->mapconsistency)
			{
				printf("\nError\nThe map is not closed at one of the edges.\n");
				ft_error_handler(ERROR_MAP_F, cub);
			}
			mapa = 0;
		}
		count++;
	}
}
