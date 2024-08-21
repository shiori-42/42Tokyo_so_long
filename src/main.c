/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:51:47 by shiori            #+#    #+#             */
/*   Updated: 2024/08/21 23:43:33 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_error(t_game *game, char *msg)
{
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
	}
	free_resources(game);
	exit(EXIT_FAILURE);
}

int	ft_exit(t_game *game)
{
	ft_printf("-----------------------------------------------\n");
	ft_printf("              Game Over :(                   \n");
	ft_printf("        You gave up on the mission.          \n");
	ft_printf("   Is the game too challenging for you?      \n");
	ft_printf("        Don't worry, you can try again!      \n");
	ft_printf("                                             \n");
	ft_printf("   Total moves made: %d                       \n",
		game->move_count);
	ft_printf("   Collectibles gathered: %d/%d                \n",
		game->collected, game->collectibles);
	ft_printf("-----------------------------------------------\n");
	free_resources(game);
	exit(EXIT_SUCCESS);
}

void	winner(t_game *game)
{
	ft_printf("-----------------------------------------------\n");
	ft_printf("    🎉🎉🎉  Congratulations!!!!  🎉🎉🎉     \n");
	ft_printf("    You found all collectibles and exit.     \n");
	ft_printf("        ✓✓✓✓✓✓✓✓ You won! ✓✓✓✓✓✓✓✓           \n");
	ft_printf("     Is %d moves the best you can do?         \n",
		game->move_count);
	ft_printf("-----------------------------------------------\n");
	free_resources(game);
	exit(EXIT_SUCCESS);
}

void	setup_game(t_game *game, char *filename)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		handle_error(game, "Failed to initialize mlx\n");
	game->images = malloc(sizeof(t_images));
	if (!game->images)
		handle_error(game, "Failed to allocate memory for images\n");
	ft_memset(game->images, 0, sizeof(t_images));
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		handle_error(game, "Failed to allocate memory for map\n");
	ft_memset(game->map, 0, sizeof(t_map));
	count_map_size(filename, game);
	create_map(game, filename);
	if (!game->map->data)
		handle_error(game, "Failed to allocate memory for map data\n");
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE, "So Long");
	if (!game->win_ptr)
		handle_error(game, "Failed to create a new window\n");
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		handle_error(NULL, "Usage: ./so_long <map_filename>\n");
	ft_memset(&game, 0, sizeof(t_game));
	check_file_name(argv[1]);
	setup_game(&game, argv[1]);
	init_game(&game);
	is_valid_path(&game);
	render_map(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_keypress, &game);
	mlx_loop(game.mlx_ptr);
	return (EXIT_SUCCESS);
}
