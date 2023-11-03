/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:48:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/03 17:19:59 by cescanue         ###   ########.fr       */
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
		tmp->txt = mlx_xpm_file_to_image(cub->mlx, file, &tmp->w, &tmp->h);
	else if (ft_strnstr(file, ".xpm", ft_strlen(file))
		|| ft_strnstr(file, ".XPM", ft_strlen(file)))
		tmp->txt = mlx_xpm_file_to_image(cub->mlx, file, &tmp->w, &tmp->h);
	if (!tmp->txt)
	{
		free(tmp);
		printf("\nError\nLoading texture %s", file);
		printf("file not found or unsupported format (PNG or XPM supported)");
		ft_error_handler(ERROR_TXT, cub);
	}
	return (tmp);
}
