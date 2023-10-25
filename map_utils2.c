/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:08:23 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/25 22:03:31 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_text(char *line)
{
	int		count;
	char	*tmp;
	
	count = 0;
	tmp = line + 3;
	while (*tmp && *tmp != '\n')
	{
		count++;
		tmp++;
	}
	tmp = ft_calloc(count + 1, sizeof(char));
	if (!tmp)
		ft_error_handler(ERROR_MEM);
	ft_strlcpy(tmp, line + 3, count + 1);
	return (tmp);
}

void read_text_colors(int fd, char *line, int *count, t_cub *cub)
{
	int		map;
	
	map = 0;
	while (*line && !map)
	{
		while (*line && line[*count] == ' ')
				count++;
		if (!ft_strncmp(&line[*count], "NO", 2))
			cub->cmap->t_no = get_text(line);
		else if (!ft_strncmp(&line[*count], "SO", 2))
			cub->cmap->t_so = get_text(line);
		else if (!ft_strncmp(&line[*count], "EA", 2))
			cub->cmap->t_ea = get_text(line);
		else if (!ft_strncmp(&line[*count], "WE", 2))
			cub->cmap->t_we = get_text(line);
		else if (!ft_strncmp(&line[*count], "F", 1))
			ft_printf("F\n");
		else if (!ft_strncmp(&line[*count], "C", 1))
			ft_printf("C\n");
		else if (!ft_strncmp(&line[*count], "1", 1))
			map++;
		line = get_next_line(fd);
	}		
}

char	*read_map2(char *file, t_cub *cub)
{
	int		fd;
	char	*line;
	int		count;

	(void) count;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_handler(ERROR_FILE);
	line = get_next_line(fd);
	if (!line)
		ft_error_handler(ERROR_EMPTY);
	read_text_colors(fd, line, &count, cub);
	printf("NO->%s\n", cub->cmap->t_no);
	printf("SO->%s\n", cub->cmap->t_so);
	printf("EA->%s\n", cub->cmap->t_ea);
	printf("WE->%s\n", cub->cmap->t_we);
			
	return 0;
}

void	init_map2(char *file, t_cub *cub)
{
	ft_printf ("%s", BLUE);
	cub->cmap = ft_calloc(1, sizeof(t_map));
	if (!cub->cmap)
		ft_error_handler(ERROR_MEM);
	cub->raw_map = read_map2(file, cub);
	ft_printf ("\n\n");
	//check_map(cub);
}
