/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:47:14 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/09 12:11:25 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_putimgtolst(char *file, t_list **lst, t_cub *cub)
{
	t_txt	*img;

	img = ft_calloc(1, sizeof(t_txt));
	if (!img)
		ft_error_handler(ERROR_MEM, cub);
	if (ft_strnstr(file, ".png", ft_strlen(file))
		|| ft_strnstr(file, ".PNG", ft_strlen(file)))
		img->img.img = mlx_png_file_to_image(cub->mlx, file, &img->w, &img->h);
	else if (ft_strnstr(file, ".xpm", ft_strlen(file))
		|| ft_strnstr(file, ".XPM", ft_strlen(file)))
		img->img.img = mlx_xpm_file_to_image(cub->mlx, file, &img->w, &img->h);
	if (!img->img.img)
	{
		ft_printf("\nError\nLoading sprite - %s", file);
		free(img);
		ft_error_handler(ERROR_SPRITE, cub);
	}
	img->img.addr = mlx_get_data_addr(img->img.img, &img->img.bpp, \
	&img->img.len, &img->img.endian);
	img->img.mlx = cub->mlx;
	ft_lstadd_back(lst, ft_lstnew(img));
}

void	ft_loadimgs(char *path, t_list **lst, t_cub *cub)
{
	int		fd;
	char	file[200];
	char	*tmp;

	ft_strlcpy(file, path, 200);
	ft_strlcat(file, "files.txt", 200);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("\nError\nLoading %s, list of sprites.", file);
		ft_error_handler(ERROR_SPRITE, cub);
	}
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (tmp && tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		ft_strlcpy(file, path, 200);
		ft_strlcat(file, tmp, 200);
		ft_putimgtolst(file, lst, cub);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close (fd);
}

void	loading_sprites(t_cub *cub)
{
	ft_printf("Loading sprites.... ");
	if (cub->cmap->s_enemy)
	{
		cub->enemy = ft_calloc(1, sizeof(t_enemy));
		if (!cub->enemy)
			ft_error_handler(ERROR_MEM, cub);
		cub->enemy->sprites = ft_calloc(1, sizeof(t_list **));
		if (!cub->enemy->sprites)
			ft_error_handler(ERROR_MEM, cub);
		ft_loadimgs(cub->cmap->s_enemy, cub->enemy->sprites, cub);
		cub->enemy->current = (*cub->enemy->sprites)->content;
	}
	ft_printf("OK!\n");
}

void	move_sprite(t_enemy *enemy, t_cub *cub)
{
	t_list	*lst;

	if (enemy)
	{
		lst = *enemy->sprites;
		while (lst)
		{
			if (cub->enemy->current == lst->content)
			{
				if (lst->next)
					cub->enemy->current = lst->next->content;
				else
					cub->enemy->current = 0;
				break ;
			}
			lst = lst->next;
		}
		if (!cub->enemy->current || !lst)
			cub->enemy->current = ((t_list *)*cub->enemy->sprites)->content;
	}
}
