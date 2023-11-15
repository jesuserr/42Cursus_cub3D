/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:44:56 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/15 10:02:38 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

void	read_text_colors3(char **line, int count, t_cub *cub)
{
	ft_printf("\nError\nUnexpected key or double key");
	ft_printf(" %s", &(*line)[count]);
	ft_error_handler(ERROR_MAP_F, cub);
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
	else if (!cub->cmap->t_door && !ft_strncmp(&(*line)[count], "DO ", 3))
		cub->cmap->t_door = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->cha_u && !ft_strncmp(&(*line)[count], "CU ", 3))
		cub->cmap->cha_u = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->cha_d && !ft_strncmp(&(*line)[count], "CD ", 3))
		cub->cmap->cha_d = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->cha_l && !ft_strncmp(&(*line)[count], "CL ", 3))
		cub->cmap->cha_l = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->cha_r && !ft_strncmp(&(*line)[count], "CR ", 3))
		cub->cmap->cha_r = get_text(&(*line)[count + 2], cub);
	else if (!cub->cmap->c_c && !ft_strncmp(&(*line)[count], "C ", 2))
		cub->cmap->c_c = textrgbtoint(&(*line)[count], cub);
	else if (!cub->cmap->c_f && !ft_strncmp(&(*line)[count], "F ", 2))
		cub->cmap->c_f = textrgbtoint(&(*line)[count], cub);
	else if (**line != '\n' && ft_strncmp(&(*line)[count], "1", 1))
		read_text_colors3(line, count, cub);
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
