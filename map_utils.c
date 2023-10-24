/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:23:42 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/24 10:54:36 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Uses GNL to read the cub map and counts the elements of the first row */

char	*read_map(char *file, t_cub *cub)
{
	int		fd;
	char	*line;
	char	*map;
	char	*backup_map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_handler(ERROR_FILE);
	line = get_next_line(fd);
	if (!line)
		ft_error_handler(ERROR_EMPTY);
	cub->x_elem = ft_strlen(line) - 1;
	map = ft_strdup("");
	while (line != NULL)
	{
		ft_printf("%s", line);
		backup_map = map;
		map = gnl_strjoin(map, line, 1);
		free (line);
		if (!map)
			free_and_exit(ERROR_MEM, backup_map);
		line = get_next_line(fd);
	}
	close (fd);
	return (map);
}

void	check_map(t_cub *cub)
{
	char	**split;
	char	*line;
	int		i;

	split = ft_split(cub->raw_map, '\n');
	cub->y_elem = 0;
	while (split[cub->y_elem])
		line = split[cub->y_elem++];
	cub->map = malloc (sizeof(t_point) * cub->y_elem * cub->x_elem);
	if (!cub->map)
		free_split_and_exit(split, ERROR_MEM, cub->raw_map);
	i = 0;
	while (split[i])
		parse_map(cub, split[i++]);
	free_split(split);
}

/* CARLOS, aqui empieza la parte en la que estoy trabajando */

void	parse_map(t_cub *cub, char *line)
{
	int			i;
	static int	j = 0;
	static int	k = 0;

	i = 0;
	while (i < cub->x_elem)
	{
		cub->map[k].x = i * WALL_SIZE + MAP_X_OFFSET;
		cub->map[k].y = j * WALL_SIZE + MAP_Y_OFFSET;
		cub->map[k].color = 0;
		if (!ft_strncmp (line, "1", 1))
			cub->map[k].color = DEF_COLOR;
		else if (!ft_strncmp (line, "P", 1))
		{
			cub->player.angle = 0;
			cub->player.x_pos = cub->map[k].x + (WALL_SIZE / 2);
			cub->player.y_pos = cub->map[k].y + (WALL_SIZE / 2);
		}
		printf("(%04d %04d %08d) ", cub->map[k].x, cub->map[k].y, cub->map[k].color);
		line++;
		k++;
		i++;
	}
	printf("\n");
	j++;
}
