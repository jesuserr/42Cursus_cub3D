typedef struct mlx_img_list_s
{
	int						width;
	int						height;
	char					*buffer;
	struct mlx_img_list_s	*next;
}	mlx_img_list_t;

typedef struct	mlx_img_ctx_s
{
  mlx_img_list_t	*img;
  struct mlx_img_ctx_s	*next;
} mlx_img_ctx_t;

typedef struct	mlx_win_list_s
{
  void			*winid;
  mlx_img_ctx_t		*img_list;
  int			nb_flush;
  int			pixmgt;
  struct mlx_win_list_s	*next;
} mlx_win_list_t;

typedef struct		mlx_ptr_s
{
  void			*appid;
  mlx_win_list_t	*win_list;
  mlx_img_list_t	*img_list;
  void			(*loop_hook)(void *);
  void			*loop_hook_data;
  void			*loop_timer;
  mlx_img_list_t	*font;
  int			main_loop_active;
} mlx_ptr_t;
