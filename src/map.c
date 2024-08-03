/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/08/03 18:29:06 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp((file_name + len - 4), ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\nWrong file extension\n", 2);
		return (1);
	}
	return (0);
}

int	cnt_map_size(char *filename, t_game *game)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nFailed to open file\n", 2);
		return (1);
	}
	game->map->x = 0;
	game->map->y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			game->map->y++;
		if (game->map->y == 1)
			game->map->x = ft_strlen(line) - 1;
		free(line);
	}
	close(fd);
	return (0);
}

int	create_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(game, "Failed to open file\n", 1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (validate_and_store_map(game, line, &i))
			handle_error(game, "Failed map is not square\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

int	check_map_borders_and_contents(t_map *map)
{
	int	player_cnt;
	int	exit_cnt;
	int	collected;

	player_cnt = 0;
	exit_cnt = 0;
	collected = 0;
	if (map == NULL || map->data == NULL)
	{
		ft_putstr_fd("Error\nMap or map data is NULL\n", 2);
		return (1);
	}
	if (check_map_borders(map) || check_map_contents(map, &player_cnt,
			&exit_cnt, &collected))
		return (1);
	if (player_cnt != 1 || exit_cnt != 1 || collected < 1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Invalid number of players, exits, or collectibles\n", 2);
		return (1);
	}
	return (0);
}
