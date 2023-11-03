/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:10:39 by jesuserr          #+#    #+#             */
/*   Updated: 2023/11/03 16:14:18 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error_handler(t_cub *cub, int error)
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
	close_window(cub, EXIT_FAILURE);
}

/* To be used mainly with double pointers used on ft_split */

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
