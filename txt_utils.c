/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:48:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/09 11:37:33 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_txt	*load_txt(char *file, t_cub *cub)
{
	t_txt	*tmp;

	if (!file)
		return (0);
	tmp = ft_calloc(1, sizeof(t_txt));
	if (!tmp)
		ft_error_handler(ERROR_MEM, cub);
	if (ft_strnstr(file, ".png", ft_strlen(file))
		|| ft_strnstr(file, ".PNG", ft_strlen(file)))
		tmp->img.img = mlx_png_file_to_image(cub->mlx, file, &tmp->w, &tmp->h);
	else if (ft_strnstr(file, ".xpm", ft_strlen(file))
		|| ft_strnstr(file, ".XPM", ft_strlen(file)))
		tmp->img.img = mlx_xpm_file_to_image(cub->mlx, file, &tmp->w, &tmp->h);
	if (!tmp->img.img)
	{
		free(tmp);
		printf("\nError\nLoading texture %s ", file);
		printf("file not found or unsupported format (PNG or XPM supported)\n");
		ft_error_handler(ERROR_TXT, cub);
	}
	tmp->img.addr = mlx_get_data_addr(tmp->img.img, &tmp->img.bpp, \
	&tmp->img.len, &tmp->img.endian);
	return (tmp);
}

void	load_textures(t_cub *cub)
{
	ft_printf("Loading textures... ");
	if (cub->cmap)
	{
		cub->textures[0] = load_txt(cub->cmap->t_ea, cub);
		cub->textures[1] = load_txt(cub->cmap->t_no, cub);
		cub->textures[2] = load_txt(cub->cmap->t_we, cub);
		cub->textures[3] = load_txt(cub->cmap->t_so, cub);
		cub->textures[4] = NULL;
	}
	ft_printf("OK!\n");
}
