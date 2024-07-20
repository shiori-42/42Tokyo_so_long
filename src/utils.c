/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:11:50 by shiori            #+#    #+#             */
/*   Updated: 2024/07/20 22:19:50 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_double_pointer(char **ptr, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		free(ptr[y]);
		y++;
	}
	free(ptr);
}

// void	free_resources(t_game *game)
// {
// 	if (game->img_wall)
// 		mlx_destroy_image(game->mlx_ptr, game->img_wall);
// 	if (game->img_empty)
// 		mlx_destroy_image(game->mlx_ptr, game->img_empty);
// 	if (game->img_player)
// 		mlx_destroy_image(game->mlx_ptr, game->img_player);
// 	if (game->img_collectible)
// 		mlx_destroy_image(game->mlx_ptr, game->img_collectible);
// 	if (game->img_exit)
// 		mlx_destroy_image(game->mlx_ptr, game->img_exit);
// 	if (game->win_ptr)
// 		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
// 	if (game->map->data)
// 		free_double_pointer(game->map->data, game->map->y);
// 	if (game->mlx_ptr)
// 	{
// 		mlx_destroy_display(game->mlx_ptr);
// 		free(game->mlx_ptr);
// 	}
// }

void	free_resources(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx_ptr, game->img_wall);
	if (game->img_empty)
		mlx_destroy_image(game->mlx_ptr, game->img_empty);
	if (game->img_player)
		mlx_destroy_image(game->mlx_ptr, game->img_player);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx_ptr, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx_ptr, game->img_exit);
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->map && game->map->data)
	{
		free_double_pointer(game->map->data, game->map->y);
		game->map->data = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	if (game->map)
	{
		free(game->map);
		game->map = NULL;
	}
}

// int	on_destroy(t_game *game)
// {
// 	free_resources(game);
// 	exit(0);
// 	return (0);
// }

int	on_destroy(t_game *game)
{
	mlx_loop_end(game->mlx_ptr);
	return (0);
}