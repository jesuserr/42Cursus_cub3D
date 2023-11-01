/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:08:23 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/01 21:55:58 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*read_raw_map(int fd, char **line, t_cub *cub)
{
	char	*tmap;
	char	*omap;
	int		size;

	tmap = 0;
	while (*line)
	{
		size = ft_strlen(*line) + ft_strlen(tmap);
		cub->y_elem++;
		if (cub->x_elem < (int) ft_strlen(*line))
			cub->x_elem = ft_strlen(*line) - 1;
		omap = tmap;
		tmap = ft_calloc(size + 1 , sizeof(char));
		if (!tmap)
			ft_error_handler(ERROR_MEM);
		ft_strlcpy(tmap, omap, size);
		ft_strlcat(tmap, *line, size + 1);
		free (omap);
		free (*line);
		*line = get_next_line(fd);
	}
	return (tmap);
}

void	rawmap_to_squaremap2(char *smap, char *rmap, t_cub *cub)
{
	int		x;
	int		x1;
	int		y;

	y = 0;
	x1 = 0;
	while (y < cub->y_elem)
	{
		x = 0;
		while (rmap[x1] && rmap[x1] != '\n')
		{
			smap[(y * cub->x_elem) + x] = rmap[x1];
			x++;
			x1++;
		}
		x1++;
		y++;
	}
}

char	*rawmap_to_squaremap(char *rmap, t_cub *cub)
{
	char	*smap;

	if (!rmap)
		ft_error_handler(ERROR_MAP_F);
	smap = ft_calloc((cub->y_elem * cub->x_elem) + 1, sizeof(char));
	if (!smap)
		ft_error_handler(ERROR_MEM);
	ft_memset(smap, ' ', cub->y_elem * cub->x_elem);
	rawmap_to_squaremap2(smap, rmap, cub);
	free(rmap);
	return (smap);
}

char	*read_map(char *file, t_cub *cub)
{
	int		fd;
	char	*line;
	char	*smap;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_handler(ERROR_FILE);
	line = get_next_line(fd);
	if (!line)
		ft_error_handler(ERROR_EMPTY);
	read_text_colors(fd, &line, cub);
	smap = rawmap_to_squaremap(read_raw_map(fd, &line, cub), cub);
	close (fd);
	return (smap);
}

void	init_map(char *file, t_cub *cub)
{
	ft_printf ("%s", BLUE);
	cub->cmap = ft_calloc(1, sizeof(t_map));
	if (!cub->cmap)
		ft_error_handler(ERROR_MEM);
	cub->raw_map = read_map(file, cub);
	check_map(cub);
	cub->map = parse_map(cub);
}
