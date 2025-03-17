/*
** EPITECH PROJECT, 2025
** map
** File description:
** map handling
*/
#include "my.h"

float **alloc_heightmap(int width, int height)
{
    float **heightmap = malloc(sizeof(float *) * height);

    if (!heightmap)
        return NULL;
    for (int i = 0; i < height; i++) {
        heightmap[i] = malloc(sizeof(float) * width);
        if (!heightmap[i]) {
            free_partial_heightmap(heightmap, i);
            return NULL;
        }
        for (int j = 0; j < width; j++)
            heightmap[i][j] = 0;
    }
    return heightmap;
}

void free_partial_heightmap(float **heightmap, int rows)
{
    for (int j = 0; j < rows; j++)
        free(heightmap[j]);
    free(heightmap);
}

map_t *create_map(int width, int height)
{
    map_t *map = malloc(sizeof(map_t));

    map->vertices = sfVertexArray_create();
    if (!map->vertices) {
        free(map);
        return NULL;
    }
    map->width = width;
    map->height = height;
    map->heightmap = alloc_heightmap(width, height);
    if (!map->heightmap) {
        sfVertexArray_destroy(map->vertices);
        free(map);
        return NULL;
    }
    map->texture = sfTexture_createFromFile("assets/texture.png", NULL);
    sfVertexArray_setPrimitiveType(map->vertices, sfQuads);
    modify_map_init(map);
    return map;
}

void destroy_map(map_t *map)
{
    if (!map)
        return;
    if (map->vertices)
        sfVertexArray_destroy(map->vertices);
    if (map->heightmap) {
        for (int i = 0; i < map->height; i++)
            free(map->heightmap[i]);
        free(map->heightmap);
    }
    if (map->texture)
        sfTexture_destroy(map->texture);
    free(map);
}

void draw_map(game_t *game)
{
    map_t *map = game->map;

    sfVertexArray_clear(map->vertices);
    for (int y = 0; y < map->height - 1; y++) {
        for (int x = 0; x < map->width - 1; x++) {
            draw_colored_quad(map, x, y);
        }
    }
    sfRenderWindow_drawVertexArray(game->window, map->vertices, NULL);
}
