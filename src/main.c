/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:51:47 by shiori            #+#    #+#             */
/*   Updated: 2024/07/21 22:48:09 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_error(t_game *game, char *str, int num)
{
	if (num)
	{
		free_resources(game);
	}
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	ft_exit(t_game *game)
{
	ft_printf("-----------------------------------------------\n");
	ft_printf("|              Game Over :(                   |\n");
	ft_printf("|        You gave up on the mission.          |\n");
	ft_printf("|   Is the game too challenging for you?      |\n");
	ft_printf("|        Don't worry, you can try again!      |\n");
	ft_printf("|                                             |\n");
	ft_printf("|   Total moves made: %d                       |\n",
		game->move_cnt);
	ft_printf("|   Collectibles gathered: %d/%d                |\n",
		game->collected, game->collectibles);
	ft_printf("-----------------------------------------------\n");
	free_resources(game);
	exit(EXIT_SUCCESS);
}

void	winner(t_game *game)
{
	ft_printf("-----------------------------------------------\n");
	ft_printf("|    🎉🎉🎉  Congratulations!!!!!  🎉🎉🎉     |\n");
	ft_printf("|    You found all collectibles and exit.     |\n");
	ft_printf("|        ✓✓✓✓✓✓✓✓ You won! ✓✓✓✓✓✓✓✓           |\n");
	ft_printf("|     Is %d moves the best you can do?         |\n",
		game->move_cnt);
	ft_printf("-----------------------------------------------\n");
	free_resources(game);
	exit(EXIT_SUCCESS);
}

int	setup_game(t_game *game, char *filename)
{
	ft_memset(game, 0, sizeof(t_game));
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (1);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (free(game->map), 1);
	if (cnt_map_size(filename, game, game->map) || !check_file_name(filename))
		return (free_resources(game), 1);
	game->map->data = ft_calloc(game->map->y + 1, sizeof(char *));
	if (!game->map->data || create_map(game, filename, game->map))
		return (free_resources(game), 1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->window_width,
			game->window_height, "So Long");
	if (!game->win_ptr)
		return (free_resources(game), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		handle_error(NULL, "Usage: ./so_long <filename>\n", 0);
	if (setup_game(&game, argv[1]))
		handle_error(&game, "Failed to setup game\n", 1);
	init_game(&game, game.map);
	if (!check_current_path(&game))
		handle_error(&game, "No valid path in map\n", 1);
	render_map(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, 1L << 17, on_destroy, &game);
	mlx_loop(game.mlx_ptr);
	free_resources(&game);
	return (EXIT_SUCCESS);
}
