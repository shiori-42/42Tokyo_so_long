/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:11:50 by shiori            #+#    #+#             */
/*   Updated: 2024/08/22 16:05:32 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_data_until(char **data, int i)
{
	while (i > 0)
	{
		i--;
		free(data[i]);
	}
	free(data);
}

void	free_double_pointer(char **ptr, int height)
{
	int	y;

	if (!ptr)
		return ;
	y = 0;
	while (y < height)
	{
		if (ptr[y])
			free(ptr[y]);
		y++;
	}
	free(ptr);
}

void	free_images(t_game *game)
{
	if (game->images->image_wall)
		mlx_destroy_image(game->mlx_ptr, game->images->image_wall);
	if (game->images->image_empty)
		mlx_destroy_image(game->mlx_ptr, game->images->image_empty);
	if (game->images->image_player)
		mlx_destroy_image(game->mlx_ptr, game->images->image_player);
	if (game->images->image_items)
		mlx_destroy_image(game->mlx_ptr, game->images->image_items);
	if (game->images->image_exit)
		mlx_destroy_image(game->mlx_ptr, game->images->image_exit);
}

void	free_window_and_map(t_game *game)
{
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->map && game->map->data)
	{
		free_double_pointer(game->map->data, game->map->height);
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

void	free_resources(t_game *game)
{
	if (game)
	{
		free_images(game);
		free(game->images);
		free_window_and_map(game);
	}
}
