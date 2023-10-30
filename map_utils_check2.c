/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_check2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:36:37 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/30 21:57:57 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	freearray(char **mapa, int y)
{
	int	count;

	count = 0;
	while (count < y)
		free(mapa[count++]);
	free(mapa);
}

void	check_limits(t_cub *cub)
{
	//int		x;
	//int		y;
	char	**mapa;
	int		count;
	
	(void) mapa;

	count = 0;
	while (cub->raw_map[count])
		if (cub->raw_map[count++] == '0')
		{
			mapa = str_to_array(cub->x_elem, cub->y_elem, cub->raw_map);
			//checkmap();
			freearray(mapa, cub->y_elem);
			mapa = 0;
		}	
	
	
	/*/
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
	}*/
}
