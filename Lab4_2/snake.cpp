#include "snake.h"

#include <QObject>
#include <QPainter>
#include <QTime>
#include <QPushButton>
#include <QThread>
#include <QWidget>
#include <QStyleFactory>
#include <QLabel>

snake::snake(QWidget *parent)
    : QMainWindow(parent)
{
    resize(WIDTH+230, HEIGHT);
    QPushButton *pb1 = new QPushButton("Play/Pause", this),
            *pb2 = new QPushButton("Restart", this);
    pb1->setGeometry(405, 90, 80, 25);
    pb2->setGeometry(405, 125, 80, 25);
    QObject::connect(pb1, SIGNAL(clicked()), SLOT(play_pause()));
    QObject::connect(pb2, SIGNAL(clicked()), SLOT(restart()));

    rightDirection = true;
    leftDirection = false;
    downDirection = false;
    upDirection = false;
    inGame = true;

    LoadImage();
    InitGame();
}

snake::~snake()
{
}

void snake::LoadImage()
{
    head_img.load("C:/Users/gutro/Desktop/GIT/labs/Lab4_2/Source/head.png");
    tail_img.load("C:/Users/gutro/Desktop/GIT/labs/Lab4_2/Source/tail.png");
    apple_img.load("C:/Users/gutro/Desktop/GIT/labs/Lab4_2/Source/apple1.png");
    wall_img.load("C:/Users/gutro/Desktop/GIT/labs/Lab4_2/Source/wall.png");
    big_wall_img.load("C:/Users/gutro/Desktop/GIT/labs/Lab4_2/Source/bigWall.png");
    backGround.load("C:/Users/gutro/Desktop/GIT/labs/Lab4_2/Source/backGround");
}

void snake::InitGame()
{
    setFocus();
    dots = 3;
    for (int i=0; i<dots;i++)
    {
        dot[i].setX(50 - i*10);
        dot[i].setY(50);
    }
    LocateWall();
    LocateApple();
    timerID = startTimer(DELAY);
}

void snake::LocateApple()
{
    QTime time = QTime::currentTime();
    srand ((uint)time.msec());

    apple.setX((rand() % RAND_POS) * SIZE_DOTS);
    apple.setY((rand() % RAND_POS) * SIZE_DOTS);
    for (int i=0; i<dots; i++)
    {
        if (apple.x() == dot[i].x() && apple.y() == dot[i].y())
        {
            apple.setX((rand() % RAND_POS) * SIZE_DOTS);
            apple.setY((rand() % RAND_POS) * SIZE_DOTS);
        }
    }
    for (int i=0; i<7; i++)
    {
        if ((apple.x() == wall[i].x() && apple.y() == wall[i].y()) ||
                ( apple.x() == big_wall[i].x() && apple.y() == big_wall[i].y()) ||
                (apple.x() == big_wall[i].x()+10 && apple.y() == big_wall[i].y()))
        {
            apple.setX((rand() % RAND_POS) * SIZE_DOTS);
            apple.setY((rand() % RAND_POS) * SIZE_DOTS);
        }
    }
}

void snake::LocateWall()
{
    for (int i=0; i<7; i++)
    {
        wall[i].setX((rand() % RAND_POS) * SIZE_DOTS);
        wall[i].setY((rand() % RAND_POS) * SIZE_DOTS);
        big_wall[i].setX((rand() % RAND_POS) * SIZE_DOTS);
        big_wall[i].setY((rand() % RAND_POS) * SIZE_DOTS);

    }
}

void snake::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    Drawing();
}

void snake::LevelUp()
{
    level = level + 5;
    killTimer(timerID);
    timerID = startTimer(DELAY-level);
}

void snake::Drawing()
{
    QPainter qp(this);
    QString count = QString::number(dots-1),
            control_message1 = "Control with the arrows",
            DELAYSTR = "LVL = " + QString::number(level/5);
    QFont font("Courier", 7, QFont::DemiBold);

    qp.setPen(QColor(Qt::black));
    qp.setFont(font);
    qp.drawText(405, 45, "SCORE:");
    qp.drawText(460, 45, count);
    qp.drawText(405, 15, control_message1);
    qp.drawText(405, 60, DELAYSTR);
    qp.drawLine(400, 0, 400, 400);
    qp.drawImage(0, 0, backGround);

    if (inGame)
    {
        qp.drawImage(apple.x(),(apple.y()-4), apple_img);
        for (int i=0; i<7; i++)
        {
            qp.drawImage(wall[i].x(), wall[i].y(), wall_img);
            qp.drawImage(big_wall[i].x(), big_wall[i].y(), big_wall_img);
        }

        for (int i= 0; i<dots; i++)
        {
            if (i==0)
            {
                qp.drawImage(dot[i].x(), dot[i].y(), head_img);
            }
            else {
                qp.drawImage(dot[i].x(), dot[i].y(), tail_img);
            }
        }
    }
    else {
        GameOver(qp);
    }
}

void snake::GameOver(QPainter &qp)
{
    QString end_message = "GAME OVER!";
    QFont font("Courier", 20, QFont::DemiBold);

    qp.setPen(QColor(Qt::blue));
    qp.setFont(font);

    qp.drawText(10, 45, end_message);
}

void snake::CheckApple()
{
    if (dot[0].x() == apple.x() && dot[0].y() == apple.y())
    {
        dots++;
        if (dots < 48 && dots%2==0) { LevelUp(); }
        LocateApple();
    }
}

void snake::Move()
{
    for (int i= dots; i>0; i--)
    {
        dot[i].setX(dot[i-1].x());
        dot[i].setY(dot[i-1].y());
    }
    if (rightDirection) {dot[0].setX(dot[0].x()+SIZE_DOTS);}
    if (leftDirection) {dot[0].setX(dot[0].x()-SIZE_DOTS);}
    if (downDirection) {dot[0].setY(dot[0].y()+SIZE_DOTS);}
    if (upDirection) {dot[0].setY(dot[0].y()-SIZE_DOTS);}
}

void snake::CheckCollision()
{
    for (int i=dots; i>0; i--)
    {
        if (dots>=4 && (dot[0].x() == dot[i].x() && dot[0].y() == dot[i].y()))
        {
            inGame = false;
        }
    }
    if (dot[0].y() > HEIGHT) {inGame = false;}
    if (dot[0].y() < 0) {inGame = false;}
    if (dot[0].x() >= WIDTH) {inGame = false;}
    if (dot[0].x() < 0) {inGame = false;}
    for (int i=0; i<7; i++)
    {
        if ((dot[0].x() == wall[i].x() && dot[0].y() == wall[i].y()) ||
                ((dot[0].x() == big_wall[i].x() && dot[0].y() == big_wall[i].y()) || (dot[0].x() == (big_wall[i].x()+10) && dot[0].y() == big_wall[i].y())))
        {
            inGame = false;
            break;
        }
    }

    if (!inGame) {
        killTimer(timerID);
        level =0;
    }
}

void snake::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (inGame)
    {
        CheckApple();
        CheckCollision();
        Move();
    }
    repaint();
}

void snake::keyPressEvent(QKeyEvent *event)
{
    setFocus();
    int key = event->key();
    if (key == Qt::Key_Left && !rightDirection)
    {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }
    if (key == Qt::Key_Right && !leftDirection)
    {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }
    if (key == Qt::Key_Up && !downDirection)
    {
        upDirection = true;
        leftDirection = false;
        rightDirection = false;
    }
    if (key == Qt::Key_Down && !upDirection)
    {
        downDirection = true;
        leftDirection = false;
        rightDirection = false;
    }
    clearFocus();
    QWidget::keyPressEvent(event);
}

void snake::play_pause()
{
    setFocus();
    static bool pause_flag = false;
    if (!pause_flag && inGame)
    {
        killTimer(timerID);
        pause_flag = true;
    }
    else if (pause_flag && inGame){
        timerID = startTimer(DELAY - level);
        pause_flag = false;
    }
    clearFocus();
}

void snake::restart()
{
    setFocus();
    if (!inGame)
    {
        inGame =true;
        rightDirection = true;
        leftDirection = false;
        downDirection = false;
        upDirection = false;

        InitGame();
        Drawing();
        repaint();
    }
    clearFocus();
}





