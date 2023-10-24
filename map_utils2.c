/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:08:23 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/24 21:11:13 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map2(char *file, t_cub *cub)
{
	ft_printf ("%s", BLUE);
	cub->raw_map = read_map(file, cub);
	ft_printf ("\n\n");
	check_map(cub);
}