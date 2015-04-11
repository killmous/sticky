#include "sticky.h"

#include <QGraphicsDropShadowEffect>
#include <QGridLayout>

using namespace std;

Sticky::Sticky() {
    window = new QWidget(this);

    decoration = new Decoration(window);
    decoration->setFixedHeight(20);
    text = new QTextEdit(window);
    grip = new QSizeGrip(window);

    QGridLayout* layout = new QGridLayout(window);
    layout->addWidget(decoration, 0, 0);
    layout->addWidget(text, 1, 0);
    layout->addWidget(grip, 1, 0, Qt::AlignBottom | Qt::AlignRight);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    setStyleSheet(R"(
* {
    background-color: #D5DB5A;
}

QPushButton {
    font: 18px;
    border: none;
}

QPushButton:hover {
    font: bold;
}

QPushButton:focus {
    outline: none;
}

QSizeGrip {
    background-color: #E1EB31;
}

QTextEdit {
    border: none;
    background-color: #E1EB31;
    font: 24px "Special Elite";
}
    )");

    setCentralWidget(window);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground); //enable MainWindow to be transparent
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(5);
    window->setGraphicsEffect(effect);

    dragging = false;
}

Sticky::~Sticky() {
    delete decoration;
    delete text;
    delete window;
}

void Sticky::mousePressEvent(QMouseEvent* event){
    QWidget* widget;
    if((widget = QWidget::childAt(event->pos())) && widget->inherits("Decoration")) {
        _mpos = event->pos();
        dragging = true;
    }
}

void Sticky::mouseReleaseEvent(QMouseEvent* event) {
    dragging = false;
}

void Sticky::mouseMoveEvent(QMouseEvent* event){
    if(dragging && event->buttons() && Qt::LeftButton) {
        QPoint diff = event->pos() - _mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}