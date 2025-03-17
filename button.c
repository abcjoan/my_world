/*
** EPITECH PROJECT, 2025
** button
** File description:
** button handling
*/

#include "my.h"

void draw_button(sfRenderWindow *window, button_t *button)
{
    sfColor fill_color;

    if (button->is_hovered)
        fill_color = sfColor_fromRGB(235, 150, 24);
    else
        fill_color = sfColor_fromRGB(100, 100, 100);
    sfRectangleShape_setFillColor(button->shape, fill_color);
    sfRenderWindow_drawRectangleShape(window, button->shape, NULL);
    sfRenderWindow_drawText(window, button->text, NULL);
}

int is_button_hovered(button_t *button, sfVector2i mouse_pos)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(button->shape);

    if (mouse_pos.x >= bounds.left &&
        mouse_pos.x <= bounds.left + bounds.width &&
        mouse_pos.y >= bounds.top &&
        mouse_pos.y <= bounds.top + bounds.height) {
        button->is_hovered = 1;
        return 1;
    }
    button->is_hovered = 0;
    return 0;
}

int is_button_clicked(button_t *button, sfVector2i mouse_pos)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(button->shape);

    if (mouse_pos.x >= bounds.left &&
        mouse_pos.x <= bounds.left + bounds.width &&
        mouse_pos.y >= bounds.top &&
        mouse_pos.y <= bounds.top + bounds.height) {
        return 1;
    }
    return 0;
}

void init_button_shape(button_t *button, button_params_t params)
{
    sfRectangleShape_setPosition(button->shape, params.position);
    sfRectangleShape_setSize(button->shape, params.size);
    sfRectangleShape_setFillColor(button->shape,
        sfColor_fromRGB(100, 100, 100));
    sfRectangleShape_setOutlineThickness(button->shape, 2);
    sfRectangleShape_setOutlineColor(button->shape, sfBlack);
}

void init_button_text(button_t *button, button_params_t params)
{
    sfFloatRect text_rect;
    sfVector2f text_pos;

    sfText_setFont(button->text, params.font);
    sfText_setString(button->text, params.text);
    sfText_setCharacterSize(button->text, 24);
    sfText_setFillColor(button->text, sfWhite);
    text_rect = sfText_getLocalBounds(button->text);
    text_pos.x = params.position.x + (params.size.x - text_rect.width) / 2;
    text_pos.y = params.position.y +
        (params.size.y - text_rect.height) / 2 - 10;
    sfText_setPosition(button->text, text_pos);
}
