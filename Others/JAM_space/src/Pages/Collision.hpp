/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Collision
*/

#pragma once

#include "Sfml.hpp"
#include "../AEatable.hpp"
#include <list>

namespace Jam {
    class ParticleGenerator;
    class Collision {
        public: static void perform_collision(std::list<std::unique_ptr<AEatable>> &collider);
    };
}