/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syonekur <syonekur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/08/22 16:02:51 by syonekur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len <= ft_strlen(MAP_EXTENSION) || ft_strncmp(file_name + len
			- ft_strlen(MAP_EXTENSION), MAP_EXTENSION,
			ft_strlen(MAP_EXTENSION)) != 0)
		handle_error(NULL, "Wrong file extension\n");
}

void	count_map_size(char *filename, t_game *game)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(game, "Failed to open file\n");
	game->map->width = 0;
	game->map->height = 0;
	while (1)
	{
		line = get_next_line_trimmed(fd);
		if (!line)
			break ;
		game->map->height++;
		if (game->map->height == 1)
			game->map->width = ft_strlen(line);
		free(line);
	}
	close(fd);
}

int	validate_and_store_map(t_game *game, char *line, int *i)
{
	int	len;

	len = ft_strlen(line);
	if (len != game->map->width)
	{
		free(line);
		free_map_data_until(game->map->data, *i);
		game->map->data = NULL;
		return (1);
	}
	game->map->data[*i] = ft_strdup(line);
	free(line);
	(*i)++;
	if (*i == game->map->height)
		check_map_borders_and_contents(game);
	return (0);
}

char	*get_next_line_trimmed(int fd)
{
	char	*line;
	char	*newline_pos;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
	}
	newline_pos = ft_strchr(line, '\r');
	if (newline_pos)
	{
		*newline_pos = '\0';
	}
	return (line);
}

void	create_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		i;
	int		is_invalid;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(game, "Failed to open file\n");
	is_invalid = 0;
	i = 0;
	while (1)
	{
		line = get_next_line_trimmed(fd);
		if (!line)
			break ;
		if (is_invalid)
			free(line);
		else
			is_invalid = validate_and_store_map(game, line, &i);
	}
	if (is_invalid)
		handle_error(game, "Failed map is not rectangular\n");
	close(fd);
}
