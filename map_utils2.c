/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:08:23 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/29 21:44:44 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rgbtoint(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	ttorgbcheckcoma(char **line)
{
	int	count;

	count = 0;
	while (**line >= '0' && **line <= '9')
	{
		count++;
		(*line)++;
	}
	if (count > 3 || !count)
		ft_error_handler(ERROR_COLOR_F);
}

int	textrgbtoint(char *line)
{
	int	rgb[3];
	int	color;
	int	count;

	if (*(line + 1) != ' ')
		ft_error_handler(ERROR_COLOR_F);
	color = 0;
	while (color < 3)
	{
		count = 0;
		while (*line && *line != '\n' && (*line < '0' || *line > '9'))
		{
			if (*line == ',')
				count++;
			line++;
		}
		if (!*line || *line == '\n' || (color && count != 1))
			ft_error_handler(ERROR_COLOR_F);
		rgb[color] = ft_atoi(line);
		count = 0;
		ttorgbcheckcoma(&line);
		color++;
	}
	return (rgbtoint(rgb[0], rgb[1], rgb[2]));
}

char	*get_text(char *line)
{
	int		count;
	int		blanks;
	char	*tmp;

	count = 0;
	blanks = 0;
	tmp = line + 2;
	if (*tmp != ' ')
		return (0);
	while (*tmp == ' ')
	{
		tmp++;
		blanks++;
	}
	while (*tmp && *tmp != '\n')
	{
		count++;
		tmp++;
	}
	tmp = ft_calloc(count + 1, sizeof(char));
	if (!tmp)
		ft_error_handler(ERROR_MEM);
	ft_strlcpy(tmp, line + blanks + 2, count + 1);
	return (tmp);
}

void	read_text_colors(int fd, char **line, t_cub *cub)
{
	int	count;

	while (*line)
	{
		count = 0;
		while ((*line)[count] && ((*line)[count] == ' '
			|| (*line)[count] == '\t'))
			count++;
		if (!ft_strncmp(&(*line)[count], "NO", 2))
			cub->cmap->t_no = get_text(&(*line)[count]);
		else if (!ft_strncmp(&(*line)[count], "SO", 2))
			cub->cmap->t_so = get_text(&(*line)[count]);
		else if (!ft_strncmp(&(*line)[count], "EA", 2))
			cub->cmap->t_ea = get_text(&(*line)[count]);
		else if (!ft_strncmp(&(*line)[count], "WE", 2))
			cub->cmap->t_we = get_text(&(*line)[count]);
		else if (!ft_strncmp(&(*line)[count], "F", 1))
			cub->cmap->c_f = textrgbtoint(&(*line)[count]);
		else if (!ft_strncmp(&(*line)[count], "C", 1))
			cub->cmap->c_c = textrgbtoint(&(*line)[count]);
		else if (!ft_strncmp(&(*line)[count], "1", 1))
			break ;
		free(*line);
		*line = get_next_line(fd);
	}
}

char	*read_raw_map(int fd, char **line, t_cub *cub)
{
	char	*tmap;
	char	*omap;
	int	size;

	tmap = 0;
	while (*line)
	{
		size = ft_strlen(*line) + ft_strlen(tmap);
		cub->y_elem++;
		if (cub->x_elem < (int) ft_strlen(*line))
			cub->x_elem = ft_strlen(*line);
		omap = tmap;
		tmap = ft_calloc(size, sizeof(char) + 1);
		if (!tmap)
			ft_error_handler(ERROR_MEM);
		ft_strlcpy(tmap, omap, size);
		ft_strlcat(tmap, *line, size + 1);
		free (omap);
		*line = get_next_line(fd);
	}
	return (tmap);
}
char	*rawmap_to_squaremap(char *rmap, t_cub *cub)
{
	char	*smap;
	int		x;
	int		y;
	int		y1;

	if (!rmap)
		ft_error_handler(ERROR_MAP_F);
	smap = ft_calloc(cub->y_elem * cub->x_elem, sizeof(char) + 1);
	if (!smap)
		ft_error_handler(ERROR_MEM);
	ft_memset(smap, ' ', cub->y_elem * cub->x_elem);
	x = 0;
	y1 = 0;
		while (x < cub->x_elem)
	{
		y = 0;
		while (rmap[y1] && rmap[y1] != '\n')
		{
			smap[(x * cub->x_elem) +  y] = rmap[y1];
			y++;
			y1++;
		}
		y1++;
		x++;
	}
	free(rmap);
	return (smap);
}

char	*read_map2(char *file, t_cub *cub)
{
	int		fd;
	char	*line;
	char	*smap;
	int		x;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_handler(ERROR_FILE);
	line = get_next_line(fd);
	if (!line)
		ft_error_handler(ERROR_EMPTY);
	read_text_colors(fd, &line, cub);
	smap = rawmap_to_squaremap(read_raw_map(fd, &line, cub), cub);
	close (fd);
	x = 0;
	while (smap[x])
	{
		printf("%c", smap[x]);
		x++;
		if (!(x % cub->x_elem))
			printf("\n");
		
	}
	return (smap);
}

t_point *parse_map2(t_cub *cub)
{
	t_point	*map;
	int		x;
	int		y;
	int		xl;

	x = 0;
	y = 0;
	xl = 0;
	map = ft_calloc(cub->x_elem * cub->y_elem, sizeof(t_point));
	if (!map)
		ft_error_handler(ERROR_MEM);
	while (cub->raw_map && cub->raw_map[xl])
	{
		
		map[xl].x = x * WALL_SIZE + MAP_X_OFFSET;
		map[xl].y = y * WALL_SIZE + MAP_Y_OFFSET;
		map[xl].color = 0;
		if (cub->raw_map[xl] == '1')
			map[xl].color = DEF_COLOR;
		else if (cub->raw_map[xl] == 'P')
		{
			cub->player.angle = 0;
			cub->player.x_pos = map[xl].x + (WALL_SIZE / 2);
			cub->player.y_pos = map[xl].y + (WALL_SIZE / 2);
		}
		xl++;
		x++;
		if (!(xl % cub->x_elem))
		{
			y++;
			x = 0;
		}
	}
	return (map);
}

void	init_map2(char *file, t_cub *cub)
{
	ft_printf ("%s", BLUE);
	cub->cmap = ft_calloc(1, sizeof(t_map));
	if (!cub->cmap)
		ft_error_handler(ERROR_MEM);
	cub->raw_map = read_map2(file, cub);
//	check_map2(); >> Pending;
	cub->map = parse_map2(cub);
}
