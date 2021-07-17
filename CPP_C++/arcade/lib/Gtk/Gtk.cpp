/*
** EPITECH PROJECT, 2019
** Gtk.cpp
** File description:
** Created by etienne,
*/

#include <iostream>
#include "Gtk.hpp"

Gtk::Gtk(ArcadeContent &arcade)
: ADisplayModule(arcade)
{
    std::cerr << "Error: Gtk is not finished" << std::endl;
    char **argv = (char**)malloc(sizeof(char*) * 1);
    argv[0] = strdup("./a.out");
    int argc = 1;
    gtk_init(&argc, &argv);
    _window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_widget_add_events(_window, GDK_KEY_PRESS_MASK);
    g_signal_connect (G_OBJECT (_window), "key_press_event", G_CALLBACK(Gtk::_keypressEvent), NULL);
    g_signal_connect(G_OBJECT(_window), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_title(GTK_WINDOW(_window), "Arcade");
    gtk_window_set_default_size(GTK_WINDOW(_window), 1600, 960);
    //gtk_window_set_icon_from_file(GTK_WINDOW(_window), "filename", nullptr);

    gtk_widget_show(_window);
    gtk_main();
}

Gtk::~Gtk()
{
    gtk_main_quit();
}

void Gtk::updateEvent()
{
    if (isKeyPressed()) {
        releasePressedKey();
        return;
    }
    _input = _keypressEvent(nullptr, nullptr, nullptr);
    if (_input == 'x' || _input == 'X')
        turnOff();
    else if (/*_input == GTK_Key ||*/ _input == 'z' || _input == 'Z')
        moveUp();
    else if (/*_input == KEY_LEFT ||*/ _input == 'q' || _input == 'Q')
        moveLeft();
    else if (/*_input == KEY_DOWN ||*/ _input == 's' || _input == 'S')
        moveDown();
    else if (/*_input == KEY_RIGHT ||*/ _input == 'd' || _input == 'D')
        moveRight();
    else if (_input == ' ')
        validate();
    else if (_input == 'b' || _input == 'B')
        cancel();
    else if (_input == 'r' || _input == 'R')
        restart();
    else if (_input == 'p' || _input == 'P')
        backToMenu();
    else if (_input == '1' || _input == '&')
        prevGraph();
    else if (_input == '2')
        nextGraph();
    else if (_input == '3' || _input == '"')
        prevGame();
    else if (_input == '4' || _input == '\'')
        nextGame();
    else if (isKeyPressed())
        releasePressedKey();
    else if (isKeyReleased())
        noEvent();
    _input = 0;

}

void Gtk::setTexture(const std::string &pFilepath)
{
    ParserArcadeFileTexture parser(pFilepath);
    std::vector<char> lChar = parser.getSymbols();

    for (auto character : lChar)
    {
        std::string filepath = parser.getFilePath(character);
        _mGtkSprites.insert(std::pair<char, GtkWidget *>(character, gtk_image_new_from_file(filepath.c_str())));
    }
}

void Gtk::display()
{
}

unsigned int Gtk::_keypressEvent(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    static unsigned int input = 0;
    if (event != nullptr)
        input = event->keyval;
    return (input);
}

Gtk *getDisplayModule(ArcadeContent &ac)
{
    return new Gtk(ac);
}
