#include "dialog.h"
#include "ui_dialog.h"
#include "universecomposite.h"
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QTimeLine>
#include <iostream>
#include <QGraphicsView>


#define WIDTH 800
#define HEIGHT 800

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_width(WIDTH)
    , m_height(HEIGHT)
    , m_paused(false)
    , m_renderZodiacs(true)
    , m_renderLabels(true)
    , m_timestamp(0)
    , m_config(Config::getInstance())
{
    m_config->read("config.txt");
    m_universe = m_config->parseUniverseBlocks();
    m_zodiacs = m_config->parseZodiacBlocks();
    m_universe->convertRelativeToAbsolute(0,0,0,0);

    //set backdrop to black
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    //make the window appear
    ui->setupUi(this);
    this->resize(m_width, m_height);

    //create the buttons
    m_buttonPause = new QPushButton("Pause", this);
    m_buttonZodiacs = new QPushButton("Zodiacs", this);
    m_buttonLabels = new QPushButton("Labels", this);
    m_buttonAccelerate = new QPushButton("Accelerate", this);
    m_buttonDecelerate = new QPushButton("Decelerate", this);
    m_centre = new QPushButton("Centre View", this);
    m_buttonDisplayInfo = new QPushButton("Display bodies", this);
    m_allObjects = new QPushButton("View all planets", this);

    m_buttonPause->setGeometry(QRect(QPoint(0, 0), QSize(100, 50)));
    m_buttonZodiacs->setGeometry(QRect(QPoint(100, 0), QSize(100, 50)));
    m_buttonLabels->setGeometry(QRect(QPoint(200, 0), QSize(100, 50)));
    m_buttonAccelerate->setGeometry(QRect(QPoint(300, 0), QSize(100, 50)));
    m_buttonDecelerate->setGeometry(QRect(QPoint(400, 0), QSize(100, 50)));
    m_centre->setGeometry(QRect(QPoint(500, 0), QSize(100, 50)));
    m_buttonDisplayInfo->setGeometry(QRect(QPoint(600,0), QSize(100, 50)));
    m_allObjects->setGeometry(QRect(QPoint(700,0), QSize(100, 50)));

    connect(m_buttonAccelerate, SIGNAL(released()), this, SLOT(toggleAccelerate()));
    connect(m_buttonDecelerate, SIGNAL(released()), this, SLOT(toggleDecelerate()));
    connect(m_buttonPause, SIGNAL(released()), this, SLOT(togglePause()));
    connect(m_buttonZodiacs, SIGNAL(released()), this, SLOT(toggleZodiacs()));
    connect(m_buttonLabels, SIGNAL(released()), this, SLOT(toggleLabels()));
    connect(m_centre, SIGNAL(released()), this, SLOT(centreView()));
    connect(m_buttonDisplayInfo, SIGNAL(released()), this, SLOT(displayInformation()));
    connect(m_allObjects, SIGNAL(released()), this, SLOT(viewAll()));

    //setup timer
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    pause(false);
}

Dialog::~Dialog()
{
    delete ui;
    delete m_timer;
    delete m_buttonPause;
    delete m_buttonZodiacs;
    delete m_buttonLabels;
    delete m_universe;
    delete m_zodiacs;
    delete m_buttonAccelerate;
    delete m_buttonDecelerate;
    delete m_centre;
    delete m_buttonDisplayInfo;
    delete m_allObjects;
}

void Dialog::toggleZodiacs()
{
    m_renderZodiacs = !m_renderZodiacs;
}

void Dialog::toggleLabels()
{
    m_renderLabels = !m_renderLabels;
}

void Dialog::togglePause()
{
    pause(!m_paused);
}

void Dialog::toggleAccelerate()
{
    //timer cant have negative intervals
    if (m_speed != 0)
    {
        m_speed = m_speed - 250;
    }
    m_timer->start((m_speed) / m_config->getFramesPerSecond());

    std::cout << m_speed << std::endl;

}

void Dialog::toggleDecelerate()
{
    //speed can always be increased
    m_speed = m_speed + 250;
    m_timer->start((m_speed) / m_config->getFramesPerSecond());

    std::cout << m_speed << std::endl;

}

void Dialog::pause(bool pause)
{
    if(pause)
    {
        m_timer->stop();
        m_paused = true;
    }
    else
    {
        m_timer->start(1000 / m_config->getFramesPerSecond());
        m_paused = false;
    }
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Space:
        pause(!m_paused);
        return;
    case Qt::Key_W:
        m_key = 'W';
        return;
    case Qt::Key_A:
        m_key = 'A';
        return;
    case Qt::Key_S:
        m_key = 'S';
        return;
    case Qt::Key_D:
        m_key = 'D';
        return;
    default:
        return;
    }
}

void Dialog::nextFrame()
{
    //reset the forces stored in every object to 0
    m_universe->resetForces();

    //update the forces acting on every object in the universe,
    //from every object in the universe
    m_universe->addAttractionFrom(*m_universe);

    //update the velocity and position of every object in the universe
    int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
    for(int i = 0; i < m_config->getPhysicsStepSize(); i += step)
    {
        //update physics
        m_universe->updatePosition(step);
        //some time has passed
        m_timestamp += step;
    }

    //update the window (this will trigger paintEvent)
    update();
}

void Dialog::paintEvent(QPaintEvent *event)
{
    //suppress 'unused variable' warning
    Q_UNUSED(event);

    //redraw the universe
    m_painter.begin(this);
    //offset the painter so (0,0) is the center of the window
    switch (m_key)
    {
    case 'W':
        m_height = m_height + 10;
        m_painter.translate(m_width/2, m_height/2);
        m_key = '\0';
        break;
    case 'S':
        m_height = m_height - 10;
        m_painter.translate(m_width/2, m_height/2);
        m_key = '\0';
        break;
    case 'A':
        m_width = m_width + 10;
        m_painter.translate(m_width/2, m_height/2);
        m_key = '\0';
        break;
    case 'D':
        m_width = m_width - 10;
        m_painter.translate(m_width/2, m_height/2);
        m_key = '\0';
        break;
    case '/':
        m_width = WIDTH;
        m_height = HEIGHT;
        m_painter.translate(m_width/2, m_height/2);
        m_key = '\0';
        break;
    default:
        m_painter.translate(m_width/2, m_height/2);
        break;
    }

    if (m_scaleFlag == true)
    {
        /* ignore these 2 values. we need to change these 2 x and y
           values to utilise the furthest 2 objects we get retured from our
           visitor search algorithm we run on our universe.
           problem: how do we do this? just plugging in the x and y values wont work
           for scaling reasons. we need to find some sort of way to process both these
           coordinates into 1 x value and 1 y value s.t. pressing the "View All Planets"
           button will show the 2 furthest planets on the boarder and all other planets in between */
        m_painter.scale(m_sx,m_sy);
        m_scaleFlag = false;
    } else {
        //Scales the coordinate system by (sx, sy).
        m_painter.scale(m_scale, m_scale);
    }
    if(m_renderZodiacs)
    {
        for(auto zodiac : *m_zodiacs)
        {
            zodiac.render(m_painter);
        }
    }

    m_universe->render(m_painter);

    if(m_renderLabels)
    {
        m_universe->renderLabel(m_painter);
    }
    m_painter.end();
}

void Dialog::wheelEvent (QWheelEvent * event )
{
        m_scale+=(event->delta()/120); //or use any other step for zooming
        if (m_scale == 0){ //scale = 0 will turn screen black
            m_scale = 1;
        }
//        std::cout << m_scale << std::endl;
}

void Dialog::displayInformation()
{
    VisitorDisplay dv;

    m_universe->accept(dv);


}
void Dialog::centreView ()
{
    m_key = '/';
}

void Dialog::viewAll()
{
    m_scaleFlag = true;
    m_sx = -3.74027e+12/m_scale;
    m_sy = -1.83966e+12/m_scale;
    //m_scale = 3.74027e+12; //or use any other step for zooming
//    std::cout << m_scale << std::endl;
}
