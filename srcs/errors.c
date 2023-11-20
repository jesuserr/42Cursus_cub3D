/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:04 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/20 19:50:08 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error_handler(int error, t_cub *cub)
{
	if (error == ERROR_ARGS)
		ft_printf ("%s\nError\nInvalid arguments - expected one map\n", RED);
	else if (error == ERROR_FILE)
		ft_printf ("%s\nError\nopening file\n", RED);
	else if (error == ERROR_MEM)
		ft_printf ("%s\nError\nallocating memory\n", RED);
	else if (error == ERROR_EMPTY)
		ft_printf ("%s\nError\nEmpty map\n", RED);
	else if (error == ERROR_MAP)
		ft_printf ("%s\nError\nInvalid map format\n", RED);
	else if (error == ERROR_MLX)
		ft_printf ("%s\nError\nstarting MLX instances\n", RED);
	else if (error == ERROR_COLOR_F)
		ft_printf ("%s\nError\nThe color format is not RGB\n", RED);
	else if (error == ERROR_MAP_F)
		ft_printf ("%s\nError\nThe map format is not correct\n", RED);
	else if (error == ERROR_TXT)
		ft_printf ("%s\nError\nError in some of the textures\n", RED);
	close_window(cub, EXIT_FAILURE);
}

int	close_window(t_cub *cub, int exitcode)
{
	free_textures(cub);
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
}

void	free_textures(t_cub *cub)
{
	if (cub->textures[0])
	{
		mlx_destroy_image(cub->mlx, cub->textures[0]->img.img);
		free(cub->textures[0]);
	}
	if (cub->textures[1])
	{
		mlx_destroy_image(cub->mlx, cub->textures[1]->img.img);
		free(cub->textures[1]);
	}
	if (cub->textures[2])
	{
		mlx_destroy_image(cub->mlx, cub->textures[2]->img.img);
		free(cub->textures[2]);
	}
	if (cub->textures[3])
	{
		mlx_destroy_image(cub->mlx, cub->textures[3]->img.img);
		free(cub->textures[3]);
	}
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
