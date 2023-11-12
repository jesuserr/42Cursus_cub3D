/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:44:56 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/12 18:23:53 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ttorgbcheckcoma(char **line, t_cub *cub)
{
	int	count;

	count = 0;
	while (**line >= '0' && **line <= '9')
	{
		count++;
		(*line)++;
	}
	if (count > 3 || !count)
		ft_error_handler(ERROR_COLOR_F, cub);
}

int	textrgbtoint(char *line, t_cub *cub)
{
	int	rgb[3];
	int	color;
	int	count;

	if (*(line + 1) != ' ')
		ft_error_handler(ERROR_COLOR_F, cub);
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
			ft_error_handler(ERROR_COLOR_F, cub);
		rgb[color] = ft_atoi(line);
		count = 0;
		ttorgbcheckcoma(&line, cub);
		color++;
	}
	return (((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]));
}

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
	if (!ft_strncmp(&(*line)[count], "NO", 2))
		cub->cmap->t_no = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "SO", 2))
		cub->cmap->t_so = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "EA", 2))
		cub->cmap->t_ea = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "WE", 2))
		cub->cmap->t_we = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "DO", 2))
		cub->cmap->t_door = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "ENEMY", 5))
		cub->cmap->s_enemy = get_text(&(*line)[count + 5], cub);
	else if (!ft_strncmp(&(*line)[count], "CU", 2))
		cub->cmap->cha_u = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "CD", 2))
		cub->cmap->cha_d = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "CL", 2))
		cub->cmap->cha_l = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "CR", 2))
		cub->cmap->cha_r = get_text(&(*line)[count + 2], cub);
	else if (!ft_strncmp(&(*line)[count], "C", 1))
		cub->cmap->c_c = textrgbtoint(&(*line)[count], cub);
	else if (!ft_strncmp(&(*line)[count], "F", 1))
		cub->cmap->c_f = textrgbtoint(&(*line)[count], cub);
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
