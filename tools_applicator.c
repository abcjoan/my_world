/*
** EPITECH PROJECT, 2025
** G-ING-200-MAR-2-1-myworld-joan.augier-billault
** File description:
** tools_applicator
*/

#include "my.h"

sfVector2i screen_to_map_coords(game_t *game, sfVector2i screen_pos)
{
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(
        game->window, screen_pos, game->camera);
    float x = (world_pos.x / (TILE_SIZE / 2) +
        world_pos.y / (TILE_SIZE / 4)) / 2;
    float y = (world_pos.y / (TILE_SIZE / 4) -
        world_pos.x / (TILE_SIZE / 2)) / 2;

    return (sfVector2i){(int)x, (int)y};
}

static void apply_single_point(map_t *map, const toolbar_t *toolbar,
    point_t target, point_t origin)
{
    float *height = &map->heightmap[target.y][target.x];
    float orig_height = map->heightmap[origin.y][origin.x];

    if (target.x < 0 || target.x >= map->width ||
        target.y < 0 || target.y >= map->height)
        return;
    switch (toolbar->current_tool) {
    case TOOL_RAISE:
        *height += toolbar->intensity;
        break;
    case TOOL_LOWER:
        *height -= toolbar->intensity;
        break;
    case TOOL_FLATTEN:
        *height = orig_height;
        break;
    case TOOL_SMOOTH:
        if (target.x != origin.x || target.y != origin.y)
            *height = (*height + orig_height) / 2;
    }
}

void adjust_brush_size(game_t *game, int delta)
{
    game->toolbar->brush_size += delta;
    if (game->toolbar->brush_size < 1)
        game->toolbar->brush_size = 1;
    if (game->toolbar->brush_size > 5)
        game->toolbar->brush_size = 5;
    printf("Brush size: %d\n", game->toolbar->brush_size);
}

void apply_tool(const game_t *game, int x, int y)
{
    toolbar_t *toolbar = game->toolbar;
    map_t *map = game->map;
    point_t target = {x, y};
    point_t origin = {x, y};

    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return;
    for (int dy = -toolbar->brush_size + 1; dy < toolbar->brush_size; dy++) {
        for (int dx = -toolbar->brush_size +
            1; dx < toolbar->brush_size; dx++) {
            apply_single_point(map, toolbar, target, origin);
        }
    }
}
