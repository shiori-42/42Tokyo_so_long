/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:51:47 by shiori            #+#    #+#             */
/*   Updated: 2024/07/16 20:01:47 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <string.h>

void	handle_error(t_game *game, char *str, int num)
{
	if (num)
	{
		free_resources(game);
	}
	ft_putstr_fd(str, 2);
	exit(1);
}

int	ft_exit(t_game *game)
{
	free_resources(game);
	write(1, "GAME OVER :(\n", 13);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc < 2)
	{
		write(2, "Usage: ./so_long <filename>\n", 28);
		return (EXIT_FAILURE);
	}
	check_file_name(argv[1]);
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
	{
		write(2, "Error: MLX initialization failed\n", 32);
		return (EXIT_FAILURE);
	}
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "So Long");
	if (!game.win_ptr)
	{
		write(2, "Error: Window creation failed\n", 31);
		free(game.mlx_ptr);
		return (EXIT_FAILURE);
	}
	if (cnt_map_size(argv[1], &game.map) || allocate_map_and_load(argv[1],
			&game.map))
	{
		write(2, "Error: Map processing failed\n", 30);
		free_resources(&game);
		return (EXIT_FAILURE);
	}
	if (validate_map(&game.map))
	{
		write(2, "Error: Invalid map\n", 19);
		free_resources(&game);
		return (EXIT_FAILURE);
	}
	init_game(&game);
	check_current_path(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, 1L << 17, on_destroy, &game);
	mlx_loop(game.mlx_ptr);
	return (EXIT_SUCCESS);
}
