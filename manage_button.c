/*
** EPITECH PROJECT, 2025
** manage_button
** File description:
** c
*/

#include "my.h"

void setup_button_params(button_params_t *dest, button_params_t *src)
{
    dest->position = src->position;
    dest->size = src->size;
    dest->text = src->text;
    dest->font = src->font;
}

button_t *create_button(sfVector2f position, sfVector2f size,
    char *text, sfFont *font)
{
    button_t *button;
    button_params_t params = {position, size, text, font};
    button_params_t local_params;

    button = alloc_button();
    if (!button)
        return NULL;
    setup_button_params(&local_params, &params);
    init_button_shape(button, local_params);
    init_button_text(button, local_params);
    return button;
}

void destroy_button(button_t *button)
{
    if (!button)
        return;
    if (button->shape)
        sfRectangleShape_destroy(button->shape);
    if (button->text)
        sfText_destroy(button->text);
    free(button);
}

void setup_menu_buttons(menu_t *menu)
{
    sfVector2f button_size = {300, 60};
    sfVector2f center_pos = {810, 400};

    menu->play_button = create_button(center_pos, button_size,
        "Play", menu->font);
    center_pos.y += 100;
    menu->settings_button = create_button(center_pos, button_size,
        "Settings", menu->font);
    center_pos.y += 100;
    menu->quit_button = create_button(center_pos, button_size,
        "Quit", menu->font);
}

void process_button_click(game_t *game, sfVector2i mouse_pos)
{
    if (is_button_clicked(game->menu->play_button, mouse_pos)) {
        game->state = STATE_GAME;
        printf("Play button clicked!\n");
        return;
    }
    if (is_button_clicked(game->menu->settings_button, mouse_pos)) {
        game->state = STATE_SETTINGS;
        printf("Settings button clicked!\n");
        return;
    }
    if (is_button_clicked(game->menu->quit_button, mouse_pos)) {
        game->state = STATE_QUIT;
        sfRenderWindow_close(game->window);
    }
}
