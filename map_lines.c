/*
** EPITECH PROJECT, 2025
** G-ING-200-MAR-2-1-myworld-joan.augier-billault
** File description:
** map_lines
*/
#include "my.h"


sfVector2f to_isometric(int x, int y, float height)
{
    sfVector2f pos;

    pos.x = (x - y) * (TILE_SIZE / 2);
    pos.y = (x + y) * (TILE_SIZE / 4) - height * 10;
    return pos;
}

void append_horizontal_line(map_t *map, int x, int y)
{
    sfVertex vertex;

    vertex.color = sfWhite;
    vertex.position = to_isometric(x, y, map->heightmap[y][x]);
    sfVertexArray_append(map->vertices, vertex);
    if (x < map->width - 1) {
        vertex.position = to_isometric(x + 1, y, map->heightmap[y][x + 1]);
        sfVertexArray_append(map->vertices, vertex);
    }
}

void append_vertical_line(map_t *map, int x, int y)
{
    sfVertex vertex;

    vertex.color = sfWhite;
    vertex.position = to_isometric(x, y, map->heightmap[y][x]);
    sfVertexArray_append(map->vertices, vertex);
    if (y < map->height - 1) {
        vertex.position = to_isometric(x, y + 1, map->heightmap[y + 1][x]);
        sfVertexArray_append(map->vertices, vertex);
    }
}
