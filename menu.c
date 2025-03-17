/*
** EPITECH PROJECT, 2025
** menu
** File description:
** menu handling
*/
#include "my.h"

static void setup_menu_background(menu_t *menu)
{
    menu->background = sfRectangleShape_create();
    sfRectangleShape_setSize(menu->background, (sfVector2f){1920, 1080});
    sfRectangleShape_setFillColor(menu->background,
        sfColor_fromRGB(50, 50, 50));
}

static void setup_menu_title(menu_t *menu)
{
    menu->title = sfText_create();
    sfText_setFont(menu->title, menu->font);
    sfText_setString(menu->title, "My World");
    sfText_setCharacterSize(menu->title, 72);
    sfText_setFillColor(menu->title, sfWhite);
    sfText_setPosition(menu->title, (sfVector2f){760, 200});
}

menu_t *create_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    menu->font = sfFont_createFromFile("assets/fonts/Barlow-Black.ttf");
    if (!menu->font) {
        free(menu);
        return NULL;
    }
    setup_menu_background(menu);
    setup_menu_title(menu);
    setup_menu_buttons(menu);
    return menu;
}

void destroy_menu(menu_t *menu)
{
    if (!menu)
        return;
    if (menu->background)
        sfRectangleShape_destroy(menu->background);
    if (menu->title)
        sfText_destroy(menu->title);
    if (menu->font)
        sfFont_destroy(menu->font);
    if (menu->play_button)
        destroy_button(menu->play_button);
    if (menu->settings_button)
        destroy_button(menu->settings_button);
    if (menu->quit_button)
        destroy_button(menu->quit_button);
    free(menu);
}

void draw_menu(game_t *game)
{
    sfRenderWindow_drawRectangleShape(game->window,
        game->menu->background, NULL);
    sfRenderWindow_drawText(game->window, game->menu->title, NULL);
    draw_button(game->window, game->menu->play_button);
    draw_button(game->window, game->menu->settings_button);
    draw_button(game->window, game->menu->quit_button);
}

void handle_menu_event(game_t *game)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(game->window);

    is_button_hovered(game->menu->play_button, mouse_pos);
    is_button_hovered(game->menu->settings_button, mouse_pos);
    is_button_hovered(game->menu->quit_button, mouse_pos);
    if (game->event.type == sfEvtMouseButtonPressed &&
        game->event.mouseButton.button == sfMouseLeft) {
        process_button_click(game, mouse_pos);
    }
}
