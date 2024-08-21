/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:27:11 by shiori            #+#    #+#             */
/*   Updated: 2024/08/21 13:26:03 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len <= ft_strlen(MAP_EXTENSION) || ft_strncmp(file_name + len
			- ft_strlen(MAP_EXTENSION), MAP_EXTENSION,
			ft_strlen(MAP_EXTENSION)) != 0)
	{
		ft_putstr_fd("Error\nWrong file extension\n", 2);
		return (1);
	}
	return (0);
}

int	count_map_size(char *filename, t_game *game)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(game, "Failed to open file", 0);
	game->map->width = 0;
	game->map->height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			game->map->height++;
		if (game->map->height == 1)
			game->map->width = ft_strlen(line) - 1;
		free(line);
	}
	close(fd);
	return (0);
}

int	validate_and_store_map(t_game *game, char *line, int *i)
{
	int	len;

	len = ft_strlen(line);
	if (len != game->map->width)
	{	
		while  (*i>=0)
		{	
			free(game->map->map[*i]);		
			i--;	
		}	
		free(line);
		handle_error(game, "Failed map is not square\n", 1);
	}
	game->map->map[*i] = ft_strdup(line);
	(*i)++;
	if (*i == game->map->height)
		check_map_borders_and_contents(game);
	return (0);
}
char *get_next_line_trimmed(int fd)
{
    char *line = get_next_line(fd);
    if (!line)
        return NULL;

    char *newline_pos = ft_strchr(line, '\n');
    if (newline_pos)
    {
        *newline_pos = '\0';
    }
    return line;
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
		line = get_next_line_trimmed(fd);
		if (!line)
			break ;
		game->map->map[i + 1] = NULL;
		validate_and_store_map(game, line, &i);
		free(line);
	}
	close(fd);
	return (0);
}
