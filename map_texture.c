/*
** EPITECH PROJECT, 2025
** map_texture
** File description:
** Color-based terrain texturing
*/

#include "my.h"

static const terrain_color_t TERRAIN_COLORS[] = {
    {-100.0f, 0.1f, {65, 105, 225, 255}},
    {0.1f, 2.0f, {34, 139, 34, 255}},
    {2.0f, 4.0f, {139, 137, 137, 255}},
    {4.0f, 10.0f, {255, 250, 250, 255}}
};

sfColor get_terrain_color(float height)
{
    for (int i = 0; i < NUM_TERRAIN_COLORS; i++) {
        if (height >= TERRAIN_COLORS[i].min_height &&
            height <= TERRAIN_COLORS[i].max_height) {
            return TERRAIN_COLORS[i].color;
        }
    }
    return sfWhite;
}

void draw_colored_quad(map_t *map, int x, int y)
{
    sfVertex vertices[4];

    vertices[0].position = to_isometric(x, y, map->heightmap[y][x]);
    vertices[0].color = get_terrain_color(map->heightmap[y][x]);
    vertices[1].position = to_isometric(x + 1, y, map->heightmap[y][x + 1]);
    vertices[1].color = get_terrain_color(map->heightmap[y][x + 1]);
    vertices[2].position = to_isometric(x + 1, y + 1,
        map->heightmap[y + 1][x + 1]);
    vertices[2].color = get_terrain_color(map->heightmap[y + 1][x + 1]);
    vertices[3].position = to_isometric(x, y + 1, map->heightmap[y + 1][x]);
    vertices[3].color = get_terrain_color(map->heightmap[y + 1][x]);
    sfVertexArray_append(map->vertices, vertices[0]);
    sfVertexArray_append(map->vertices, vertices[1]);
    sfVertexArray_append(map->vertices, vertices[2]);
    sfVertexArray_append(map->vertices, vertices[3]);
}

void modify_map_init(map_t *map)
{
    float height;

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            height = sinf((float)x / 3.0f) *
                cosf((float)y / 3.0f) * 3.0f;
            map->heightmap[y][x] = height;
        }
    }
}
