/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:51:47 by shiori            #+#    #+#             */
/*   Updated: 2024/07/15 20:23:53 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	t_game	game;

	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		return (1);
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "So Long");
	if (!game.win_ptr)
		return (free(game.mlx_ptr), 1);
	game.map = read_map("maps/map1.ber");
	if (!game.map.data || validate_map(&game.map) != 0)
	{
		write(2, "Error: invalid map\n", 19);
		return (1);
	}
	game.window_width = 800;
	game.window_height = 600;
	if (game.win_ptr == NULL)
		init_game(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, 1L << 17, on_destroy, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
