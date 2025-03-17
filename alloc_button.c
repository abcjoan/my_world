/*
** EPITECH PROJECT, 2025
** alloc_button
** File description:
** alloc_button
*/

#include "my.h"

button_t *alloc_button(void)
{
    button_t *button = malloc(sizeof(button_t));

    if (!button)
        return NULL;
    button->shape = sfRectangleShape_create();
    button->text = sfText_create();
    if (!button->shape || !button->text) {
        if (button->shape)
            sfRectangleShape_destroy(button->shape);
        if (button->text)
            sfText_destroy(button->text);
        free(button);
        return NULL;
    }
    button->is_hovered = 0;
    return button;
}
