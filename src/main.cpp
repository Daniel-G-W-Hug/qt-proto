#include "mainwindow.hpp"

#include <QApplication>

#include <iostream>


int main(int argc, char* argv[])
{

    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }
}
