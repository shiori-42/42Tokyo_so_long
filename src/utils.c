/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:11:50 by shiori            #+#    #+#             */
/*   Updated: 2024/08/04 17:40:43 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_double_pointer(char **ptr, int height)
{
	int	y;

	if (!ptr)
		return ;
	y = 0;
	while (y < height)
	{
		free(ptr[y]);
		y++;
	}
	free(ptr);
}

void	free_images(t_game *game)
{
	if (game->image_wall)
		mlx_destroy_image(game->mlx_ptr, game->image_wall);
	if (game->image_empty)
		mlx_destroy_image(game->mlx_ptr, game->image_empty);
	if (game->image_player)
		mlx_destroy_image(game->mlx_ptr, game->image_player);
	if (game->image_collectible)
		mlx_destroy_image(game->mlx_ptr, game->image_collectible);
	if (game->image_exit)
		mlx_destroy_image(game->mlx_ptr, game->image_exit);
}

void	free_map_window_display(t_game *game)
{
	if (game->map && game->map->data)
	{
		free_double_pointer(game->map->data, game->map->y);
		game->map->data = NULL;
	}
	if (game->map)
	{
		free(game->map);
		game->map = NULL;
	}
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
}

void	free_resources(t_game *game)
{
	free_images(game);
	free_map_window_display(game);
}
