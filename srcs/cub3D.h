/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:32:37 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/20 19:45:53 by jesuserr         ###   ########.fr       */
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
# define ERROR_TXT			8

# define WIDTH			1200		// 42_iMac 2560x1440 full screen
# define HEIGHT			900
# define DEF_COLOR		0xf26e04	// Wall RGB color
# define WHITE			0xFFFFFF
# define PI				3.141592654
# define INC_OFFSET		4			// Player movement pixels,wall size multiple
# define WALL_SIZE		64			// Must be power of 2
# define ROT_ANGLE_INC	3			// Must be multiple of 360 and 90
# define ROT_ANG_MOUSE	1			// Must be multiple of 360 and 90
# define FOV			64			// Field of view (even number)
# define VERT_SCALE		1			// Modifies wall height in screen
# define DIST_TO_WALL	8			// Multiple of WALL_SIZE

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include "../minilibx_macos/mlx_error.h"
# include <fcntl.h>	// for open
# include <math.h>
# include "controls.h"
# include <stdio.h>	// for printf

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCTS
*/
typedef struct s_keys
{
	int		mouse_x;
	int		d_pressed;
	int		w_pressed;
	int		a_pressed;
	int		s_pressed;
	int		left_pressed;
	int		right_pressed;
	int		shift_pressed;
	int		info_on_screen;
	int		map_scale;
	int		map_x_offset;
}	t_keys;

typedef struct s_player
{
	int		x_pos;
	int		y_pos;
	int		angle;
	float	x_vector;
	float	y_vector;
	int		speed;
	int		offset_x;
	int		offset_y;
	int		orig_x_pos;
	int		orig_y_pos;
	int		orig_angle;
	int		size;
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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	void	*mlx;
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
	char	**mapa;
	int		x;
	int		y;
	int		xl;
}	t_parse;

typedef struct s_txt
{
	t_img	img;
	int		w;
	int		h;
	float	scale;
	float	offset;
}	t_txt;

typedef struct s_cub
{
	t_keys		key;
	void		*mlx;
	void		*mlx_win;
	char		*raw_map;
	int			x_elem;
	int			y_elem;
	int			mapconsistency;
	int			timer;
	float		aspect_ratio;
	t_point		*map;
	t_img		img;
	t_player	player;
	t_map		*cmap;
	t_txt		*textures[5];
	t_ray_cast	horz;
	t_ray_cast	vert;
}	t_cub;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
/*		errors.c		*/
void	ft_error_handler(int error, t_cub *cub);
int		close_window(t_cub *cub, int exitcode);
void	close_cmaps(t_cub *cub);
void	free_textures(t_cub *cub);
/*		graphics.c		*/
void	mlx_put_pixel(t_cub *cub, int x, int y, int color);
void	draw_vert_line(t_line line, t_cub *cub);
void	draw_floor_and_ceiling(t_cub *cub);
void	keys_info_on_screen(t_cub *cub);
/*		hooks.c				*/
int		key_pressed(int keycode, t_cub *cub);
int		key_released(int keycode, t_cub *cub);
void	reset_player(t_cub *cub);
/*		map_utils.c				*/
void	init_map(char *file, t_cub *cub);
/*		map_utils2.c				*/
void	read_text_colors(int fd, char **line, t_cub *cub);
/*		map_utils3.c				*/
int		textrgbtoint(char *line, t_cub *cub);
/*		map_utils_parse.c		*/
t_point	*parse_map(t_cub *cub);
/*		map_utils_check.c		*/
int		check_map(t_cub *cub);
/*		map_utils_check.c		*/
char	**str_to_array(int lx, int ly, char *smap, t_cub *cub);
/*		map_utils_check2.c		*/
void	check_limits(t_cub *cub);
/*		moves.c				*/
void	key_actions(t_cub *cub);
/*		ray_casting.c		*/
int		ray_casting(t_cub *cub);
/*		raycast_utils.c 		*/
void	init_ray_casters(t_cub *cub, t_ray_cast *ver, t_ray_cast *hor, float a);
double	degrees_to_radians(int angle_degrees, float inc_angle);
void	check_first_corner_exception(t_cub *cub, t_ray_cast *v, t_ray_cast *h);
void	calc_player_vector(t_cub *cub);
/*		wall_utils.c 		*/
void	draw_wall(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);
int		choose_texture(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz);
void	calc_line_height(t_line *line, t_cub *cub, t_txt *txt);
float	wall_height_and_color(t_line *line, t_cub *cub);
void	draw_texture(t_line line, t_cub *cub, t_txt *txt, float offset);
/*		txt_utils.c 		*/
t_txt	*load_txt(char *file, t_cub *cub);
void	load_textures(t_cub *cub);

#endif