/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:34:08 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/23 17:56:28 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/
# define BLUE       "\033[0;94m"
# define RED        "\033[0;31m"

# define ERROR_ARGS			0
# define ERROR_FILE     	1
# define ERROR_MEM			2
# define ERROR_EMPTY		3
# define ERROR_MAP			4
# define ERROR_MLX			5

# define WIDTH			1024
# define HEIGHT			768
# define DEF_COLOR		0xf26e04	// Wall RGB color
# define WHITE			0xFFFFFF
# define PI				3.141592654
# define MAP_X_OFFSET	0			// Initial minimap x-position
# define MAP_Y_OFFSET	0			// Initial minimap y-position
# define INC_OFFSET		4			// Player movement pixels
# define WALL_SIZE		32			// Must be power of 2 (for the moment)
# define ROT_ANGLE_INC	6			// Must be multiple of 360

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "libft/includes/get_next_line.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/libft.h"
# include "mlx.h"
# include <fcntl.h>	// for open
# include <math.h>
# include "controls.h"
# include <stdio.h>	// for printf

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCTS
*/
typedef struct s_player
{
	int	x_pos;
	int	y_pos;
	int	angle;
}	t_player;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;	
}	t_point;

typedef struct s_line
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		color;
}	t_line;

typedef struct s_line_aux
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		error;	
}	t_line_aux;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_fdf
{
	void		*mlx;
	void		*mlx_win;
	char		*raw_map;
	int			x_elem;
	int			y_elem;
	t_point		*map;
	t_img		img;
	t_player	player;
}	t_fdf;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
void	ft_error_handler(int error);
void	free_split(char **str);
void	free_and_exit(int error, char *ptr);
void	free_split_and_exit(char **str, int error, char *ptr);
void	free_map_and_exit(t_fdf *fdf, int error, int flag);

void	mlx_put_pixel(t_fdf *fdf, int x, int y, int color);
void	draw_line(t_line line, t_fdf *fdf);
void	line_direction(t_line *line, t_line_aux *line_aux);
void	draw_square(t_fdf *fdf, t_point square, int size);
void	draw_rectangle(t_fdf *fdf, t_line diagonal);
void	draw_pointer(t_fdf *fdf);

int		key_pressed(int keycode, t_fdf *fdf);
int		close_window(t_fdf *fdf);

void	init_map(char *file, t_fdf *fdf);
void	init_win(t_fdf *fdf, char *s);
void	init_hooks(t_fdf *fdf);

char	*read_map(char *file, t_fdf *fdf);
void	check_map(t_fdf *fdf);
void	parse_map(t_fdf *fdf, char *line);

void	key_action_1(int keycode, t_fdf *fdf);
void	action_aux(t_fdf *fdf);

void	projection(t_fdf *fdf);

#endif