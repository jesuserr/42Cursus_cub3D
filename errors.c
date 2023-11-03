/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:04 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/03 17:45:06 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error_handler(int error, t_cub *cub)
{
	if (error == ERROR_ARGS)
		ft_printf ("%sError\nInvalid arguments - expected one map\n", RED);
	else if (error == ERROR_FILE)
		ft_printf ("%sError\nopening file\n", RED);
	else if (error == ERROR_MEM)
		ft_printf ("%sError\nallocating memory\n", RED);
	else if (error == ERROR_EMPTY)
		ft_printf ("%sError\nEmpty map\n", RED);	
	else if (error == ERROR_MAP)
		ft_printf ("%sError\nInvalid map format\n", RED);
	else if (error == ERROR_MLX)
		ft_printf ("%sError\nstarting MLX instances\n", RED);
	else if (error == ERROR_COLOR_F)
		ft_printf ("%sError\nThe color format is not RGB\n", RED);
	else if (error == ERROR_MAP_F)
		ft_printf ("%sError\nThe map format is not correct\n", RED);
	else if (error == ERROR_TXT)
		ft_printf ("%sError\nThe texture not correct\n", RED);
	close_window(cub, EXIT_FAILURE);
}
