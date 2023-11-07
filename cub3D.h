/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/07 15:45:45 by cescanue         ###   ########.fr       */
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
# define ERROR_SPRITE		9

# define WIDTH			1024
# define HEIGHT			768
# define DEF_COLOR		0xf26e04	// Wall RGB color
# define WHITE			0xFFFFFF
# define PI				3.141592654
# define INC_OFFSET		4			// Player movement pixels,wall size multiple
# define WALL_SIZE		64			// Must be power of 2
# define ROT_ANGLE_INC	3			// Must be multiple of 360 and 90
# define ROT_ANG_MOUSE	1			// Must be multiple of 360 and 90
# define FOV			66			// Field of view (even number)
# define VERT_SCALE		1			// Modifies wall height in screen
# define DIST_TO_WALL	4			// Multiple of WALL_SIZE

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "libft/includes/get_next_line.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/libft.h"
# include "mlx.h"
# include "minilibx_macos/mlx_error.h"
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
	int		map_on_screen;
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
	void	*mlx;
}	t_img;

typedef struct s_map
{
	char		*t_no;
	char		*t_so;
	char		*t_ea;
	char		*t_we;
	char		*s_enemy;
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
}	t_txt;

typedef struct s_enemy
{
	t_list	**sprites;
	t_txt	*current;
}	t_enemy;


typedef struct s_cub
{
	t_keys		key;
	void		*mlx;
	void		*mlx_win;
	char		*raw_map;
	int			x_elem;
	int			y_elem;
	int			mapconsistency;
	t_point		*map;
	t_img		img;
	t_player	player;
	t_map		*cmap;
	t_txt		*txt_so;
	t_txt		*txt_no;
	t_txt		*txt_we;
	t_txt		*txt_ea;
	t_enemy		*enemy;
}	t_cub;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
/*		errors.c		*/
void	ft_error_handler(int error, t_cub *cub);
int		close_window(t_cub *cub, int exitcode);
void	close_cmaps(t_cub *cub);
void	free_sprites(t_cub *cub);
void	free_textures(t_cub *cub);
/*		graphics.c		*/
void	mlx_put_pixel(t_cub *cub, int x, int y, int color);
void	draw_line(t_line line, t_cub *cub);
void	line_direction(t_line *line, t_line_aux *line_aux);
void	draw_pointer(t_cub *cub);
void	draw_vert_line(t_line line, t_cub *cub);
/*		graphics_2.c		*/
void	draw_square(t_cub *cub, t_point square, int size);
void	draw_rectangle(t_cub *cub, t_line diagonal);
void	on_screen_minimap(t_cub *cub);
/*		hooks.c				*/
int		mouse_move(int x, int y, t_cub *cub);
int		key_pressed(int keycode, t_cub *cub);
int		key_released(int keycode, t_cub *cub);
/*		map_utils.c				*/
void	init_map(char *file, t_cub *cub);
/*		map_utils2.c				*/
void	read_text_colors(int fd, char **line, t_cub *cub);
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
void	draw_shorter_ray(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz);
void	check_first_corner_exception(t_cub *cub, t_ray_cast *v, t_ray_cast *h);
void	calc_player_vector(t_cub *cub);
/*		wall_utils.c 		*/
void	draw_floor_and_ceiling(t_cub *cub);
void	rise_walls(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);
void	draw_texture(t_cub *cub, t_txt *txt, int x, int y);
void	hexdump(const void *data, size_t length);
/*		txt_utils.c 		*/
t_txt	*load_txt(char *file, t_cub *cub);
void	load_textures(t_cub *cub);
/*		sprites.c 		*/
void	loading_sprites(t_cub *cub);
#endif