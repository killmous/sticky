#include <ctime>
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <random>
#include <unistd.h>
#include <vector>
#include "sticky.h"

using namespace std;

int main(int argc, char **argv) {
    srand(time(NULL));

    int c;
    while((c = getopt(argc, argv, "h::")) != -1) {
        switch(c) {
        case 'h':
            std::cout <<
R"(Usage: sticky [-h] [FILE ...]

Simple configurable desktop sticky note program.

Propositional Arguments:
    FILE        text file to be displayed

Optional Arguments:
    -h          show this help message and exit
)";
            return 0;
        default:
            abort();
        }
    }

    QApplication app(argc, argv);

    std::vector<Sticky*> files;
    for(int i = optind; i < argc; ++i) {
        QFile file(argv[i]);
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream fstream(&file);
        files.push_back(new Sticky(fstream.readAll()));
    }

    if(files.empty()) {
        files.push_back(new Sticky());
    }
    for(Sticky* sticky : files) {
        sticky->show();
    }

    return app.exec();
}