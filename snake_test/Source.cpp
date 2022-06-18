#include "Source.h"

void Game::init_game()
{
    std::srand(time(NULL));

    snake_picture.loadFromFile("resources/images/snake.png");
    snake.setTexture(snake_picture);

    none_picture.loadFromFile("resources/images/none.png");
    none.setTexture(none_picture);

    apple_picture.loadFromFile("resources/images/apple.png");
    apple.setTexture(apple_picture);

    wall_picture.loadFromFile("resources/images/wall.png");
    wall.setTexture(wall_picture);

    snake_head_picture.loadFromFile("resources/images/head.png");
    snake_head.setTexture(snake_head_picture);

    sb_ate_apple.loadFromFile("resources/sounds/get_apple2.wav");
    sound_ate_apple.setBuffer(sb_ate_apple);
    sound_ate_apple.setVolume(40);

    sb_snake_kill_yourself.loadFromFile("resources/sounds/died.wav");
    sound_snake_kill_yourself.setBuffer(sb_snake_kill_yourself);
    sound_snake_kill_yourself.setVolume(50);

    sb_snake_dead_from_wall.loadFromFile("resources/sounds/dead.wav");
    sound_snake_dead_from_wall.setBuffer(sb_snake_dead_from_wall);
    sound_snake_dead_from_wall.setVolume(70);

    sb_pause_game.loadFromFile("resources/sounds/pause_game.wav");
    sound_pause_game.setBuffer(sb_pause_game);
    sound_pause_game.setVolume(20);

    sb_score10.loadFromFile("resources/sounds/score10.wav");
    sound_score10.setBuffer(sb_score10);
    sound_score10.setVolume(45);

    font_score.loadFromFile("resources/fonts/BigFat.otf");
    text_score.setFont(font_score);

    font_game_over.loadFromFile("resources/fonts/BigOld.ttf");
    text_game_over.setFont(font_game_over);

    text_game_over.setString("GAME OVER");
    text_game_over.setCharacterSize(86);
    text_game_over.setFillColor(sf::Color::Blue);
    text_game_over.setPosition((window_width - text_game_over.getLocalBounds().width) / 2, (window_height - text_game_over.getLocalBounds().height) / 2 - 30);
}

/**
 *
 * @return
 */
int Game::get_random_empty_cell()
{
    int empty_cell_count = 0;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (field[j][i] == field_cell_type_none) {
                empty_cell_count++;
            }
        }
    }
    int target_empty_cell_index = std::rand() % empty_cell_count;
    int empty_cell_index = 0;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (field[j][i] == field_cell_type_none) {
                if (empty_cell_index == target_empty_cell_index) {
                    return j * field_size_x + i;
                }
                empty_cell_index++;
            }
        }
    }
    return -1;
}
/**
 * @param applePosition
 * @return
 */
void Game::apple_add()
{
    int applePosition = get_random_empty_cell();
    if (applePosition != -1) {
        field[applePosition / field_size_x][applePosition % field_size_x] = field_cell_type_apple;
    }
}

/**
 * Method clear_field
 * @return
 */
void Game::clear_field()
{
    for (int i = 0; i < field_size_x; i++) {
        for (int j = 0; j < field_size_y; j++) {
            field[i][j] = 0;
        }
    }
    for (int i = 0; i < snake_length; i++) {
        field[snake_position_x - i][snake_position_y] = snake_length - i;
    }
    for (int i = 0; i < field_size_x; i += 1) {
        if (i < 6 || (field_size_x - i - 1) < 6) {
            field[i][0] = field_cell_type_wall;
            field[i][field_size_y - 1] = field_cell_type_wall;
        }
    }
    for (int i = 0; i < field_size_y; i += 1) {
        if (i < 6 || (field_size_y - i - 1) < 6) {
            field[0][i] = field_cell_type_wall;
            field[field_size_x - 1][i] = field_cell_type_wall;
        }
    }
    apple_add();
}

/**
 * Method draw_field - draw cell in the window
 * sf::Color - sets the text color
 * snake_head.getLocalBounds() - retrieves text dimensions height or width
 * std::to_string - turns a value into a string
 * @param window a window a render on
 */

void Game::draw_field(sf::RenderWindow& window)
{

    for (int i = 0; i < field_size_x; i++) {
        for (int j = 0; j < field_size_y; j++) {
            switch (field[i][j]) {
                case field_cell_type_none:
                    none.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(none);
                    break;
                case field_cell_type_apple:
                    apple.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(apple);
                    break;
                case field_cell_type_wall:
                    wall.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(wall);
                    break;
                default:
                    if (field[i][j] == snake_length) {
                        float offset_x = snake_head.getLocalBounds().width / 2;
                        float offset_y = snake_head.getLocalBounds().height / 2;
                        snake_head.setPosition(float(i * cell_size + offset_x), float(j * cell_size) + offset_y);
                        snake_head.setOrigin(offset_x, offset_y);
                        switch (snake_direction) {
                            case snake_direction_up:
                                snake_head.setRotation(90);
                                break;
                            case snake_direction_right:
                                snake_head.setRotation(-180);
                                break;
                            case snake_direction_left:
                                snake_head.setRotation(0);
                                break;
                            case snake_direction_down:
                                snake_head.setRotation(-90);
                                break;
                        }
                        window.draw(snake_head);
                    }
                    else {
                        snake.setPosition(float(i * cell_size), float(j * cell_size));
                        window.draw(snake);
                    }
            }
        }
    }
    // Draw score_bar//
    text_score.setString("Score: " + std::to_string(score));
    text_score.setCharacterSize(28);
    if (score >= 20) {
        text_score.setFillColor(sf::Color::Blue);
        text_score.setPosition(window_width / 2 - 65, 0);
        window.draw(text_score);
    }
    else {
        text_score.setFillColor(sf::Color::Black);
        text_score.setPosition(window_width / 2 - 65, 0);
        window.draw(text_score);
    }

}

/**
 * Method increaseSnake - increases the snake
 * @return
 */
void Game::increaseSnake()
{
    for (int i = 0; i < field_size_x; i++) {
        for (int j = 0; j < field_size_y; j++) {
            if (field[i][j] > field_cell_type_none) {
                field[i][j] += 1;
            }
        }
    }
}

/**
 * Method movement - responsible for the movement of the snake
 * Passage through the wall is carried out using: Passage through the wall is carried out by:
 * zeroing the coordinates or setting the largest coordinate.
 * sound_ate_apple.play - plays sound when eating an apple.
 */
void Game::movement() {
    switch (snake_direction) {
        case snake_direction_up:
            snake_position_y -= 1;
            if (snake_position_y < 0) {
                snake_position_y = field_size_y - 1;
            }
            break;
        case snake_direction_right:
            snake_position_x += 1;
            if (snake_position_x > field_size_x - 1) {
                snake_position_x = 0;
            }
            break;
        case snake_direction_down:
            snake_position_y += 1;
            if (snake_position_y > field_size_y - 1) {
                snake_position_y = 0;
            }
            break;
        case snake_direction_left:
            snake_position_x -= 1;
            if (snake_position_x < 0) {
                snake_position_x = field_size_x - 1;
            }
            break;
    }

    if ((field[snake_position_x][snake_position_y]) != field_cell_type_none) {
        switch (field[snake_position_x][snake_position_y]) {
            case field_cell_type_apple:
                sound_ate_apple.play();
                snake_length += 1;
                score += 1;
                if (score % 10 == 0) {
                    sound_score10.play();
                }
                increaseSnake();
                apple_add();
                break;
            case field_cell_type_wall:
                sound_snake_dead_from_wall.play();
                game_over = true;
                break;
            default:
                if (field[snake_position_x][snake_position_y] > 1) {
                    sound_snake_kill_yourself.play();
                    game_over = true;
                }
        }
    }
    if (!game_over) {
        for (int i = 0; i < field_size_x; i++) {
            for (int j = 0; j < field_size_y; j++) {
                if (field[i][j] > 0) {
                    field[i][j] -= 1;
                }
            }
        }
        field[snake_position_x][snake_position_y] = snake_length;
    }
}
