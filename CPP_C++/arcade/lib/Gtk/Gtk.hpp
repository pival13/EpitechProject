/*
** EPITECH PROJECT, 2019
** Gtk.hpp
** File description:
** Created by etienne,
*/

#ifndef OOP_ARCADE_2019_GTK_HPP
#define OOP_ARCADE_2019_GTK_HPP


#include "ADisplayModule.hpp"
#include <gtk/gtk.h>

class Gtk: public ADisplayModule {
public:
    Gtk(ArcadeContent &ac);
    ~Gtk();

    void updateEvent() override;
    void setTexture(const std::string & fileName) override ;
    void display() override;

private:
    static unsigned int _keypressEvent(GtkWidget *widget, GdkEventKey *event, gpointer data);

    std::map<char, GtkWidget *> _mGtkSprites;
    GtkApplication *_app;
    GtkWidget *_window;
    unsigned int _input;
};

extern "C" Gtk *getDisplayModule(ArcadeContent &);

#endif //OOP_ARCADE_2019_GTK_HPP
