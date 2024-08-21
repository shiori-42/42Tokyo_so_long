/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:51:47 by shiori            #+#    #+#             */
/*   Updated: 2024/08/21 13:40:04 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// first submission

#include "so_long.h"

void handle_error(t_info *game, char *msg, int num)
{
    if (msg)
    {
        ft_putstr_fd("Error\n", 2);
        ft_putstr_fd(msg, 2);
    }
    if (num)
    {
        free_resources(game);
    }
    exit(EXIT_FAILURE);
}

int	ft_exit(t_info *game)
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

void	winner(t_info *game)
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

int	setup_game(t_info *game, char *filename)
{
	ft_memset(game, 0, sizeof(t_info));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (1);
	if (check_file_name(filename))
		return (free_resources(game), 1);
	if (count_map_size(filename, game))
		return (free_resources(game), 1);
	game->map->map = (char **)malloc((game->map->height + 1) * sizeof(char *));
	if (!game->map->map)
		return (free_resources(game), 1);
	create_map(game, filename);
	game->window = mlx_new_window(game->mlx, game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE, "So Long");
	if (!game->window)
		return (free_resources(game), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	game;

	if (argc != 2)
		handle_error(NULL, "Usage: ./so_long <map.filename>\n", 0);
	if (setup_game(&game, argv[1]))
		handle_error(&game, "Failed to setup game\n", 1);
	init_game(&game);
	if (!is_valid_path(&game))
		handle_error(&game, "No valid path in map\n", 1);
	render_map(&game);
	mlx_hook(game.window, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.window, 17, 0, close_handler, &game);
	mlx_expose_hook(game.window, handle_expose, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q so_long");
// }