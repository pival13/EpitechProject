/*
** EPITECH PROJECT, 2020
** Background
** File description:
** main window
*/

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include "Background.hpp"

Jam::BackgroundStar::BackgroundStar()
{
    this->size = (float)(rand() % 20);
    this->growing = (int)this->size % 2;
    this->size /= 10;
    this->shape = sf::CircleShape(this->size);
    this->shape.setFillColor(sf::Color(255 - (rand() % 16), 255 - (rand() % 32), 255 - (rand() % 32), 255));
}

Jam::BackgroundStar::~BackgroundStar() {

}

void Jam::BackgroundStar::changeSize() {
    unsigned int seed = rand();

    if (this->size == STAR_SIZE && (seed & 2)) {
        return;
    }
    if (this->size == 0 && growing != true) {
        growing = seed & 4;
        return;
    }
    if (seed >> (32 - GROWTH_CHANCE) != 0)
        return;

    this->size += this->growing ? STAR_INCREMENT : -STAR_INCREMENT;

    if (this->growing)
        this->shape.move({-STAR_INCREMENT, -STAR_INCREMENT});
    else
        this->shape.move({STAR_INCREMENT, STAR_INCREMENT});

    this->pos = this->shape.getPosition();

    this->growing = this->size >= STAR_SIZE ? false : (this->size <= 0 ? true : this->growing);

    this->shape.setRadius(this->size);
}

float Jam::BackgroundStar::getSize() {
    return this->size;
}

void Jam::BackgroundStar::setPosition(sf::Vector2f &pos) {
    this->shape.setPosition(pos);
}

void Jam::BackgroundStar::setPosition(sf::Vector2u &wdwSize) {
    this->shape.setPosition((rand() % (int)(wdwSize.x - this->size - 1)), (rand() % (int)(wdwSize.y - this->size - 1)));
}

bool Jam::BackgroundStar::isGrowing() {
    return (this->growing);
}

sf::CircleShape &Jam::BackgroundStar::getShape() {
    return (this->shape);
}

void Jam::BackgroundStar::move(const sf::Vector2f &vector) {
    shape.move(vector);
}

/*
 *
 * END OF
 *  
 * BACKGROUND STAR FUNCTIONS
 * 
 */

Jam::Background::Background(sf::Vector2u wdwSize)
    : wdwSize(wdwSize)
    , starsNb(sqrt(wdwSize.x * wdwSize.y))
    , old({-666, -666})
{
    for (size_t i = 0; i < 700; i++) {
        this->stars.push_back(Jam::BackgroundStar());
        this->stars[i].setPosition(this->wdwSize);
    }
}

Jam::Background::~Background() {

}

void Jam::Background::printStars(sf::RenderWindow &wdw)
{
    if (getMs(_time) >= 1000/30)
    {
        changeStarsSizes();
        resetTime(_time);
    }
    for (BackgroundStar &star : stars) {
        wdw.draw(star.getShape());
    }
}

void Jam::Background::changeStarsSizes() {
    for (BackgroundStar &star : stars) {
        star.changeSize();
        if (star.getSize() == 0.f && star.isGrowing())
            star.setPosition(this->wdwSize);
    }
}

void Jam::Background::move(const sf::Vector2f & vector)
{
    if (old.x == -666 && old.y == -666) {
        this->old = vector;
        return;
    }
    sf::Vector2f movement = {vector.x - old.x, vector.y - old.y};
    for (BackgroundStar &star : stars) {
        star.move(movement);
    }
    old = vector;
}

/*
int main()
{
    srand(getpid());
    // create the window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My window");

    sf::Vector2u sizes = window.getSize();
    
    //Jam::BackgroundStar shape;

    Jam::Background bg(sizes);

    //shape.setFillColor(sf::Color(0xFFFFFFFF));


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //bg.changeStarsSizes();
        //shape.setPosition((rand() % (sizes.x - (unsigned int)(shape.getGlobalBounds().height))), (rand() % (sizes.y - (unsigned int)(shape.getGlobalBounds().width))));

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        bg.printStars(window);

        // end the current frame
        window.display();
        usleep(1000000 / 30);
        std::cout << "TURN" << std::endl;
    }

    return 0;
}
*/