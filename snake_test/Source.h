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
 * Game - initializes variables and methods that are used in the game code
 * sf::Texture and sf::Sprite - allows you to initialize images in the game.
 * sf::SoundBuffer and sf::Sound - allows you to use sounds in the game.
 * sf::Font and sf::Text - allows you to use downloaded fonts.
 */
struct Game
{
    /// a two-dimensional array storing the coordinates of the snake.
    int field[field_size_x][field_size_y];

    /// the x coordinate of the snake.
    int snake_position_x = field_size_x / 2;

    /// the y coordinate of the snake.
    int snake_position_y = field_size_y / 2;

    /// stores the current length of the snake at the beginning of the game it is equal to 4.
    int snake_length = 4;

    /// the direction of movement of the snake.
    int snake_direction = snake_direction_right;

    /// stores the current account.
    int score = 0;

    /// pauses the game.
    bool game_paused = false;

    /// a variable that stores the value of losing a game.
    bool game_over = false;

    /// snake.png
    sf::Texture snake_picture;
    /// snake body picture
    sf::Sprite snake;

    /// none.png
    sf::Texture none_picture;
    /// transparent picture
    sf::Sprite none;

    /// apple.png
    sf::Texture apple_picture;
    sf::Sprite apple;

    /// wall.png
    sf::Texture wall_picture;
    /// picture of the wall
    sf::Sprite wall;

    /// head.png
    sf::Texture snake_head_picture;
    /// snake head picture
    sf::Sprite snake_head;

    /// get_apple_2.wav
    sf::SoundBuffer sb_ate_apple;
    /// sound when eating an apple
    sf::Sound sound_ate_apple;

    /// died.wav
    sf::SoundBuffer sb_snake_kill_yourself;
    /// sound during death from yourself
    sf::Sound sound_snake_kill_yourself;

    /// pause_game.wav
    sf::SoundBuffer sb_pause_game;
    /// sound for pause in game
    sf::Sound sound_pause_game;

    /// dead.wav
    sf::SoundBuffer sb_snake_dead_from_wall;
    /// sound during death from the wall
    sf::Sound sound_snake_dead_from_wall;

    /// score10.wav
    sf::SoundBuffer sb_score10;
    /// sound at a time when the count is a multiple of 10
    sf::Sound sound_score10;

    ///BigOld.ttf
    sf::Font font_score;
    /// "Score"
    sf::Text text_score;

    /// BigOld.ttf
    sf::Font font_game_over;
    /// "Game Over"
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
