/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:32:37 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/20 20:30:05 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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

# define WIDTH			1200		// 42_iMac 2560x1440 full screen
# define HEIGHT			900
# define DEF_COLOR		0xf26e04	// Wall RGB color
# define DEF_DOOR		0x77AAFF	// Door tag
# define WHITE			0xFFFFFF
# define PI				3.141592654
# define INC_OFFSET		4			// Player movement pixels,wall size multiple
# define WALL_SIZE		64			// Must be power of 2
# define ROT_ANGLE_INC	3			// Must be multiple of 360 and 90
# define ROT_ANG_MOUSE	2			// Must be multiple of 360 and 90
# define FOV			64			// Field of view (even number)
# define VERT_SCALE		1			// Modifies wall height in screen
# define DIST_TO_WALL	8			// Multiple of WALL_SIZE
# define PLAYER_SIZE	10			// Player Size
# define PLAYER_ZOOM	1.5			// Portion of player's body shown
# define DOOR_DELAY		5000		// Door delay in ms

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include "../minilibx_macos/mlx_error.h"
# include <fcntl.h>				// for open
# include <math.h>
# include "controls_bonus.h"
# include <stdio.h>				// for printf
# include <sys/time.h>			// for timer

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
	float	zoom;
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
	int		door_hit;
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
	char	*t_no;
	char	*t_so;
	char	*t_ea;
	char	*t_we;
	char	*t_door;
	char	*cha_u;
	char	*cha_d;
	char	*cha_l;
	char	*cha_r;
	int		c_f;
	int		c_c;
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

typedef struct s_character
{
	t_list	**cu;
	t_list	**cd;
	t_list	**cl;
	t_list	**cr;
	t_txt	*current;
	int		timer;
}	t_character;

typedef struct s_doors
{
	int		map_pos;
	size_t	start_time;
}	t_doors;

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
	t_doors		doors[1000];
	t_point		*map;
	t_img		img;
	t_player	player;
	t_map		*cmap;
	t_txt		*textures[8];
	t_character	*cha;
	t_character	*cha1;
	t_character	*cha2;
	t_ray_cast	horz;
	t_ray_cast	vert;
}	t_cub;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                        FUNCTION PROTOTYPES
*/
/*		errors_bonus.c				*/
void	ft_error_handler(int error, t_cub *cub);
int		close_window(t_cub *cub, int exitcode);
void	close_cmaps(t_cub *cub);
void	free_textures(t_cub *cub);
/*		errors2_bonus.c				*/
void	free_characters(t_cub *cub);
/*		graphics_bonus.c			*/
void	mlx_put_pixel(t_cub *cub, int x, int y, int color);
void	draw_vert_line(t_line line, t_cub *cub);
void	draw_floor_and_ceiling(t_cub *cub);
void	draw_square(t_cub *cub, t_point square, int size);
void	on_screen_minimap(t_cub *cub);
/*		hooks_bonus.c				*/
int		mouse_move(int x, int y, t_cub *cub);
int		key_pressed(int keycode, t_cub *cub);
int		key_released(int keycode, t_cub *cub);
void	reset_player(t_cub *cub);
/*		map_utils_bonus.c			*/
void	init_map(char *file, t_cub *cub);
/*		map_utils2_bonus.c			*/
void	read_text_colors(int fd, char **line, t_cub *cub);
/*		map_utils3_bonus.c				*/
int		textrgbtoint(char *line, t_cub *cub);
/*		map_utils_parse_bonus.c		*/
t_point	*parse_map(t_cub *cub);
/*		map_utils_check_bonus.c		*/
int		check_map(t_cub *cub);
/*		map_utils_check_bonus.c		*/
char	**str_to_array(int lx, int ly, char *smap, t_cub *cub);
/*		map_utils_check2_bonus.c	*/
void	check_limits(t_cub *cub);
/*		moves_bonus.c				*/
void	key_actions(t_cub *cub);
/*		ray_casting_bonus.c			*/
int		ray_casting(t_cub *cub);
/*		raycast_utils_bonus.c 		*/
void	init_ray_casters(t_cub *cub, t_ray_cast *ver, t_ray_cast *hor, float a);
double	degrees_to_radians(int angle_degrees, float inc_angle);
void	check_first_corner_exception(t_cub *cub, t_ray_cast *v, t_ray_cast *h);
void	calc_player_vector(t_cub *cub);
float	wall_height_and_color(t_line *line, t_cub *cub);
/*		wall_utils_bonus.c 			*/
void	draw_wall(t_cub *cub, t_ray_cast *vert, t_ray_cast *horz, float x);
void	calc_line_height(t_line *line, t_cub *cub, t_txt *txt);
void	draw_texture(t_line line, t_cub *cub, t_txt *txt, float offset);
/*		txt_utils_bonus.c 			*/
t_txt	*load_txt(char *file, t_cub *cub);
void	load_textures(t_cub *cub);
/*		sprites_bonus.c 			*/
void	ft_loadimgs(char *path, t_list **lst, int scale, t_cub *cub);
t_txt	*move_sprite(t_list *lst, void *current);
/*		sprites2_bonus.c 			*/
t_txt	*scale_img(t_txt *img, int scale, t_cub *cub);
/*		character_bonus.c			*/
void	load_characters(t_cub *cub);
void	cha_hook(t_cub *cub);
void	cha_releasekey(t_cub *cub);
/*		doors_bonus.c				*/
void	init_doors(t_cub *cub);
void	detect_door(t_cub *cub);
void	assign_start_time(t_cub *cub, int pos);
long	get_time_ms(void);
void	scan_doors(t_cub *cub);

#endif