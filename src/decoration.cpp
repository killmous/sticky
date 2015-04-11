#include "decoration.h"
#include "sticky.h"

#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>

Decoration::Decoration(QWidget* parent)
    : QWidget(parent) {
    add = new QPushButton("+", parent);
    add->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    add->setVisible(false);
    quit = new QPushButton("X", parent);
    quit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    quit->setVisible(false);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(add, 0, Qt::AlignLeft);
    layout->addWidget(quit, 0, Qt::AlignRight);
    layout->setContentsMargins(4, 0, 4, 0);

    setLayout(layout);
    connect(quit, &QPushButton::clicked,
            (const QWidget*) parent->parent(), &QWidget::close);
    connect(add, &QPushButton::clicked,
            this, &Decoration::on_add_clicked);
}

Decoration::~Decoration() {
    delete add;
    delete quit;
}

void Decoration::enterEvent(QEvent*) {
    add->setVisible(true);
    quit->setVisible(true);
}

void Decoration::leaveEvent(QEvent*) {
    add->setVisible(false);
    quit->setVisible(false);
}

void Decoration::on_add_clicked() {
    Sticky* sticky = new Sticky();
    sticky->show();
}