/*
** By Kevin Pruvost, May 2020
** File description:
** Object class.
*/

#include "Object.hpp"

Object::Object(Constants::TextureId Id)
    : texture { &textureBase[Id] }
    , textureId { Id }
    , objectIdentity { ObjectIdentity::NormalObject }
{
    setTexture(*texture);
    _hAnimNumber = std::get<1>(Constants::spritesPaths[textureId]);
    _vAnimNumber = std::get<2>(Constants::spritesPaths[textureId]);
    _hSpriteSize = texture->getSize().x / _hAnimNumber;
    _vSpriteSize = texture->getSize().y / _vAnimNumber;

    setOrigin(_hSpriteSize / 2, _vSpriteSize / 2);

    sf::IntRect rect(0, 0, _hSpriteSize, _vSpriteSize);
    setTextureRect(rect);
}

Object::Object(Constants::TextureId Id, int x, int y)
    : Object(Id)
{
    setPosition(x, y);
}

Object::Object(Constants::TextureId Id, const sf::Vector2f & vec)
    : Object(Id, vec.x, vec.y)
{

}

Object::~Object()
{
}

void Object::changeTexture(Constants::TextureId Id)
{
    if (Id == textureId)
        return;

    texture = &textureBase[Id];
    setTexture(*texture);
    textureId = Id;
    _hAnimNumber = std::get<1>(Constants::spritesPaths[textureId]);
    _vAnimNumber = std::get<2>(Constants::spritesPaths[textureId]);
    _hSpriteSize = texture->getSize().x / _hAnimNumber;
    _vSpriteSize = texture->getSize().y / _vAnimNumber;

    setOrigin(_hSpriteSize / 2, _vSpriteSize / 2);

    sf::IntRect rect(0, 0, _hSpriteSize, _vSpriteSize);
    setTextureRect(rect);
}

void Object::changeTexture(Constants::TextureId Id, float time)
{
    _changeTextureClock = std::chrono::steady_clock::now();
    _changeTextureTime = time;
    _changeTextureSet = true;
    _changeTextureId = Id;
}

void Object::setGamePosition(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

/******************************************************************************/
/* 							   ANIMATION PART	 							  */
/******************************************************************************/

void Object::resetAnimation()
{
    _isAnimating = false;
    _animationOptions = AnimateOptions::NoAnimation;
    _animationSpeed = 0;
    _animationSpeedBuffer = 0;
    _horizontalIndex = 0;
    sf::IntRect rect(0, _vSpriteSize * _verticalIndex, _hSpriteSize, _vSpriteSize);
    _animationClock = std::chrono::steady_clock::now();
    setTextureRect(rect);
}

void Object::animate(int options, float speed, int verticalAnimation)
{
    if (!(_isAnimating && options == AnimateOptions::EndsOnStopMoving
    && _verticalIndex == verticalAnimation && speed == _hAnimNumber * _animationSpeedBuffer))
    {
        _verticalIndex = verticalAnimation;
        resetAnimation();
    }
    _animationSpeed = speed / _hAnimNumber;
    _animationOptions = options;
    _animationSpeedBuffer = speed / _hAnimNumber;
    _isAnimating = true;
    prepareAnimate();
    _animationQueue.clear();
}

void Object::animateQueue(int options, float speed, int verticalAnimation)
{
    if (!_animationQueue.empty()
     &&  _animationQueue[_animationQueue.size() - 1].options & AnimateOptions::Loop)
        _animationQueue.removeLast();
    if (_animationQueue.empty())
    {
        _verticalIndex = verticalAnimation;
        resetAnimation();
        _animationSpeed = speed / _hAnimNumber;
        _animationOptions = options;
        _animationSpeedBuffer = speed / _hAnimNumber;
        _isAnimating = true;
        prepareAnimate();
    }
    _animationQueue.push_back({options, speed, verticalAnimation});
}

void Object::animateOneFrame()
{
    auto rect = getTextureRect();
    if (_animationOptions & AnimateOptions::Reverse)
        rect.left -= _hSpriteSize;
    else
        rect.left += _hSpriteSize;
    ++_horizontalIndex;

    if (_horizontalIndex >= _hAnimNumber)
    {
        _horizontalIndex = 0;
        rect.left = (_animationOptions & AnimateOptions::Reverse) ? (_hAnimNumber - 1) * _hSpriteSize: 0;
    }

    setTextureRect(rect);
}

void Object::performAnimation()
{
    if (_changeTextureSet)
    {
        auto end = std::chrono::steady_clock::now();
        float elapsedSeconds = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - _changeTextureClock).count() / 1000;

        if (elapsedSeconds >= _changeTextureTime)
        {
            changeTexture(_changeTextureId);
            _changeTextureSet = false;
        }
    }

    if (!_isAnimating)
        return;

    if (_animationOptions & AnimateOptions::EndsOnStopMoving)
    {
        if (!_isMoving)
        {
            if (_animationOptions == AnimateOptions::EndsOnStopMoving)
            {
                stopAnimation();
                return;
            }

            auto rect = getTextureRect();
            if (_animationOptions & AnimateOptions::EndsOnFirstFrame)
                rect.left = 0;
            if (_animationOptions & AnimateOptions::EndsOnLastFrame)
                rect.left = (_hAnimNumber - 1) * _hSpriteSize;
            setTextureRect(rect);
            stopAnimation();
            return;
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsedSeconds = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - _animationClock).count() / 1000;
    _animationClock = std::chrono::steady_clock::now();

    _animationSpeed -= elapsedSeconds;

    if (_animationSpeed > 0)
        return;

    _animationSpeed = _animationSpeedBuffer;
    animateOneFrame();
    if (_animationOptions & AnimateOptions::EndsOnFirstFrame)
    {
        if (_horizontalIndex == 0)
            stopAnimation();
        else if (_horizontalIndex == _hAnimNumber - 1 && _animationOptions & AnimateOptions::Reverse)
            stopAnimation();
    }
    else if (_animationOptions & AnimateOptions::EndsOnLastFrame)
    {
        if (_horizontalIndex == _hAnimNumber - 1)
            stopAnimation();
        else if (_horizontalIndex == 0 && _animationOptions & AnimateOptions::Reverse)
            stopAnimation();
    }
}

void Object::stopAnimation()
{
    _isAnimating = false;

    if (!_animationQueue.empty() && _animationQueue[0].options == _animationOptions && _animationQueue[0].speed / _hAnimNumber == _animationSpeedBuffer
     && _animationQueue[0].verticalAnimation == _verticalIndex)
    {
        _animationQueue.removeAt(0);
    }

    if (!_animationQueue.empty())
    {
        _verticalIndex = _animationQueue[0].verticalAnimation;
        resetAnimation();
        _animationSpeed = _animationQueue[0].speed / _hAnimNumber;
        _animationOptions = _animationQueue[0].options;
        _animationSpeedBuffer = _animationQueue[0].speed / _hAnimNumber;
        _isAnimating = true;
        prepareAnimate();
    }
    else
        endAnimationFunction();
}

void Object::prepareAnimate()
{
    if (_animationOptions & AnimateOptions::Reverse)
    {
        sf::IntRect rect(_hSpriteSize * (_hAnimNumber - 1), _vSpriteSize * _verticalIndex, _hSpriteSize, _vSpriteSize);
        setTextureRect(rect);
    }
}

void Object::removeActualAnimations()
{
    resetAnimation();
    _animationQueue.clear();
}

void Object::goToFrame(int frame)
{
    if (frame < 0 || frame >= _hAnimNumber)
        return;

    sf::IntRect rect(_hSpriteSize * frame, _vSpriteSize * _verticalIndex, _hSpriteSize, _vSpriteSize);
    setTextureRect(rect);
}

void Object::goToVFrame(int frame)
{
    if (frame < 0 || frame >= _vAnimNumber)
        return;

    _verticalIndex = frame;
    sf::IntRect rect(0, _vSpriteSize * _verticalIndex, _hSpriteSize, _vSpriteSize);
    setTextureRect(rect);
}

/******************************************************************************/
/* 							PROGRESSIVE MOVE PART		 					  */
/******************************************************************************/

void Object::resetProgressiveMove()
{
    if (_isMoving)
        setPosition(_targetPosition);
    _targetPosition.x = 0;
    _targetPosition.y = 0;
    progressiveMoveTime = 0;
    _progressiveMoveClock = std::chrono::steady_clock::now();
    _isMoving = false;
}

void Object::rotationMove(const sf::Vector2f & vec) { rotationMove(vec.x, vec.y); }
void Object::rotationMove(float x, float y)
{
    setPosition(x, y);
}

void Object::move(const sf::Vector2f & vec, float time) { move(vec.x, vec.y, time); }
void Object::move(float x, float y, float time)
{
    if (_isMoving)
        moveTo(_targetPosition.x + x, _targetPosition.y + y, time);
    else
        moveTo(getPosition().x + x, getPosition().y + y, time);
}
void Object::moveTo(const sf::Vector2f & vec, float time) { moveTo(vec.x, vec.y, time); }
void Object::moveTo(float x, float y, float time)
{
    resetProgressiveMove();
    if (time <= 0)
    {
        setPosition(x, y);
        endMoveFunction();
        return;
    }
    _targetPosition.x = x;
    _targetPosition.y = y;
    progressiveMoveTime = time;
    _isMoving = true;
}

void Object::performProgressiveMove()
{
    if (!_isMoving)
        return;

    auto end = std::chrono::steady_clock::now();
    auto elapsedSeconds = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - _progressiveMoveClock).count() / 1000;
    _progressiveMoveClock = std::chrono::steady_clock::now();

    sf::Vector2f distance = {_targetPosition.x - getPosition().x,
                             _targetPosition.y - getPosition().y};
    float ratio = elapsedSeconds / progressiveMoveTime;
    progressiveMoveTime -= elapsedSeconds;
    if (progressiveMoveTime <= 0)
    {
        progressiveMoveTime = 0;
        ratio = 1;
        _isMoving = false;
        endMoveFunction();
    }
    distance.x *= ratio;
    distance.y *= ratio;
    sf::Sprite::move(distance);
}

void Object::setVisible(bool b)
{
    static sf::Color visColor = {255, 255, 255, 255};
    static sf::Color invisColor = {255, 255, 255, 0};

    setColor(((b) ? visColor : invisColor));
}

bool Object::isVisible()
{
    return getColor().a != 0;
}