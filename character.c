/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:37:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/09 19:04:05 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_list	**load_character_sprites(char *path, t_cub *cub)
{
	t_list	**tmp;
	if (path)
	{
		tmp = ft_calloc(1, sizeof(t_list **));
		if (!tmp)
			ft_error_handler(ERROR_MEM, cub);
		ft_loadimgs(path, tmp, cub);
		cub->cha->current = (*tmp)->content;
		return tmp;
	}
	return (0);
}

void	load_character(t_cub *cub)
{
	ft_printf("Loading character.. ");
	if (!cub->cha)
			cub->cha = ft_calloc(1, sizeof(t_character));
	cub->cha->cr = load_character_sprites(cub->cmap->cha_r, cub);
	cub->cha->cl = load_character_sprites(cub->cmap->cha_l, cub);
	cub->cha->cd = load_character_sprites(cub->cmap->cha_d, cub);
	cub->cha->cu = load_character_sprites(cub->cmap->cha_u, cub);
	ft_printf("OK!\n");
}