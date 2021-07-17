/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Collision
*/

#include "Collision.hpp"
#include "../Particle.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unistd.h>
/*
std::ostream &operator<<(std::ostream &os, sf::FloatRect &r)
{
    os << "(x=" << r.left << ", y=" << r.top << ", width=" << r.width << ", height=" << r.height << ")";
    return os;
}
*/
void Jam::Collision::perform_collision(std::list<std::unique_ptr<AEatable>> &colliders)
{
    for (std::unique_ptr<AEatable> &obj : colliders) {
        sf::FloatRect obj1 = obj->getGlobalBounds();
        sf::Vector2f orig1(obj1.left+obj1.width/2,obj1.top+obj1.height/2);
        for (std::unique_ptr<AEatable> &collider : colliders) {
            if (obj.get() == collider.get())
                continue;
            sf::FloatRect rect = collider->getGlobalBounds();
            sf::Vector2f orig2(rect.left+rect.width/2,rect.top+rect.height/2);

            if (((obj1.left > rect.left && obj1.left < rect.left+rect.width) || (rect.left > obj1.left && rect.left < obj1.left+obj1.width)) && 
                ((obj1.top > rect.top && obj1.top < rect.top+rect.height) || (rect.top > obj1.top && rect.top < obj1.top+obj1.height))) {
                float len = sqrt(pow(orig1.x-orig2.x, 2) + pow(orig1.y-orig2.y, 2));
                float a = (orig2.y-orig1.y) / (orig2.x-orig1.x);
                float d1 = sqrt(pow(sqrt(1/(1+a*a)) * obj1.width/2,2) + pow(a * sqrt(1/(1+a*a)) * obj1.height/2,2));
                float d2 = sqrt(pow(sqrt(1/(1+a*a)) * rect.width/2,2) + pow(a * sqrt(1/(1+a*a)) * rect.height/2,2));

                if (len < d1+d2) {
                    size_t value1 = obj->getNutritiveValue();
                    size_t value2 = collider->getNutritiveValue();

                    if (value1*0.9 >= value2 && obj->eat(*collider)) {
                        colliders.remove(collider);
                        return;
                    } else if (value2*0.9 >= value1 && collider->eat(*obj)) {
                        colliders.remove(obj);
                        return;
                    }
                }
            }
        }
    }
}