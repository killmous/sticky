#include <ctime>
#include <QApplication>
#include <random>
#include "sticky.h"

using namespace std;

int main(int argc, char **argv) {
    srand(time(NULL));
    QApplication app(argc, argv);

    Sticky sticky;
    sticky.show();

    return app.exec();
}