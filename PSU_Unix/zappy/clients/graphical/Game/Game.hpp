/*
** By Kevin Pruvost, May 2020
** File description:
** Game class.
*/

#pragma once

// Project includes
#include "Page.hpp"
#include "Target.hpp"
#include "BottomTarget.hpp"
#include "Incantation.hpp"
#include "GameBackground.hpp"
#include "PlayerButton.hpp"
#include "TeamButton.hpp"

// Lib includes
#include "Json/Json.hpp"

// C++ includes
#include <map>

/**
 * @brief Inherits from Page, aimed to be where every events will be displayed.
 */
class Game : virtual public Page
{
public:
	Game(GraphicalClient & client, ZappyRenderWindow & window, sf::Event & event);
	~Game();

	/**
	 * @brief Override of Page::compute().
	 * @param window
	 * @param event
	 * @param client
	 * @return int
	 */
	int compute(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client) override;
	/**
	 * @brief Override of Page::draw().
	 * @param window
	 * @param event
	 * @param client
	 * @return int
	 */
    int draw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client) override;

private:
	void formMap(GraphicalClient & client);
	void buildTileMap();
	sf::Color generateRandomSfColor();

	enum Direction
	{
		DOWN,
		RIGHT,
		UP,
		LEFT
	};
	void rotate(Direction direction, ZappyRenderWindow & window);
	int _angle = 0;
	void placeObjectsAfterRotation();
	void placeNewPlayer();
	void placeNewEgg();
	void placeCamera(ZappyRenderWindow & window);
	void convertPositionWithRotation(sf::Vector2i & pos);
	void convertPositionWithRotation(sf::Vector2f & pos);
	void moveCamera(ZappyRenderWindow & window, Direction direction);
	void moveCameraTo(ZappyRenderWindow & window, int x, int y);
	void moveCameraTo(ZappyRenderWindow & window, const sf::Vector2i & vec);

	void focusCameraOn(Object * object, ZappyRenderWindow & window);
    void focusOnPlayer(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
    void focusOnEgg(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);

	sf::Vector2i _cameraPosition = {0, 0};

	void checkCursorHighlight();

private:
	KVector<Mob> _players;
	KVector<Cocoon> _eggs;
    KVector<Object> _objects;
    KVector<Floor> _tiles;
	KVector<KVector<std::reference_wrapper<Floor>>> _tilesByPosition;
	sf::Vector2f _mapSize = {0, 0};
	GameBackground _background;

	ssize_t _tileWidth;
	ssize_t _tileHeight;

	int _mouseWheelSensitivity;
	bool _invertXAxis;
	bool _invertYAxis;

	Cursor _cursor;

	std::map<std::string, sf::Color> _teamsColor;

	Target _cameraTarget;
	Object * cameraTarget()
	{
		if (_cameraTarget.objectIdentity == Object::ObjectIdentity::Mob)
		{
			for (auto & player : _players)
			{
				if (_cameraTarget == player)
					return &player;
			}
		}
		else if (_cameraTarget.objectIdentity == Object::ObjectIdentity::Egg)
		{
			for (auto & player : _eggs)
			{
				if (_cameraTarget == player)
					return &player;
			}
		}
		else
		{
			for (auto & player : _tiles)
			{
				if (_cameraTarget == player)
					return &player;
			}
		}
		return nullptr;
	}

/******************************************************************************/
/*																			  */
/*								INTERFACE PART							      */
/*																			  */
/******************************************************************************/

void updatePanelInfos();

InterfaceObject _objectDescriptionPanel;
InterfaceObject _bottomBar;
InterfaceObject _tvBackground;
InterfaceObject _face;
InterfaceObject _tvEffect;

InterfaceObject _compass;
InterfaceObject _compassCursor;
PlayerData::Orientation _orientation = PlayerData::Orientation::NORTH;

Constants::TextureId _currentTvTextureId = Constants::TextureId::FLOOR1;

KVector<InterfaceObject> _interfaceObjects;
KVector<InterfaceTextObject> _interfaceTextObjects;

InterfaceObject _timePanel;
InterfaceObject _timeSetButton;
InterfaceObject _timeText;

void writeInteractions(sf::Event & event, GraphicalClient & client);
std::string getChar(sf::Event & event);

bool timeTextFocused = false;

InterfaceTextObject _displayWin;
bool _gameEnded = false;
bool closed = false;
std::string _winningTeam;

void checkEnd(ZappyRenderWindow & window);

/******************************************************************************/
/*																			  */
/*								BOTTOM BAR PART								  */
/*																			  */
/******************************************************************************/

#define MAX_TEAMS_LINE_SIZE 6
#define MAX_PLAYERS_LINE_SIZE 8

InterfaceObject _playersButton;
InterfaceObject _teamsButton;
InterfaceObject _arrowBetweenPlayersTeams;

InterfaceObject _arrowUp;
InterfaceObject _arrowDown;

BottomTarget _displayTarget;
std::string teamFocused;

KVector<BottomButton> * displayBar()
{
	if (_displayTarget.teamName.empty())
		return &_teamsButtons.at(_displayTarget.index);
	else
		return &_playersButtons.at(_displayTarget.teamName).at(_displayTarget.index);
}

KVector<KVector<BottomButton>> _teamsButtons;
std::map<std::string, KVector<KVector<BottomButton>>> _playersButtons;
std::map<std::string, size_t> _playersCountPerTeam;

InterfaceTextObject _playerCount;

void goToTeamsBar();
void checkPlayerCount();

bool bottomBarInteractions(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
bool displayBarInteractions(ZappyRenderWindow & window);
void refreshBottomBar();
void addToBottomBar(Mob * player);
void addToBottomBar(const std::string & teamName);
void removeFromBottomBar(Mob * player, ZappyRenderWindow & window);
void removeFromBottomBar(const std::string & teamName);
void formatBottomBar();
void resetBottomBar();
void checkForArrowsBottomBar();

void refreshIcons(int id, Constants::TextureId textureId);

void moveDisplayBar(bool up);

/******************************************************************************/
/*																			  */
/*									EVENTS PART								  */
/*																			  */
/******************************************************************************/

private:
	void leftClickInteractions(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);

private:
	int computeEvents(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);

	void eventBct(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventTna(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPnw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPpo(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPlv(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPin(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPdr(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPgt(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventSgt(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventSeg(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventSmg(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventEnw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventEht(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventEbo(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventEdi(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPfk(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPex(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPbc(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPic(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPie(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
	void eventPdi(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);

private:
	int _timeUnit = 0;
	std::string _serverMsg;
	KVector<Incantation> _incantations;

	std::unique_ptr<std::thread> thread;
};