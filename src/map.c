/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/07/15 23:16:26 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_file_name(const char *file_name)
{
	size_t	len;

	len = ft_strlen((char *)file_name);
	if (len < 4 || ft_strncmp((char *)(file_name + len - 4), ".ber", 4) != 0)
	{
		write(2, "Error\nWrong file extension\n", 28);
		exit(EXIT_FAILURE);
	}
}

int	cnt_map_size(const char *filename, t_game *map)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	map->x = 0;
	map->y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != '\n')
			map->y++;
		if (map->y == 1)
			map->x = ft_strlen(line) - 1;
		free(line);
	}
	close(fd);
}

int	allocate_map_and_load(&game->map)
{
	int	i;

	map->data = malloc(map->y * sizeof(char *));
	if (!map->data)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
		map->data[i++] = line;
	close(fd);
	return (0);
}

int	validate_map(t_map *map)
{
	int	player_cnt;
	int	exit_cnt;
	int	collected;

	player_cnt = 0;
	exit_cnt = 0;
	collected = 0;
	for (int y = 0; y < map->y; y++)
	{
		for (int x = 0; x < map->x; x++)
		{
			if (map->data[y][x] == 'P')
				player_cnt++;
			else if (map->data[y][x] == 'E')
				exit_cnt++;
			else if (map->data[y][x] == 'C')
				collected++;
			else if (map->data[y][x] != '0' && map->data[y][x] != '1')
				return (1);
		}
	}
	printf("Player count: %d\n", player_cnt);   // デバッグ用メッセージ
	printf("Exit count: %d\n", exit_cnt);       // デバッグ用メッセージ
	printf("Collected count: %d\n", collected); // デバッグ用メッセージ
	if (player_cnt != 1)
		return (1);
	if (exit_cnt != 1)
		return (1);
	if (collected < 1)
		return (1);
	return (0);
}
