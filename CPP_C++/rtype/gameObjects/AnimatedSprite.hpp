/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** AnimatedSprite
*/

#pragma once

#include "Drawable.hpp"

class AnimatedSprite : public Drawable {
    public: struct AnimatedSpriteData {
        AnimatedSpriteData() = default;
        AnimatedSpriteData(const std::string &animFilepath, const std::vector<Transform> &datas);
        AnimatedSpriteData(const std::string &animFilepath, const Transform &initialFrame, const Vector2 &offsetBetweenFrame, size_t nbFrame);
        AnimatedSpriteData(const std::string &animFilepath, const std::vector<std::pair<Vector2, Vector2>> &listSizeOffset, double angle=0, const Vector2 &scale={1, 1});
        ~AnimatedSpriteData();

        std::string filepath;
        std::vector<Transform> datas;
    };
    
    public:
        AnimatedSprite(GameObject *parent=nullptr);
        AnimatedSprite(size_t FPS, const std::map<std::string, AnimatedSpriteData> &datas, GameObject *parent=nullptr);
        ~AnimatedSprite();

        void playAnimation(const std::string &animId, bool loop=false);

        const sf::Sprite &getSprite();

    protected:
        void changeFrame();

    protected:
        std::map<std::string, AnimatedSpriteData> animDatas;
        std::string currentAnim;
        std::string prevAnim;
        size_t nbFrame;
        size_t animFPS;
        std::chrono::system_clock::time_point lastChangeFrame;
};
