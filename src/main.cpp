#include <QApplication>
#include "sticky.h"

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Sticky sticky;
    sticky.show();

    return app.exec();
}