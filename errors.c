/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:04 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/03 18:07:02 by jesuserr         ###   ########.fr       */
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

int	close_window(t_cub *cub, int exitcode)
{
	close_cmaps(cub);
	if (cub->map)
		free(cub->map);
	if (cub->raw_map)
		free(cub->raw_map);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->mlx_win)
	{
		mlx_clear_window(cub->mlx, cub->mlx_win);
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	}
	if (cub->mlx)
	{
		mlx_destroy_image(cub->mlx, ((mlx_ptr_t *)cub->mlx)->img_list);
		free(((mlx_ptr_t *)cub->mlx)->img_list);
		free(cub->mlx);
	}
	exit (exitcode);
	ft_memset(cub, 0, sizeof(t_cub));
	return (exitcode);
}

void	close_cmaps(t_cub *cub)
{
	if (cub->cmap && cub->cmap->t_so)
		free(cub->cmap->t_so);
	if (cub->cmap && cub->cmap->t_we)
		free(cub->cmap->t_we);
	if (cub->cmap && cub->cmap->t_no)
		free(cub->cmap->t_no);
	if (cub->cmap && cub->cmap->t_ea)
		free(cub->cmap->t_ea);
	if (cub->cmap)
		free(cub->cmap);
}
