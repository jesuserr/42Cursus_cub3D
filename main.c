/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:49:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/03 17:21:22 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_win(t_cub *cub, char *s)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_error_handler(ERROR_MLX, cub);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, s);
	if (!cub->mlx_win)
		ft_error_handler(ERROR_MLX, cub);
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img.img)
		ft_error_handler(ERROR_MLX, cub);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp, \
		&cub->img.len, &cub->img.endian);
}

void	init_struct(t_cub *cub)
{
/* Esto se puede borrar, ya que el memset se ocupa de inicialiar todo a 0, te lo dejo por si lo quieres para glo que no controlo
	cub->key.a_pressed = 0;
	cub->key.d_pressed = 0;
	cub->key.w_pressed = 0;
	cub->key.s_pressed = 0;
	cub->key.left_pressed = 0;
	cub->key.right_pressed = 0;
	cub->key.shift_pressed = 0;
	cub->key.mouse_x = 0;
	cub->key.map_on_screen = 0;
*/	
	ft_memset(&cub->key, 0, sizeof(t_keys));
	cub->player.speed = INC_OFFSET;
	cub->key.map_scale = (-cub->x_elem / 3) + 18;
	if (cub->key.map_scale < 5)
		cub->key.map_scale = 5;
	cub->key.map_x_offset = (WIDTH - cub->x_elem * cub->key.map_scale) / 2;
	calc_player_vector(cub);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		ft_error_handler(ERROR_ARGS, &cub);
	ft_memset(&cub, 0, sizeof(t_cub));
	init_map(argv[1], &cub);
	init_win(&cub, argv[1]);
	init_struct(&cub);
	ray_casting(&cub);
	mlx_hook(cub.mlx_win, 17, 0, close_window, &cub);
	mlx_hook(cub.mlx_win, 2, 0, key_pressed, &cub);
	mlx_loop_hook(cub.mlx, ray_casting, &cub);
	mlx_hook(cub.mlx_win, 3, 0, key_released, &cub);
	mlx_hook(cub.mlx_win, 6, 0, mouse_move, &cub);
	//mlx_loop(cub.mlx);
	close_window(&cub, EXIT_SUCCESS);
	return (0);
}
