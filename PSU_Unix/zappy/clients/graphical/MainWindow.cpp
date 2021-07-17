/*
** By Kevin Pruvost, May 2020
** File description:
** MainWindow class.
*/

#include "MainWindow.hpp"

static std::mutex mutex;
sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

MainWindow::MainWindow(const std::string & ip, const std::string & port)
    : _window(videoMode, "Zerggy", sf::Style::Titlebar | sf::Style::Close
        | sf::Style::Fullscreen)
    , _client(ip, port)
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::createPages()
{
    _pages.emplace_back(new Menu(_window));
    _pages.emplace_back(new Game(_client, _window, _event));
}

void MainWindow::playingMusic()
{
    if (musicBase[Constants::MusicId::MUSIC_GAME].getStatus() != sf::Music::Status::Playing)
        musicBase[Constants::MusicId::MUSIC_GAME].play();
}

int MainWindow::exec()
{
    if (!_client._logged)
    {
        std::unique_lock<std::mutex> lock(mutex);
        _client._loggedCond.wait_for(lock, std::chrono::seconds(5));
        if (!_client._logged)
            throw EXCEPTION("Zappy connection protocol has not been detected.");
    }

    _window.setFramerateLimit(144);
    _window.setMouseCursorVisible(false);

    _pageId = PageId::MENU_PAGE;

    createPages();

    int ret = EXIT_SUCCESS;

    while (_window.isOpen() && !_client.closed)
    {
        _window.clear();

        _event = sf::Event();
        if (_window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
            {
                _window.close();
                continue;
            }
            try
            {
                if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Escape)
                    _pageId = PageId::MENU_PAGE;
                if ((ret = _pages[_pageId - 1]->compute(_window, _event, _client)) != EXIT_SUCCESS)
                {
                    if (ret == EXIT_FAILURE)
                    {
                        _window.close();
                        continue;
                    }
                    _pageId = PageId(ret);
                }
            } catch (const std::exception & e) {
                std::cerr << "Compute Error : " << e.what() << std::endl;
            }
        }

        playingMusic();

        try {
            if (_pages[_pageId - 1]->draw(_window, _event, _client) == EXIT_FAILURE)
            {
                _window.close();
                continue;
            }
        } catch (const std::exception & e) {
            std::cerr << "Draw Error : " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        _window.display();
    }
    _client.closed = true;
    return EXIT_SUCCESS;
}