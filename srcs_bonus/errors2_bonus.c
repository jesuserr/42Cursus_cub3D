/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:51:22 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/16 12:50:06 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_dellsti(void *img)
{
	if (((t_txt *)img)->img.img)
		mlx_destroy_image(((t_txt *)img)->img.mlx, ((t_txt *)img)->img.img);
	if (((t_txt *)img))
		free(((t_img *)img));
}

void	free_character2(t_cub *cub)
{
	t_list		**tmp;
	t_character	*ctmp;

	if (cub->cha && cub->cha->cr)
	{
		tmp = cub->cha->cr;
		cub->cha->cr = 0;
		ft_lstclear(tmp, ft_dellsti);
		free(tmp);
	}
	if (cub->cha)
	{
		ctmp = cub->cha;
		cub->cha = 0;
		free(ctmp);
	}
}

void	free_character(t_cub *cub)
{
	t_list	**tmp;

	if (cub->cha && cub->cha->cu)
	{
		tmp = cub->cha->cu;
		cub->cha->cu = 0;
		ft_lstclear(tmp, ft_dellsti);
		free(tmp);
	}
	if (cub->cha && cub->cha->cd)
	{
		tmp = cub->cha->cd;
		cub->cha->cd = 0;
		ft_lstclear(tmp, ft_dellsti);
		free(tmp);
	}
	if (cub->cha && cub->cha->cl)
	{
		tmp = cub->cha->cl;
		cub->cha->cl = 0;
		ft_lstclear(tmp, ft_dellsti);
		free(tmp);
	}
	free_character2(cub);
}

void	free_characters(t_cub *cub)
{
	cub->cha = cub->cha1;
	free_character(cub);
	cub->cha1 = 0;
	cub->cha = cub->cha2;
	free_character(cub);
	cub->cha1 = 0;
	cub->cha = 0;
}
