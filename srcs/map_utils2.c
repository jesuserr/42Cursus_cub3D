/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:44:56 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/14 21:50:54 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_text(char *line, t_cub *cub)
{
	int		count;
	int		blanks;
	char	*tmp;

	count = 0;
	blanks = 0;
	tmp = line;
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
		ft_error_handler(ERROR_MEM, cub);
	ft_strlcpy(tmp, line + blanks, count + 1);
	return (tmp);
}

void	read_text_colors2(char **line, int count, t_cub *cub)
{
	if (!cub->cmap->t_no && !ft_strncmp(&(*line)[count], "NO ", 3))
		cub->cmap->t_no = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->t_so && !ft_strncmp(&(*line)[count], "SO ", 3))
		cub->cmap->t_so = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->t_ea && !ft_strncmp(&(*line)[count], "EA ", 3))
		cub->cmap->t_ea = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->t_we && !ft_strncmp(&(*line)[count], "WE ", 3))
		cub->cmap->t_we = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->c_c && !ft_strncmp(&(*line)[count], "C ", 2))
		cub->cmap->c_c = textrgbtoint(&(*line)[count], cub);
	else if (!cub->cmap->c_f && !ft_strncmp(&(*line)[count], "F ", 2))
		cub->cmap->c_f = textrgbtoint(&(*line)[count], cub);
	else if ((*line)[count] != '\n' && (*line)[count] != '1')
	{
		ft_printf("\nError\nUnexpected key or double key %s", &(*line)[count]);
		ft_error_handler(ERROR_MAP_F, cub);
	}
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
		read_text_colors2(line, count, cub);
		if (!ft_strncmp(&(*line)[count], "1", 1))
			break ;
		free(*line);
		*line = get_next_line(fd);
	}
}
