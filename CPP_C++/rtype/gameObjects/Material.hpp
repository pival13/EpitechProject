/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Material
*/

#pragma once

#include "Transform.hpp"
#include <map>
#include <SFML/Graphics.hpp>

class Material {
    public:
        Material() = delete;
        Material(const Material &) = delete;
        Material &operator=(const Material &) = delete;
        ~Material();

        static Material *createMaterial(const std::string &filename);

        const sf::Texture &getTexture() const { return _texture; }
        //sf::Texture& getTexture() { return _texture; }

    protected:
        sf::Texture _texture;
    
    private:
        Material(const std::string& filename);
};
