/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** ModuleGraph
*/

#ifndef MODULEGRAPH_HPP_
#define MODULEGRAPH_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "../Interfaces/IMonitorModule.hpp"
 #include <vector>

class Stick {
	public:
		Stick() {};
		~Stick() {};
		sf::RectangleShape _stick;
		sf::Vector2f _pos;
		sf::Color _color;
		float _value;
};

typedef enum e_MemSwap {
	MEMFREE,
	MEMTOT,
	CACHED,
	BUFF,
	SWFREE,
	SWTOT
} MemSwap;

class ModuleGraph {
	public:
		ModuleGraph(IMonitorModule *module);
		~ModuleGraph();
		IMonitorModule &getModule() const {return(_module);};
		void setPos(sf::Vector2f pos);
		sf::Vector2f getPos() const {return(_pos);}
		sf::Text getTextFirst() const { return _text; };
		sf::Text getTextSecond() const { return _textSec; };
		void setTextTwo(sf::Text text, sf::Text textSec) { _text = text; _textSec = textSec; };
		void setMemorySwapArray(sf::RectangleShape *rect, sf::Color color) { rect->setFillColor(color);_memSwapArray.push_back(rect); };
		void resetMemorySwapArray(void) {_memSwapArray.clear();}
		void resetSticks() {_sticks.clear();}
		sf::Sprite &getSpriteMod() {return(_spriteMod);};
		sf::Sprite &getSpriteModIn() {return(_spriteModIn);};
		sf::Sprite getSpriteModConst() const {return(_spriteMod);}
		sf::Sprite getSpriteModInConst() const {return(_spriteModIn);}
		void setTexture(sf::Texture textureFirst, sf::Texture textureSecond);
		void createStick(int tabCPU[60], float max);
		std::list<Stick *> getSticks() const {return(_sticks);}
		std::vector<sf::RectangleShape *>getMemSwapArray() const {return(_memSwapArray);}

	private:
		IMonitorModule &_module;
		sf::Text _text;
		sf::Text _textSec;
		sf::Text _textTre;
		sf::Vector2f _pos;
		sf::Sprite _spriteMod;
		sf::Sprite _spriteModIn;
		std::vector<sf::RectangleShape *> _memSwapArray;
		std::list<Stick *> _sticks;
};

#endif /* !MODULEGRAPH_HPP_ */
