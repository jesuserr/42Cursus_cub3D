/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:44:36 by cescanue          #+#    #+#             */
/*   Updated: 2023/11/20 20:56:38 by jesuserr         ###   ########.fr       */
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
	ft_memset(&cub->key, 0, sizeof(t_keys));
	cub->player.speed = INC_OFFSET;
	cub->aspect_ratio = ((float)WIDTH / (float)HEIGHT) * 0.75 * VERT_SCALE;
	calc_player_vector(cub);
}

void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->mlx_win, 17, 0, close_window, cub);
	mlx_hook(cub->mlx_win, 2, 0, key_pressed, cub);
	mlx_loop_hook(cub->mlx, ray_casting, cub);
	mlx_hook(cub->mlx_win, 3, 0, key_released, cub);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	ft_memset(&cub, 0, sizeof(t_cub));
	if (argc != 2)
		ft_error_handler(ERROR_ARGS, &cub);
	init_map(argv[1], &cub);
	init_win(&cub, argv[1]);
	init_struct(&cub);
	load_textures(&cub);
	ray_casting(&cub);
	init_hooks(&cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
