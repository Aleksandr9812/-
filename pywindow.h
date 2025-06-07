#ifndef PYWINDOW_H
#define PYWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QPushButton>

using namespace std;

namespace Ui {
class PyWindow;
}

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QWidget* parrent = 0):
        QPushButton(parrent){

    }
    void setPosition(int);
    int number;
    int x;
    int y;
};

class PyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PyWindow(QWidget *parent = 0);
    ~PyWindow();

private:
    void shuffle();
    bool isWin();
    vector<vector<MyButton*> > buttons;
    Ui::PyWindow *ui;
private slots:
    void click_on_button();
};

#endif // PYWINDOW_H
