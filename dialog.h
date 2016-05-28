#ifndef DIALOG_H
#define DIALOG_H

#include "config.h"
#include "universecomponent.h"
#include "zodiac.h"
#include "visitordisplay.h"
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <list>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    virtual ~Dialog();

private slots:
    //prepare the next frame, called by the timer
    void nextFrame();
    //toggle the simultation's pause state
    void togglePause();
    //toggle rendering of Zodiacs
    void toggleZodiacs();
    //toggle rendering of labels
    void toggleLabels();
    //pressed accelerate
    void toggleAccelerate();
    //pressed decelerate
    void toggleDecelerate();
    //display information for the planet that was clicked on
    void displayInformation();
    //centre view
    void centreView();


private:
    //method called when the window is being redrawn
    void paintEvent(QPaintEvent *event);
    //pause (or unpause) the simulation
    void pause(bool pause);
    //handle key presses
    void keyPressEvent(QKeyEvent *event);
    //handle mouse wheel
    void wheelEvent(QWheelEvent *);


private:
    Ui::Dialog* ui;
    QTimer* m_timer; //Timer object for triggering updates

    //buttons for UI
    QPushButton* m_buttonPause;
    QPushButton* m_buttonZodiacs;
    QPushButton* m_buttonLabels;

    //buttons for UI stage 3
    QPushButton* m_buttonAccelerate;
    QPushButton* m_buttonDecelerate;
    QPushButton* m_buttonDisplayInfo;
    QPushButton* m_centre;

    int m_speed = 1000;
    int m_numScheduledScalings = 0;
    qreal m_scale = 1;

    QPainter m_painter;
    char m_key;

    int m_width; //width of the window
    int m_height; //height of the window
    bool m_paused; //is the simulation paused?
    bool m_renderZodiacs; //should Zodiacs be rendered?
    bool m_renderLabels; //should labels be rendered?
    long m_timestamp; //simulation time since simulation start
    UniverseComponent* m_universe; //The universe
    std::list<Zodiac>* m_zodiacs; //Vector of zodiac lines
    Config* m_config; //the singleton config instance

};

#endif // DIALOG_H
