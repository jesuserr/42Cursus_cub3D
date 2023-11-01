/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:49:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/01 15:06:55 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_win(t_cub *cub, char *s)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		free_map_and_exit(cub, ERROR_MLX, 0);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, s);
	if (!cub->mlx_win)
		free_map_and_exit(cub, ERROR_MLX, 1);
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img.img)
		free_map_and_exit(cub, ERROR_MLX, 2);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp, \
		&cub->img.len, &cub->img.endian);
}

void	init_struct(t_cub *cub)
{
	cub->key.a_pressed = 0;
	cub->key.d_pressed = 0;
	cub->key.w_pressed = 0;
	cub->key.s_pressed = 0;
	cub->key.left_pressed = 0;
	cub->key.right_pressed = 0;
	cub->key.shift_pressed = 0;
	cub->player.speed = INC_OFFSET;
	calc_player_vector(cub);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		ft_error_handler(ERROR_ARGS);
	init_map(argv[1], &cub);
	init_win(&cub, argv[1]);
	init_struct(&cub);
	ray_casting(&cub);
	mlx_hook(cub.mlx_win, 17, 0, close_window, &cub);
	mlx_hook(cub.mlx_win, 2, 0, key_pressed, &cub);
	mlx_loop_hook(cub.mlx, ray_casting, &cub);
	mlx_hook(cub.mlx_win, 3, 0, key_released, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
