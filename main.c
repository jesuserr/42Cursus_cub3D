/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/10/23 11:37:28 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map(char *file, t_fdf *fdf)
{
	ft_printf ("%s", BLUE);
	fdf->raw_map = read_map(file, fdf);
	ft_printf ("\n\n");
	check_map(fdf);
}

void	init_win(t_fdf *fdf, char *s)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		free_map_and_exit(fdf, ERROR_MLX, 0);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, s);
	if (!fdf->mlx_win)
		free_map_and_exit(fdf, ERROR_MLX, 1);
	fdf->img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img.img)
		free_map_and_exit(fdf, ERROR_MLX, 2);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, \
		&fdf->img.len, &fdf->img.endian);
}

void	init_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_win, 17, 0, close_window, fdf);
	mlx_hook(fdf->mlx_win, 2, 0, key_pressed, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;	

	if (argc != 2)
		ft_error_handler(ERROR_ARGS);
	init_map(argv[1], &fdf);
	init_win(&fdf, argv[1]);
	projection(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, fdf.img.img, 0, 0);
	init_hooks(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
