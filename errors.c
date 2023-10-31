/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:10:39 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/31 21:50:10 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error_handler(int error)
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
	exit(EXIT_FAILURE);
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

/* Used mainly to save lines of code and meet norm on some cases */

void	free_and_exit(int error, char *ptr)
{
	free(ptr);
	ft_error_handler(error);
}

/* Another free function to save space - Two previous functions combined */

void	free_split_and_exit(char **str, int error, char *ptr)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	free(ptr);
	ft_error_handler(error);
}

/* Function to exit in controlled way when there is an error during */
/* the mlx init. Flag controls the step where the error happened and */
/* frees in consequence */

void	free_map_and_exit(t_cub *cub, int error, int flag)
{
	if (flag == 1)
		free(cub->mlx);
	if (flag == 2)
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	free(cub->raw_map);
	free(cub->map);
	ft_error_handler(error);
}
