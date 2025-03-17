/*
** EPITECH PROJECT, 2025
** toolbar
** File description:
** toolbar handling
*/

#include "my.h"

toolbar_t *create_toolbar(void)
{
    toolbar_t *toolbar = malloc(sizeof(toolbar_t));

    if (!toolbar)
        return NULL;
    toolbar->current_tool = TOOL_RAISE;
    toolbar->brush_size = 1;
    toolbar->intensity = 1.0f;
    return toolbar;
}

void destroy_toolbar(toolbar_t *toolbar)
{
    if (!toolbar)
        return;
    free(toolbar);
}

void move_camera(game_t *game, sfVector2f direction)
{
    game->camera_position.x += direction.x;
    game->camera_position.y += direction.y;
    sfView_setCenter(game->camera, (sfVector2f){
        (MAP_WIDTH * TILE_SIZE) / 2.0f + game->camera_position.x,
        (MAP_HEIGHT * TILE_SIZE) / 4.0f + game->camera_position.y});
}

void zoom_camera(game_t *game, float factor)
{
    game->zoom_level *= factor;
    if (game->zoom_level < 0.5f)
        game->zoom_level = 0.5f;
    if (game->zoom_level > 2.0f)
        game->zoom_level = 2.0f;
    sfView_setSize(game->camera, (sfVector2f){
        1920 * game->zoom_level, 1080 * game->zoom_level});
}

void change_tool(game_t *game, tool_type_t tool)
{
    game->toolbar->current_tool = tool;
    printf("Tool changed to: %d\n", tool);
}
