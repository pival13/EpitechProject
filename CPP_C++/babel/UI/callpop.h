#ifndef CALLPOPUP_H
#define CALLPOPUP_H

#include <QMainWindow>
#include <QString>
#include <QMovie>
#include <QListWidget>
#include <functional>

#include "../audio/Audio.hpp"

class UIHandler;

namespace Ui {
class CallPopUp;
}

class CallPopUp : public QMainWindow
{
    Q_OBJECT

public:

    explicit CallPopUp(UIHandler &handl, Babel::Audio &audio, QWidget *parent = 0);
    ~CallPopUp();

    void preparePopUp(const std::function<void()> &endCallFunction);

public slots:
    void insertOutputsDevices();

private:
    Ui::CallPopUp *ui;

    Babel::Audio &audio;
    UIHandler &handler;

    std::function<void()> _actionEnd;
};

#endif // CALLPOPUP_H