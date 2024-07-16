/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/07/16 21:32:58 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp((file_name + len - 4), ".ber", 4) != 0)
	{
		write(2, "Error\nWrong file extension\n", 28);
		exit(EXIT_FAILURE);
	}
}


int	cnt_map_size(char *filename, t_map *map)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error opening file\n", 19);
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
	printf("Map Size: %d x %d\n", map->x, map->y); // デバッグ
	return (0);
}

int	validate_map(t_map *map)
{
	int	player_cnt;
	int	exit_cnt;
	int	collected;
	int	x;
	int	y;

	player_cnt = 0;
	exit_cnt = 0;
	collected = 0;
	if (map == NULL || map->data == NULL)
	{
		fprintf(stderr, "Error: map or map->data is NULL\n");
		return (1);
	}
	y = 0;
	while (y < map->y)
	{
		if (map->data[y] == NULL)
		{
			fprintf(stderr, "Error: map->data[%d] is NULL\n", y);
			return (1);
		}
		x = 0;
		while (x < map->x)
		{
			if (map->data[y][x] == 'P')
				player_cnt++;
			else if (map->data[y][x] == 'E')
				exit_cnt++;
			else if (map->data[y][x] == 'C')
				collected++;
			else if (map->data[y][x] != '0' && map->data[y][x] != '1')
				return (1);
			x++;
		}
		y++;
	}
	printf("Player Count: %d, Exit Count: %d, Collected Count: %d\n",
		player_cnt, exit_cnt, collected); // デバッグ
	if (player_cnt != 1 || exit_cnt != 1 || collected < 1)
		return (1);
	return (0);
}

int	allocate_map_and_load(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	map->data = malloc(map->y * sizeof(char *));
	if (!map->data)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->data[i++] = line;
	}
	close(fd);
	// デバッグ
	for (i = 0; i < map->y; i++)
	{
		printf("Map Line %d: %s", i, map->data[i]);
	}
	return (0);
}
