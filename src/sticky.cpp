#include "sticky.h"

#include <array>
#include <QDebug>
#include <QGridLayout>
#include <random>
#include <sstream>
#include <tuple>

const std::array<std::tuple<const char*, const char*>, 3> colors =
    {std::make_tuple<const char*, const char*>("#D5DB5A", "#E1EB31"),
     std::make_tuple<const char*, const char*>("#53B3B5", "#68D7D9"),
     std::make_tuple<const char*, const char*>("#D90D8B", "#FC30AE")};

Sticky::Sticky(const QString file) {
    window = new QWidget(this);
    decoration = new Decoration(window);
    decoration->setFixedHeight(20);
    text = new QPlainTextEdit(window);
    text->setPlainText(file);
    grip = new QSizeGrip(window);

    QGridLayout* layout = new QGridLayout(window);
    layout->addWidget(decoration, 0, 0);
    layout->addWidget(text, 1, 0);
    layout->addWidget(grip, 1, 0, Qt::AlignBottom | Qt::AlignRight);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    setStyleSheet(getStylesheet(rand()).c_str());

    setCentralWidget(window);
    setWindowFlags(Qt::FramelessWindowHint);

    dragging = false;
}

Sticky::Sticky(const Sticky& sticky)
    : decoration(sticky.decoration),
      text(sticky.text),
      grip(sticky.grip),
      window(sticky.window) {}

Sticky::~Sticky() {
    delete decoration;
    delete text;
    delete grip;
    delete window;
}

void Sticky::mousePressEvent(QMouseEvent* event){
    QWidget* widget;
    if((widget = QWidget::childAt(event->pos())) && widget->inherits("Decoration")) {
        _mpos = event->pos();
        dragging = true;
    }
}

void Sticky::mouseReleaseEvent(QMouseEvent*) {
    dragging = false;
}

void Sticky::mouseMoveEvent(QMouseEvent* event){
    if(dragging && event->buttons() && Qt::LeftButton) {
        QPoint diff = event->pos() - _mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

std::string Sticky::getStylesheet(int rand) {
    int i = rand % colors.size();
    std::ostringstream ss;
    ss << R"(
* {
    background-color: )" << std::get<0>(colors[i]) << R"(;
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
    background-color: )" << std::get<1>(colors[i]) << R"(;
}

QPlainTextEdit {
    border: none;
    background-color: )" << std::get<1>(colors[i]) << R"(;
    font: 24px "Special Elite";
}
    )";
    return ss.str();
}