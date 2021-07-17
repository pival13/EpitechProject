#ifndef POPUPBINARY_H
#define POPUPBINARY_H

#include <QMainWindow>
#include <QString>
#include <QMovie>
#include <QListWidget>

class UIHandler;

namespace Ui {
class PopupBinary;
}

class PopupBinary : public QMainWindow
{
    Q_OBJECT

public:

    explicit PopupBinary(UIHandler &handl, QWidget *parent = 0);
    ~PopupBinary();

    void preparePopUp(const std::string &msg, const std::function<void()> &actionOk, const std::function<void()> &actionKo);

public slots:

private:
    Ui::PopupBinary *ui;

    std::function<void()> _actionOk;
    std::function<void()> _actionKo;

    UIHandler &handler;
};

#endif // POPUPBINARY_H