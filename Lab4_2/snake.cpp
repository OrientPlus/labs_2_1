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
        x[i] = 50 - i*10;
        y[i] = 50;
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
        if (apple.x() == x[i] && apple.y() == y[i])
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
                qp.drawImage(x[i], y[i], head_img);
            }
            else {
                qp.drawImage(x[i], y[i], tail_img);
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
    if (x[0] == apple.x() && y[0] == apple.y())
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
        x[i] = x[i-1];
        y[i] = y[i-1];
    }
    if (rightDirection) {x[0] += SIZE_DOTS;}
    if (leftDirection) {x[0] -= SIZE_DOTS;}
    if (downDirection) {y[0] += SIZE_DOTS;}
    if (upDirection) {y[0] -= SIZE_DOTS;}
}

void snake::CheckCollision()
{
    for (int i=dots; i>0; i--)
    {
        if (dots>=4 && (x[0] == x[i] && y[0] == y[i]))
        {
            inGame = false;
        }
    }
    if (y[0] > HEIGHT) {inGame = false;}
    if (y[0] < 0) {inGame = false;}
    if (x[0] >= WIDTH) {inGame = false;}
    if (x[0] < 0) {inGame = false;}
    for (int i=0; i<7; i++)
    {
        if ((x[0] == wall[i].x() && y[0] == wall[i].y()) ||
                ((x[0] == big_wall[i].x() && y[0] == big_wall[i].y()) || (x[0] == (big_wall[i].x()+10) && y[0] == big_wall[i].y())))
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





