/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:47:14 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/11 21:46:03 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_txt	*ft_putimgtolstscale(int scale, t_txt *img, t_cub *cub)
{
	t_txt	*simg;

	if (scale > 1)
	{
		simg = scale_img(img, scale, cub);
		mlx_destroy_image(cub->mlx, img->img.img);
		free(img);
		return (simg);
	}
	return (img);
}

void	ft_putimgtolst(char *file, t_list **lst, int scale, t_cub *cub)
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
	img = ft_putimgtolstscale(scale, img, cub);
	img->img.mlx = cub->mlx;
	ft_lstadd_back(lst, ft_lstnew(img));
}

void	ft_loadimgs(char *path, t_list **lst, int scale, t_cub *cub)
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
		ft_putimgtolst(file, lst, scale, cub);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close (fd);
}

t_txt	*move_sprite(t_list *lst, void *current)
{
	t_txt	*next;
	t_list	*tlst;

	tlst = lst;
	next = 0;
	if (lst)
	{
		while (lst)
		{
			if (current == lst->content)
			{
				if (lst->next)
					next = lst->next->content;
				else
					next = 0;
				break ;
			}
			lst = lst->next;
		}
		if (!next || !lst)
			next = tlst->content;
	}
	return (next);
}
