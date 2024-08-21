/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:11:50 by shiori            #+#    #+#             */
/*   Updated: 2024/08/21 13:26:03 by shiori           ###   ########.fr       */
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

void	free_images(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->tile)
		mlx_destroy_image(game->mlx, game->tile);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->item)
		mlx_destroy_image(game->mlx, game->item);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
}

void	free_window_and_map(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	if (game->window)
	{
		mlx_destroy_window(game->mlx, game->window);
		game->window = NULL;
	}
	if (game->map && game->map->map)
	{
		printf("here\n");
		free_double_pointer(game->map->map, game->map->height);
		printf("end\n");
		game->map->map = NULL;
	}
	if (game->map)
	{
		free(game->map);
		game->map = NULL;
	}
}

void	free_resources(t_game *game)
{
	free_images(game);
	free_window_and_map(game);
}

void	free_map_data(char **data, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (data[i])
			free(data[i]);
		i++;
	}
	free(data);
}


