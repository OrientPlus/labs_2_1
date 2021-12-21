#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QEvent>


class snake : public QMainWindow
{
    Q_OBJECT

public:
    snake(QWidget *parent = nullptr);
    ~snake();
protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    QImage head_img, tail_img, apple_img, wall_img, big_wall_img, backGround;

    static const int HEIGHT = 400,
    WIDTH = 400,
    DOTS = 1600,
    SIZE_DOTS = 10,
    DELAY = 150,
    RAND_POS = 31;

    int dots,
    timerID,
    temp =1, level = 0;

    QPoint apple, wall[7], big_wall[7];
    QPoint dot[DOTS];

    bool rightDirection,
    leftDirection,
    upDirection,
    downDirection,
    inGame,
    pause_flag=false;

    void LoadImage();
    void InitGame();
    void LocateApple();
    void CheckApple();
    void CheckCollision();
    void Move();
    void Drawing();
    void GameOver(QPainter &);
    void RestartGame();
    void LevelUp();
    void LocateWall();
public slots:
      void play_pause();
      void restart();



};
#endif // SNAKE_H
