/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:37:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/13 00:51:16 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_list	**load_character_sprites(char *path, int scale, t_cub *cub)
{
	t_list	**tmp;

	if (path)
	{
		tmp = ft_calloc(1, sizeof(t_list **));
		if (!tmp)
			ft_error_handler(ERROR_MEM, cub);
		ft_loadimgs(path, tmp, scale, cub);
		cub->cha->current = (*tmp)->content;
		return (tmp);
	}
	return (0);
}

void	load_character(int scale, t_cub *cub)
{
	static int	i = 0;

	if (i == 0)
		ft_printf("Loading character.. ");
	if (!cub->cha)
		cub->cha = ft_calloc(1, sizeof(t_character));
	cub->cha->cr = load_character_sprites(cub->cmap->cha_r, scale, cub);
	cub->cha->cl = load_character_sprites(cub->cmap->cha_l, scale, cub);
	cub->cha->cd = load_character_sprites(cub->cmap->cha_d, scale, cub);
	cub->cha->cu = load_character_sprites(cub->cmap->cha_u, scale, cub);
	if (i == 0)
		ft_printf("OK!\n");
	i++;
}

void	cha_hook(t_cub *cub)
{
	if (cub->cha && cub->cha->current
		&& cub->cha->timer++ > 6 - (cub->key.shift_pressed * 5))
	{
		if (cub->key.w_pressed && cub->cha->cu)
			cub->cha->current = move_sprite(*cub->cha->cu, cub->cha->current);
		else if (cub->key.s_pressed && cub->cha->cd)
			cub->cha->current = move_sprite(*cub->cha->cd, cub->cha->current);
		else if (cub->key.a_pressed && cub->cha->cl)
			cub->cha->current = move_sprite(*cub->cha->cl, cub->cha->current);
		else if (cub->key.d_pressed && cub->cha->cr)
			cub->cha->current = move_sprite(*cub->cha->cr, cub->cha->current);
		cub->cha->timer = 0;
	}
	if (cub->cha && cub->cha->current)
		mlx_put_image_to_window(cub->mlx, cub->mlx_win, \
		cub->cha->current->img.img, (WIDTH / 2) - cub->cha->current->w / 2, \
		HEIGHT - (cub->cha->current->h / cub->player.zoom));
}

void	cha_releasekey(t_cub *cub)
{
	if (cub->cha && cub->cha->cu)
		cub->cha->current = ((t_list *)*cub->cha->cu)->content;
}
