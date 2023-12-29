#include "w_main.hpp"

#include <QApplication>

#include <iostream>


int main(int argc, char* argv[])
{

    try {
        QApplication app(argc, argv);

        w_main window;

        window.setWindowTitle("qt Test");
        window.show();

        return app.exec();
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }
}
