#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>
#include <string>

const int field_cell_type_none = 0;
const int field_cell_type_apple = -1;
const int field_cell_type_wall = -2;
const int snake_direction_up = 0;
const int snake_direction_right = 1;
const int snake_direction_down = 2;
const int snake_direction_left = 3;
const int field_size_x = 35;
const int field_size_y = 25;
const int cell_size = 32;
const int window_width = field_size_x * cell_size;
const int window_height = field_size_y * cell_size;
sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Snake", sf::Style::Close);

/**
 * Game - initializes variables that are used in the game code
 * field[][] - a two-dimensional array storing the coordinates of the snake.
 * snake_position - the x or y coordinate of the snake.
 * snake length - stores the current length of the snake.
 * score - stores the current account.
 * game paused - pauses the game.
 * game over - a variable that stores the value of losing a game.
 * sf::Texture and sf::Sprite - allows you to initialize images in the game.
 * sf::SoundBuffer and sf::Sound - allows you to use sounds in the game.
 * sf::Font and sf::Text - allows you to use downloaded fonts.
 */
struct Game
{
    int field[field_size_x][field_size_y];
    int snake_position_x = field_size_x / 2;
    int snake_position_y = field_size_y / 2;
    int snake_length = 4;
    int snake_direction = snake_direction_right;
    int score = 0;


    bool game_paused = false;
    bool game_over = false;

    sf::Texture snake_picture;
    sf::Sprite snake;

    sf::Texture none_picture;
    sf::Sprite none;

    sf::Texture apple_picture;
    sf::Sprite apple;

    sf::Texture wall_picture;
    sf::Sprite wall;

    sf::Texture snake_head_picture;
    sf::Sprite snake_head;

    sf::SoundBuffer sb_ate_apple;
    sf::Sound sound_ate_apple;

    sf::SoundBuffer sb_snake_kill_yourself;
    sf::Sound sound_snake_kill_yourself;

    sf::SoundBuffer sb_pause_game;
    sf::Sound sound_pause_game;

    sf::SoundBuffer sb_snake_dead_from_wall;
    sf::Sound sound_snake_dead_from_wall;

    sf::SoundBuffer sb_score10;
    sf::Sound sound_score10;

    sf::Font font_score;
    sf::Text text_score;

    sf::Font font_game_over;
    sf::Text text_game_over;

    void init_game();
    int get_random_empty_cell();
    void apple_add();
    void clear_field();
    void increaseSnake();
    void movement();
    void draw_field();
    bool isGamePaused();
};
