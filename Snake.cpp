#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
#include "snake_test/Source.cpp"


/**
 * std::vector<int> -
 *
 */
auto game()
{
    Game game;
    game.init_game();

    std::srand(time(NULL));

    game.clear_field();

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (game.game_paused) {
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            game.game_paused = false;
                            game.sound_pause_game.play();
                            break;
                        case sf::Keyboard::G:
                            game.game_over = true;
                            game.sound_snake_dead_from_wall.play();
                            break;
                    }

                }
                else {
                    int new_direction = game.snake_direction; /* Взаимствование */
                    switch (event.key.code) {                 /* Взаимствование */
                        case sf::Keyboard::Up:
                            new_direction = snake_direction_up;
                            break;
                        case sf::Keyboard::Down:
                            new_direction = snake_direction_down;
                            break;
                        case sf::Keyboard::Left:
                            new_direction = snake_direction_left;
                            break;
                        case sf::Keyboard::Right:
                            new_direction = snake_direction_right;
                            break;
                        case sf::Keyboard::W:
                            new_direction = snake_direction_up;
                            break;
                        case sf::Keyboard::S:
                            new_direction = snake_direction_down;
                            break;
                        case sf::Keyboard::A:
                            new_direction = snake_direction_left;
                            break;
                        case sf::Keyboard::D:
                            new_direction = snake_direction_right;
                            break;
                        case sf::Keyboard::Escape:
                            game.game_paused = true;
                            game.sound_pause_game.play();
                            break;
                        case sf::Keyboard::G:
                            game.game_over = true;
                            game.sound_snake_dead_from_wall.play();
                            break;
                    }
                    if (new_direction == snake_direction_up and game.snake_direction == snake_direction_down or
                                                                new_direction == snake_direction_down and game.snake_direction == snake_direction_up or
                                                                                                          new_direction == snake_direction_left and game.snake_direction == snake_direction_right or
                                                                                                                                                    new_direction == snake_direction_right and game.snake_direction == snake_direction_left)
                    {
                        new_direction = game.snake_direction;
                    }


                    game.snake_direction = new_direction;
                }
            }
        }



        if (!game.game_paused) {
            game.movement();
        }

        window.clear(sf::Color(150, 212, 140));

        game.draw_field();

        if (game.game_over) {
            window.draw(game.text_game_over);
            window.display();
            sf::sleep(sf::seconds(2));
            window.close();
        }

        window.display();

        sf::sleep(sf::milliseconds(100));
    }
    return 0;
}


int main()
{
    setlocale(LC_ALL, "ru");

    game();
}