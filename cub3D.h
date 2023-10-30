/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:49:33 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/30 20:30:26 by jesuserr         ###   ########.fr       */
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
# define ERROR_COLOR_F		6
# define ERROR_MAP_F		7

# define WIDTH			1024
# define HEIGHT			768
# define DEF_COLOR		0xf26e04	// Wall RGB color
# define WHITE			0xFFFFFF
# define PI				3.141592654
# define MAP_X_OFFSET	0			// Initial minimap x-position
# define MAP_Y_OFFSET	0			// Initial minimap y-position
# define INC_OFFSET		8			// Player movement pixels,wall size multiple
# define WALL_SIZE		64			// Must be power of 2
# define ROT_ANGLE_INC	6			// Must be multiple of 360, player rotation
# define FOV			66			// Field of view (even number)
# define VERT_SCALE		1			// Modifies wall height in screen

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

typedef struct s_ray_cast
{
	float	ray_x;
	float	ray_y;	
	int		depth_of_field;
	int		depth_of_field_max;	
	int		map_x;
	int		map_y;
	int		map_pos;
	float	arc_tan;
	float	tan;
	float	x_offset;
	float	y_offset;
	double	ray_angle;
	float	ray_length;	
}	t_ray_cast;

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

typedef struct s_map
{
	char		*t_no;
	char		*t_so;
	char		*t_ea;
	char		*t_we;
	int			c_f;
	int			c_c;
}	t_map;

typedef struct s_parse
{
	t_point	*map;
	int		x;
	int		y;
	int		xl;
}	t_parse;

typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;
	char		*raw_map;
	int			x_elem;
	int			y_elem;
	t_point		*map;
	t_img		img;
	t_player	player;
	t_map		*cmap;
}	t_cub;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
/*		errors.c		*/
void	ft_error_handler(int error);
void	free_split(char **str);
void	free_and_exit(int error, char *ptr);
void	free_split_and_exit(char **str, int error, char *ptr);
void	free_map_and_exit(t_cub *cub, int error, int flag);
/*		graphics.c		*/
void	mlx_put_pixel(t_cub *cub, int x, int y, int color);
void	draw_line(t_line line, t_cub *cub);
void	line_direction(t_line *line, t_line_aux *line_aux);
void	draw_pointer(t_cub *cub);
/*		graphics_2.c		*/
void	draw_square(t_cub *cub, t_point square, int size);
void	draw_rectangle(t_cub *cub, t_line diagonal);
/*		hooks.c				*/
int		key_pressed(int keycode, t_cub *cub);
int		close_window(t_cub *cub);
/*		map_utils.c				*/
void	init_map(char *file, t_cub *cub);
/*		map_utils2.c				*/
void	read_text_colors(int fd, char **line, t_cub *cub);
/*		map_utils_parse.c		*/
t_point	*parse_map(t_cub *cub);
/*		map_utils_check.c		*/
int		check_map(t_cub *cub);
/*		moves.c				*/
void	key_action_1(int keycode, t_cub *cub);
int		check_collision(int keycode, t_cub *cub);
void	action_aux(t_cub *cub);
/*		ray_casting.c		*/
void	ray_casting(t_cub *cub);
/*		raycast_utils.c 		*/
void	init_ray_casters(t_cub *cub, t_ray_cast *ver, t_ray_cast *hor, float a);
double	degrees_to_radians(int angle_degrees, float inc_angle);
void	draw_shorter_ray(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz);
void	check_first_corner_exception(t_cub *cub, t_ray_cast *v, t_ray_cast *h);
/*		wall_utils.c 		*/
void	draw_floor_and_ceiling(t_cub *cub);
void	rise_walls(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);

#endif