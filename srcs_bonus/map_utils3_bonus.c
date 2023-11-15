/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:50:27 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/15 14:05:32 by cescanue         ###   ########.fr       */
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

void	checkrgbcolor(int color, t_cub *cub)
{
	if (color < 0 || color > 255)
	{
		ft_printf("\nError\nThe color value is not valid,");
		ft_printf(" it has to be between 0-255");
		ft_error_handler(ERROR_MAP_F, cub);
	}
}

void	check_rgb_extra(char *line, t_cub *cub)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			ft_error_handler(ERROR_COLOR_F, cub);
		line++;
	}
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
		while (*line && *line != '\n' && *line != '-'
			&& *line != '+' && (*line < '0' || *line > '9'))
		{
			if (*line == ',')
				count++;
			line++;
		}
		if (!*line || *line == '\n' || (color && count != 1))
			ft_error_handler(ERROR_COLOR_F, cub);
		rgb[color] = ft_atoi(line);
		checkrgbcolor(rgb[color++], cub);
		ttorgbcheckcoma(&line, cub);
	}
	check_rgb_extra(line, cub);
	return (((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]));
}
