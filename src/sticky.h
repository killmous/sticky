#ifndef __STICKY_H__
#define __STICKY_H__

#include <QEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>
#include <QSizeGrip>
#include <QTextEdit>
#include <QWidget>
#include "decoration.h"

class Sticky : public QMainWindow {
    Q_OBJECT
public:
    Sticky();
    ~Sticky();
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    std::string getStylesheet(int rand);
    Decoration* decoration;
    QSizeGrip* grip;
    QTextEdit* text;
    QWidget* window;

    QPoint _mpos;
    bool dragging;
};

#endif