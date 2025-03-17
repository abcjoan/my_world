/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** main
*/

#include "my.h"

void destroy(game_t *game)
{
    if (game->menu)
        destroy_menu(game->menu);
    if (game->map)
        destroy_map(game->map);
    if (game->toolbar)
        destroy_toolbar(game->toolbar);
    if (game->camera)
        sfView_destroy(game->camera);
    if (game->window)
        sfRenderWindow_destroy(game->window);
}

void render_state(game_t *game)
{
    switch (game->state) {
        case STATE_MENU:
            sfRenderWindow_setView(game->window,
                sfRenderWindow_getDefaultView(game->window));
            draw_menu(game);
            break;
        case STATE_GAME:
            sfRenderWindow_setView(game->window, game->camera);
            draw_map(game);
            break;
        case STATE_SETTINGS:
            sfRenderWindow_setView(game->window,
                sfRenderWindow_getDefaultView(game->window));
            break;
        default:
            break;
    }
}

void loop_main(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    render_state(game);
    sfRenderWindow_display(game->window);
    sfRenderWindow_setFramerateLimit(game->window, 60);
    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        handle_event(game);
    }
}

int game_check(game_t *game)
{
    if (!game)
    return 84;
    game->window = create_renderwindow(1920, 1080, 64, "My World");
    if (!game->window) {
        free(game);
        return 84;
    }
    return 0;
}

int main(void)
{
    game_t *game = malloc(sizeof(game_t));

    game_check(game);
    init_game(game);
    if (!game->menu || !game->map || !game->toolbar || !game->camera) {
        destroy(game);
        free(game);
        return 84;
    }
    while (sfRenderWindow_isOpen(game->window)) {
        loop_main(game);
    }
    destroy(game);
    free(game);
    return 0;
}
