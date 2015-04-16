#ifndef __STICKY_H__
#define __STICKY_H__

#include <QEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>
#include <QSizeGrip>
#include <QPlainTextEdit>
#include <QWidget>
#include <string>
#include "decoration.h"

class Sticky : public QMainWindow {
    Q_OBJECT
public:
    Sticky(const QString file = 0);
    Sticky(const Sticky& sticky);
    ~Sticky();
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    std::string getStylesheet(int rand);
    Decoration* decoration;
    QSizeGrip* grip;
    QPlainTextEdit* text;
    QWidget* window;

    QPoint _mpos;
    bool dragging;
};

#endif