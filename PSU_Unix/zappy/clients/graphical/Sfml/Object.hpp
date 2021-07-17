/*
** By Kevin Pruvost, May 2020
** File description:
** Object class.
*/

#pragma once

// Project includes
#include "TextObject.hpp"

// C++ includes
#include <chrono>

/**
 * @brief Inherits from sf::Sprite.
 * Its purpose is to make the user able to animate it easily and to make it
 * move progressively all in one function.
 * Its other purpose is also to be inherited by many other children classes
 * to make specific 'Objects'.
 */
class Object : virtual public sf::Sprite
{
public:
	Object(Constants::TextureId Id);
	Object(Constants::TextureId Id, int x, int y);
	Object(Constants::TextureId Id, const sf::Vector2f & vec);
	~Object();

public:
	/**
	 * @brief Changes the texture according to the Constants::TextureId enumeration.
	 * @param Id
	 */
	void changeTexture(Constants::TextureId Id);
	void changeTexture(Constants::TextureId Id, float time);
	/**
	 * @brief Sets the pos attribute.
	 * @param x
	 * @param y
	 */
	void setGamePosition(int x, int y);

private:
	std::chrono::steady_clock::time_point _changeTextureClock;
	float _changeTextureTime;
	bool _changeTextureSet = false;
	Constants::TextureId _changeTextureId = Constants::TextureId::TOTAL_TEXTURE;

public:
	sf::Texture * texture = nullptr;
	Constants::TextureId textureId = Constants::TextureId::TOTAL_TEXTURE;
	sf::Vector2i pos = {0, 0};

/******************************************************************************/
/* 							   ANIMATION PART	 							  */
/******************************************************************************/
public:
	/**
	 * @brief Options for animation.
	 */
	enum AnimateOptions
	{
		NoAnimation = 0,
		Loop = 0b1,
		EndsOnFirstFrame = 0b10,
		EndsOnLastFrame = 0b100,
		EndsOnStopMoving = 0b1000,
		Reverse = 0b10000
	};
	/**
	 * @brief Animates the sprite.
	 * See the AnimateOptions enum for the 'options' parameter.
	 * 'speed' is the time needed (in seconds) to make the complete animation.
	 * /!\ : Cancels animateQueue().
	 * @param options
	 * @param speed
	 * @param verticalAnimation
	 */
	void animate(int options, float speed, int verticalAnimation = 0);
	/**
	 * @brief Makes a queue with multiple animations, the parameters are the
	 * same as animate().
	 * @param options
	 * @param speed
	 * @param verticalAnimation
	 */
	void animateQueue(int options, float speed, int verticalAnimation = 0);
	/**
	 * @brief Stops the actual animation and pursue with the next one if
	 * there's a queue.
	 */
	void resetAnimation();
	/**
	 * @brief Stops the animation.
	 */
	void removeActualAnimations();
	/**
	 * @brief Used exclusively by ZappyRenderWindow::draw().
	 */
	void performAnimation();
	/**
	 * @brief Go to horizontal frame according to the parameter.
	 * @param frame
	 */
	void goToFrame(int frame);
	/**
	 * @brief Go to vertical frame according to the parameter.
	 * @param frame
	 */
	void goToVFrame(int frame);
	/**
	 * @brief Virtual function modified by children that is used at the end
	 * of an animation.
	 */
	virtual void endAnimationFunction() {};
	/**
	 * @brief Virtual function modified by children that is used at the end of
	 * a movement.
	 */
	virtual void endMoveFunction() {};
	/**
	 * @brief Returns if the object is animating atm.
	 * @return true
	 * @return false
	 */
	bool isAnimating() { return _isAnimating; }
protected:
	void animateOneFrame();
	void stopAnimation();
	void prepareAnimate();
protected:
	/**
	 * @brief Structure used by animateQueue() to store animations informations.
	 */
	struct AnimationInfos
	{
		int options;
		float speed;
		int verticalAnimation;
	};

	int _animationOptions = AnimateOptions::NoAnimation;
	float _animationSpeed = 0;
	float _animationSpeedBuffer = 0;
	int _hAnimNumber;
	int _vAnimNumber;
	int _hSpriteSize;
	int _vSpriteSize;
	int _verticalIndex = 0;
	int _horizontalIndex = 0;
	bool _isAnimating = false;
	KVector<AnimationInfos> _animationQueue;
	std::chrono::steady_clock::time_point _animationClock;

/******************************************************************************/
/* 							PROGRESSIVE MOVE PART		 					  */
/******************************************************************************/
public:
	virtual void rotationMove(const sf::Vector2f & vec);
	virtual void rotationMove(float x, float y);
	/**
	 * @brief Moves the object, if time is >= 0, then it will move progressively.
	 * @param vec
	 * @param time
	 */
	virtual void move(const sf::Vector2f & vec, float time = 0);
	virtual void move(float x, float y, float time = 0);
	/**
	 * @brief Moves the object to the given position.
	 * @param vec
	 * @param time
	 */
	virtual void moveTo(const sf::Vector2f & vec, float time = 0);
	virtual void moveTo(float x, float y, float time = 0);
	/**
	 * @brief If time set by move() or moveTo() was >= 0, teleports the object to the
	 * given position and so, stops the animation.
	 */
	void resetProgressiveMove();
	/**
	 * @brief Used exclusively by ZappyRenderWindow::draw().
	 */
	void performProgressiveMove();
protected:
	sf::Vector2f _targetPosition = {0, 0};
	bool _isMoving = false;
	std::chrono::steady_clock::time_point _progressiveMoveClock;
public:
	float progressiveMoveTime = 0;

/******************************************************************************/
/* 								OTHER PART				 					  */
/******************************************************************************/

public:
	/**
	 * @brief Sets an object visible or not.
	 * @param b
	 */
	void setVisible(bool b);
	/**
	 * @brief Returns if the object is visible or not.
	 * @return true
	 * @return false
	 */
	bool isVisible();

public:
	KVector<TextObject> _textObjects;

public:
	enum ObjectIdentity
	{
		NormalObject,
		Mob,
		Egg,
		Floor,
		Interface
	};
	ObjectIdentity objectIdentity;

};