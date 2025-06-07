#include "pywindow.h"
#include "ui_pywindow.h"
#include <QString>
#include <QMessageBox>
//#include <random>
#include <time.h>

void MyButton::setPosition(int t){
    x = t / 4;
    y = t % 4;
}

PyWindow::PyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PyWindow)
{
    ui->setupUi(this);
    buttons = vector<vector<MyButton*> >(4);
    int t = 1;
    setFixedSize(400,400);
    for(int i = 0; i < 4; i++){
        buttons[i] = vector<MyButton*>(4);
        for(int j = 0; j < 4; j++){
            if(t == 16){
                buttons[i][j] = NULL;
                break;
            }
            else
                buttons[i][j] = new MyButton(this);
            //this->setParent(buttons[i][j]);
            //buttons[i][j]->setGeometry(100*j, 100*i, 100, 100);
            //buttons[i][j]->setFixedSize(QSize(100,100));
            QString text = QString::number(t);
            buttons[i][j]->number = t;
            buttons[i][j]->setText(text);
            buttons[i][j]->x = i;
            buttons[i][j]->y = j;
            buttons[i][j]->setVisible(true);
            connect(buttons[i][j], SIGNAL(clicked()), SLOT(click_on_button()));
            t++;
        }
    }
    shuffle();

}

PyWindow::~PyWindow()
{
    delete ui;
    for(int i = 0; i< 4;i++){
        for(int j = 0; j< 4;j++){
            delete buttons[i][j];
        }
    }
}

void PyWindow::click_on_button(){
    MyButton* button = static_cast< MyButton* >( sender() );
    if(button->x > 0 && buttons[button->x - 1][button->y] == NULL){
        buttons[button->x - 1][button->y] = button;
        buttons[button->x][button->y] = NULL;
        button->x--;
        button->setGeometry(100*button->y, 100*button->x, 100, 100);
        if(isWin()){
            QMessageBox::warning( this, "Title","You win!!", QMessageBox::Ok );
            shuffle();
        }
        return;
    }
    if(button->y > 0 && buttons[button->x][button->y - 1] == NULL){
        buttons[button->x][button->y - 1] = button;
        buttons[button->x][button->y] = NULL;
        button->y--;
        button->setGeometry(100*button->y, 100*button->x, 100, 100);
        if(isWin()){
            QMessageBox::warning( this, "Title","You win!!", QMessageBox::Ok );
            shuffle();
        }
        return;
    }
    if(button->x < 3 && buttons[button->x + 1][button->y] == NULL){
        buttons[button->x + 1][button->y] = button;
        buttons[button->x][button->y] = NULL;
        button->x++;
        button->setGeometry(100*button->y, 100*button->x, 100, 100);
        if(isWin()){
            QMessageBox::warning( this, "Title","You win!!", QMessageBox::Ok );
            shuffle();
        }
        return;
    }
    if(button->y < 3 && buttons[button->x][button->y + 1] == NULL){
        buttons[button->x][button->y + 1] = button;
        buttons[button->x][button->y] = NULL;
        button->y++;
        button->setGeometry(100*button->y, 100*button->x, 100, 100);
        if(isWin()){
            QMessageBox::warning( this, "Title","You win!!", QMessageBox::Ok );
            shuffle();
        }
        return;
    }
}

void PyWindow::shuffle(){
    for(int i = 0; i < 15; i++){
        srand(time(NULL));
        int j = rand() % 15;
        MyButton* t = buttons[j / 4][j % 4];
        buttons[j / 4][j % 4] = buttons[i / 4][i % 4];
        buttons[i / 4][i % 4] = t;
        if(buttons[j / 4][j % 4] != NULL)
            buttons[j / 4][j % 4]->setPosition(j);
        if(buttons[i / 4][i % 4] != NULL)
            buttons[i / 4][i % 4]->setPosition(i);
    }
    for(int i = 0; i < 4;i++){
        for(int j = 0; j< 4;j++){
            if(buttons[i][j] != NULL)
                buttons[i][j]->setGeometry(100*buttons[i][j]->y, 100*buttons[i][j]->x, 100, 100);
        }
    }
}

bool PyWindow::isWin(){
    int t = 1;
    for(int i = 0; i < 4;i++){
        for(int j = 0; j < 4;j++){
            if(t == 16 && buttons[i][j] == NULL)
                break;
            if(buttons[i][j] == NULL || buttons[i][j]->number != t)
                return false;
            t++;
        }
    }
    return true;
}

