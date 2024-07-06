#ifndef MAP_H
#define MAP_H

typedef struct s_map {
    int width;
    int height;
    char **data;
} t_map;

int load_map(const char *filename, t_map *map);
int validate_map(t_map *map);

#endif
