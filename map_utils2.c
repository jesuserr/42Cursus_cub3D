/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:44:56 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/01 21:43:57 by cescanue         ###   ########.fr       */
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
