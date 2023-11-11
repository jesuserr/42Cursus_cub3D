/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:10:15 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/11 21:46:05 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	scale_img2(t_txt *img, t_txt *simg, int scale)
{
	char	*dst;
	char	*or;
	int		w;
	int		h;

	w = 0;
	while (w < img->w * scale)
	{
		h = 0;
		while (h < img->h * scale)
		{
			dst = simg->img.addr + (w * simg->img.len + h \
			* (simg->img.bpp / 8));
			or = img->img.addr + ((w / scale) * img->img.len \
			+ (h / scale) * (img->img.bpp / 8));
			*(unsigned int *)dst = *(unsigned int *)or;
			h++;
		}
		w++;
	}
}

t_txt	*scale_img(t_txt *img, int scale, t_cub *cub)
{
	t_txt	*simg;

	if (!img)
		return (0);
	simg = ft_calloc(1, sizeof(t_txt));
	if (!simg)
		ft_error_handler(ERROR_MEM, cub);
	simg->img.img = mlx_new_image(cub->mlx, img->w * scale, img->h * scale);
	simg->img.addr = mlx_get_data_addr(simg->img.img, &simg->img.bpp, \
	&simg->img.len, &simg->img.endian);
	scale_img2(img, simg, scale);
	simg->h = img->h * scale;
	simg->w = img->w * scale;
	return (simg);
}
