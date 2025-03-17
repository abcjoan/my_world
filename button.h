/*
** EPITECH PROJECT, 2025
** G-ING-200-MAR-2-1-myworld-joan.augier-billault
** File description:
** button
*/

#include "my.h"

#ifndef BUTTON_H_
    #define BUTTON_H_

typedef struct {
    sfRectangleShape *shape;
    sfText *text;
    int is_hovered;
} button_t;

typedef struct button_params_s {
    sfVector2f position;
    sfVector2f size;
    char *text;
    sfFont *font;
} button_params_t;

#endif /* !BUTTON_H_ */
