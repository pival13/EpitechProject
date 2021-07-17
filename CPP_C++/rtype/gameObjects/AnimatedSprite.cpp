/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** AnimatedSprite
*/

#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSpriteData::AnimatedSpriteData(const std::string &animFilepath, const std::vector<Transform> &_datas)
: filepath(animFilepath), datas(_datas) {}
AnimatedSprite::AnimatedSpriteData::AnimatedSpriteData(const std::string &animFilepath, const std::vector<std::pair<Vector2, Vector2>> &listOffsetPos, double angle, const Vector2 &scale)
: filepath(animFilepath)
{
    for (const auto &p : listOffsetPos)
        datas.push_back(Transform(p.second, p.first, {0.5, 0.5, 0.5}, {0, 0, angle}, {scale.x, scale.y, 1}));
}
AnimatedSprite::AnimatedSpriteData::AnimatedSpriteData(const std::string &animFilepath, const Transform &initialFrame, const Vector2 &offsetBetweenFrame, size_t nbFrame)
: filepath(animFilepath)
{
    for (size_t i = 0; i != nbFrame; ++i)
        datas.push_back(Transform(
            initialFrame.getPosition()+(offsetBetweenFrame)*double(i),
            initialFrame.getSizeUnscaled(),
            initialFrame.getPivot(),
            initialFrame.getDegRotation(),
            initialFrame.getScale()
        ));
}

AnimatedSprite::AnimatedSpriteData::~AnimatedSpriteData() {}

AnimatedSprite::AnimatedSprite(GameObject *parent)
: Drawable("", Transform(), parent), nbFrame(0), animFPS(0), lastChangeFrame(std::chrono::system_clock::now()) {}
AnimatedSprite::AnimatedSprite(size_t FPS, const std::map<std::string, AnimatedSpriteData> &datas, GameObject *parent)
: AnimatedSprite(parent)
{
    animFPS = FPS;
    animDatas = datas;
    if (!datas.empty())
        prevAnim = currentAnim = datas.begin()->first;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::playAnimation(const std::string &animId, bool loop)
{
    if (!animDatas.count(animId))
        throw std::invalid_argument("Unknow animation: " + animId);
    prevAnim = loop ? animId : currentAnim;
    currentAnim = animId;
    nbFrame = 0;
    lastChangeFrame = std::chrono::system_clock::now();
    materialRect = animDatas[animId].datas.front();
    setMaterial(Material::createMaterial(animDatas[animId].filepath));
}

void AnimatedSprite::changeFrame()
{
    if (!animDatas.count(currentAnim) || animDatas[currentAnim].datas.size() == 0) return;
    if (nbFrame == animDatas[currentAnim].datas.size() - 1) {
        if (animDatas.count(prevAnim))
            currentAnim = prevAnim;
        nbFrame = 0;
    } else
        ++nbFrame;
    materialRect = animDatas[currentAnim].datas[nbFrame];
    setMaterial(Material::createMaterial(animDatas[currentAnim].filepath));
}

const sf::Sprite &AnimatedSprite::getSprite()
{
    if (!_sprite.getTexture() && animDatas.count(currentAnim))
        setMaterial(Material::createMaterial(animDatas[currentAnim].filepath));
    if (lastChangeFrame + std::chrono::milliseconds(1000 / animFPS) < std::chrono::system_clock::now()) {
        changeFrame();
        lastChangeFrame += std::chrono::milliseconds(1000 / animFPS);
    }
    return _sprite;
}