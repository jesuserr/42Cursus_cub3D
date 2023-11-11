/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:51:22 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/09 21:28:13 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_dellsti(void *img)
{
	if (((t_txt *)img)->img.img)
		mlx_destroy_image(((t_txt *)img)->img.mlx, ((t_txt *)img)->img.img);
	if (((t_txt *)img))
		free(((t_img *)img));
}

void	free_enemy(t_cub *cub)
{
	if (cub->enemy && cub->enemy->sprites)
	{
		ft_lstclear(cub->enemy->sprites, ft_dellsti);
		free(cub->enemy->sprites);
	}
	if (cub->enemy)
		free(cub->enemy);
}

void	free_character(t_cub *cub)
{
	if (cub->cha && cub->cha->cu)
	{
		ft_lstclear(cub->cha->cu, ft_dellsti);
		free(cub->cha->cu);
	}
	if (cub->cha && cub->cha->cd)
	{
		ft_lstclear(cub->cha->cd, ft_dellsti);
		free(cub->cha->cd);
	}
	if (cub->cha && cub->cha->cl)
	{
		ft_lstclear(cub->cha->cl, ft_dellsti);
		free(cub->cha->cl);
	}
	if (cub->cha && cub->cha->cr)
	{
		ft_lstclear(cub->cha->cr, ft_dellsti);
		free(cub->cha->cr);
	}
	if (cub->cha)
		free(cub->cha);
}
