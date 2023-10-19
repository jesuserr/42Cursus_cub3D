/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:23:42 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/19 01:25:43 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Uses GNL to read the fdf map and counts the elements of the first row */

char	*read_map(char *file, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	*map;
	char	*backup_map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_handler(ERROR_FILE);
	//ft_printf ("%sReading Map..... \n", BLUE);
	line = get_next_line(fd);
	if (!line)
		ft_error_handler(ERROR_EMPTY);
	fdf->x_elem = count_x_elem(line, 1);
	map = ft_strdup("");
	while (line != NULL)
	{
		ft_printf("%s",line);
		backup_map = map;
		map = gnl_strjoin(map, line, 1);
		free (line);
		if (!map)
			free_and_exit(ERROR_MEM, backup_map);
		line = get_next_line(fd);		
	}
	printf("\n\n");
	close (fd);
	return (map);
}

/* Returns the number of elements on a given line */
/* Same function as the one used in ft_printf with modification */
/* to deal with line feeds \n (var jump) */

int	count_x_elem(char *line, int jump)
{
	int	n;
	(void)jump;
	
	n = 0;
	while (*line)
	{
		n++;
		line++;
	}
	n--;
	return (n);
}

/* Verifies that all lines have the same number of elements */
/* and that no line contains any forbidden characters (ALLOWED_CHR) */
/* If there is only one line (no 3D element) -> finishes too */
/* After map parsing, centers and scales Z coordinates, figure 100% centered */

void	check_map(t_fdf *fdf)
{
	char	**split;
	char	*line;
	int		i;

	split = ft_split(fdf->raw_map, '\n');
	fdf->y_elem = 0;
	while (split[fdf->y_elem])
		line = split[fdf->y_elem++];
	fdf->map = malloc (sizeof(t_point) * fdf->y_elem * fdf->x_elem);
	if (!fdf->map)
		free_split_and_exit(split, ERROR_MEM, fdf->raw_map);
	i = 0;
	//ft_printf ("%sOK!\nParsing Map..... \n", BLUE);
	//ft_printf ("%d %d\n", fdf->x_elem, fdf->y_elem);
	while (split[i])
		parse_map(fdf, split[i++]);
	free_split(split);
}

/* Parses the map in such way that X = 0 and Y = 0 are in the center */
/* Determines max and min values of Z to center all heights later */
/* Note: k can be replaced by (i + (j * fdf->x_elem)) */
/*       harder to read but can help to save a couple of lines if needed */

void	parse_map(t_fdf *fdf, char *line)
{
	int			i;
	static int	j = 0;
	static int	k = 0;

	i = 0;
	while (i < fdf->x_elem)
	{
		fdf->map[k].x = i * SQUARE_SIZE + INIT_OFFSET_X;
		fdf->map[k].y = j * SQUARE_SIZE + INIT_OFFSET_Y;
		fdf->map[k].color = 0;
		if (!ft_strncmp (line, "1" ,1))
			fdf->map[k].color = DEF_COLOR;
		else if (!ft_strncmp (line, "P" ,1))
		{
			fdf->player.x_pos = fdf->map[k].x + (SQUARE_SIZE / 2);
			fdf->player.y_pos = fdf->map[k].y + (SQUARE_SIZE / 2);
		}
		//printf("(%06.2f %06.2f %d) ", fdf->map[k].x, fdf->map[k].y, fdf->map[k].color);
		printf("(%06.2f %06.2f) ", fdf->map[k].x, fdf->map[k].y);
		line++;
		k++;
		i++;
	}
	printf("\n");
	j++;	
}

