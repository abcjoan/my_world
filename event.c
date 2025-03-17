/*
** EPITECH PROJECT, 2025
** event
** File description:
** event
*/
#include "my.h"

void if_click(game_t *game)
{
    sfVector2i mouse_pos;
    sfVector2i map_pos;

    if (game->event.type != sfEvtMouseButtonPressed)
        return;
    if (game->event.mouseButton.button != sfMouseLeft)
        return;
    if (game->state != STATE_GAME)
        return;
    mouse_pos = sfMouse_getPositionRenderWindow(game->window);
    map_pos = screen_to_map_coords(game, mouse_pos);
    if (map_pos.x >= 0 && map_pos.x < game->map->width &&
        map_pos.y >= 0 && map_pos.y < game->map->height) {
        apply_tool(game, map_pos.x, map_pos.y);
        printf("Applied tool at map position: %d, %d\n", map_pos.x, map_pos.y);
    }
}

void handle_game_mouse(game_t *game)
{
    float factor;

    if (game->event.type == sfEvtMouseButtonPressed) {
        printf("Mouse clicked at: %d, %d\n",
            game->event.mouseButton.x, game->event.mouseButton.y);
        if_click(game);
    } else if (game->event.type == sfEvtMouseWheelScrolled) {
        factor = (game->event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
        zoom_camera(game, factor);
    }
}

void handle_event(game_t *game)
{
    if (game->event.type == sfEvtClosed)
        sfRenderWindow_close(game->window);
    switch (game->state) {
        case STATE_MENU:
            handle_menu_event(game);
            break;
        case STATE_GAME:
            handle_game_mouse(game);
            handle_game_keys(game);
            break;
        case STATE_SETTINGS:
            break;
        case STATE_QUIT:
            break;
    }
}

void handle_game_keys_one(game_t *game)
{
    if (game->event.type != sfEvtKeyPressed)
        return;
    if (game->event.key.code == sfKeyUp)
        move_camera(game, (sfVector2f){0, -10});
    else if (game->event.key.code == sfKeyDown)
        move_camera(game, (sfVector2f){0, 10});
    if (game->event.key.code == sfKeyLeft)
        move_camera(game, (sfVector2f){-10, 0});
    if (game->event.key.code == sfKeyRight)
        move_camera(game, (sfVector2f){10, 0});
    if (game->event.key.code == sfKeyR)
        change_tool(game, TOOL_RAISE);
}

void handle_game_keys(game_t *game)
{
    handle_game_keys_one(game);
    if (game->event.key.code == sfKeyL)
        change_tool(game, TOOL_LOWER);
    if (game->event.key.code == sfKeyF)
        change_tool(game, TOOL_FLATTEN);
    if (game->event.key.code == sfKeyS)
        change_tool(game, TOOL_SMOOTH);
    if (game->event.key.code == sfKeyAdd || game->event.key.code == sfKeyEqual)
        adjust_brush_size(game, 1);
    if (game->event.key.code == sfKeySubtract
        || game->event.key.code == sfKeyDash)
        adjust_brush_size(game, -1);
}
