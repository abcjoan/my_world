/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** my
*/
#ifndef MY_H_
    #define MY_H_

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <time.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <math.h>
    #include <stdarg.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include "button.h"

    #define MAP_WIDTH 20
    #define MAP_HEIGHT 20
    #define TILE_SIZE 64
    #define NUM_TERRAIN_COLORS 4

typedef enum {
    TOOL_RAISE,
    TOOL_LOWER,
    TOOL_FLATTEN,
    TOOL_SMOOTH
} tool_type_t;

typedef struct {
    float height;
    sfVector2f position_2d;
    sfVector3f position_3d;
    sfColor color;
} tile_t;

typedef struct map_s {
    sfVertexArray *vertices;
    int width;
    int height;
    float **heightmap;
    sfTexture *texture;
} map_t;

typedef struct {
    tool_type_t current_tool;
    int brush_size;
    float intensity;
} toolbar_t;

typedef enum {
    STATE_MENU,
    STATE_GAME,
    STATE_SETTINGS,
    STATE_QUIT
} game_state_t;

typedef struct {
    sfRectangleShape *background;
    button_t *play_button;
    button_t *settings_button;
    button_t *quit_button;
    sfText *title;
    sfFont *font;
} menu_t;
typedef struct {
    float min_height;
    float max_height;
    sfColor color;
} terrain_color_t;
typedef struct {
    int x;
    int y;
} point_t;
typedef struct {
    sfRenderWindow *window;
    sfEvent event;
    map_t *map;
    toolbar_t *toolbar;
    sfView *camera;
    sfVector2f camera_position;
    float zoom_level;
    float rotation_angle;
    game_state_t state;
    menu_t *menu;
} game_t;

button_t *create_button(sfVector2f position, sfVector2f size,
    char *text, sfFont *font);
void destroy_button(button_t *button);
void draw_button(sfRenderWindow *window, button_t *button);
int is_button_hovered(button_t *button, sfVector2i mouse_pos);
int is_button_clicked(button_t *button, sfVector2i mouse_pos);
void init_button_text(button_t *button, button_params_t params);
button_t *alloc_button(void);
void setup_button_params(button_params_t *dest, button_params_t *src);
void init_button_shape(button_t *button, button_params_t params);
sfRenderWindow *create_renderwindow(unsigned int x, unsigned int y,
    unsigned int bpp, char *title);
void free_partial_heightmap(float **heightmap, int rows);
sfColor get_terrain_color(float height);
sfVector2i screen_to_map_coords(game_t *game, sfVector2i screen_pos);
void apply_tool(const game_t *game, int x, int y);
void draw_colored_quad(map_t *map, int x, int y);
void modify_map_init(map_t *map);
void change_tool(game_t *game, tool_type_t tool);
void adjust_brush_size(game_t *game, int delta);

menu_t *create_menu(void);
void destroy_menu(menu_t *menu);
void draw_menu(game_t *game);
void handle_menu_event(game_t *game);
void setup_menu_buttons(menu_t *menu);
void process_button_click(game_t *game, sfVector2i mouse_pos);

map_t *create_map(int width, int height);
void destroy_map(map_t *map);
void draw_map(game_t *game);
sfVector2f to_isometric(int x, int y, float height);
void append_horizontal_line(map_t *map, int x, int y);
void append_vertical_line(map_t *map, int x, int y);

toolbar_t *create_toolbar(void);
void destroy_toolbar(toolbar_t *toolbar);
void move_camera(game_t *game, sfVector2f direction);
void zoom_camera(game_t *game, float factor);

void handle_event(game_t *game);
void if_click(game_t *game);
void handle_game_mouse(game_t *game);
void handle_game_keys(game_t *game);

void loop_main(game_t *game);
void init_game(game_t *game);
void destroy(game_t *game);
void render_state(game_t *game);
int init_game_components(game_t *game);
void init_camera_view(game_t *game);

#endif /* MY_H_ */
