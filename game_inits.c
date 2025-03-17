/*
** EPITECH PROJECT, 2025
** G-ING-200-MAR-2-1-myworld-joan.augier-billault
** File description:
** game_inits
*/

#include "my.h"

sfRenderWindow *create_renderwindow(unsigned int x, unsigned int y,
    unsigned int bpp, char *title)
{
    sfVideoMode video_mode = {x, y, bpp};

    return sfRenderWindow_create(video_mode, title, sfResize | sfClose, NULL);
}

void init_camera_view(game_t *game)
{
    sfView_setSize(game->camera, (sfVector2f){1920, 1080});
    sfView_setCenter(game->camera, (sfVector2f){
        (MAP_WIDTH * TILE_SIZE) / 2.0f, (MAP_HEIGHT * TILE_SIZE) / 4.0f});
    game->camera_position = (sfVector2f){0, 0};
    game->zoom_level = 1.0f;
    game->rotation_angle = 0.0f;
}

int init_game_map_menu(game_t *game)
{
    game->menu = create_menu();
    if (!game->menu)
        return 0;
    game->map = create_map(MAP_WIDTH, MAP_HEIGHT);
    if (!game->map) {
        destroy_menu(game->menu);
        return 0;
    }
    return 0;
}

int init_game_components(game_t *game)
{
    init_game_map_menu(game);
    game->toolbar = create_toolbar();
    if (!game->toolbar) {
        destroy_map(game->map);
        destroy_menu(game->menu);
        return 0;
    }
    game->camera = sfView_create();
    if (!game->camera) {
        destroy_toolbar(game->toolbar);
        destroy_map(game->map);
        destroy_menu(game->menu);
        return 0;
    }
    return 1;
}

void init_game(game_t *game)
{
    game->state = STATE_MENU;
    if (!init_game_components(game))
        return;
    init_camera_view(game);
}
