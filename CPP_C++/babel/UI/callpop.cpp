#include "callpop.h"
#include "UIHandler.hpp"
#include "ui_callpop.h"

CallPopUp::CallPopUp(UIHandler &handl, Babel::Audio &_audio, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CallPopUp)
    , handler(handl)
    , audio(_audio)
{
    ui->setupUi(this);
    ui->VolumeSlider->setMaximum(200);
    ui->VolumeSlider->setMinimum(0);

    QObject::connect(ui->EndcallButton, &QPushButton::clicked, this, [this]() {
        if (_actionEnd) _actionEnd();
        hide();
    });
    QObject::connect(ui->menuOutPut, SIGNAL(triggered(QAction *)), this, SLOT(insertOutputsDevices()));
    QObject::connect(ui->VolumeSlider, &QSlider::valueChanged, this, [this](int v) { audio.setOutputVolume(float(v) / 100); });
}

CallPopUp::~CallPopUp()
{
    delete ui;
}

void CallPopUp::preparePopUp(const std::function<void()> &endCallFunction)
{
    _actionEnd = endCallFunction;
    ui->VolumeSlider->setSliderPosition(audio.getOutputVolume() * 100);
}

void CallPopUp::insertOutputsDevices()
{
    std::list<std::string> devices = audio.getOutputDevices();

    std::cout << devices.size() << std::endl;
    ui->menuOutPut->clear();
    for (const std::string &d : devices)
        ui->menuOutPut->addAction(QString(d.data()), [this, &d]() { audio.setOutputDevice(d); });
}
