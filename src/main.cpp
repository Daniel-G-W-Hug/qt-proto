#include "w_gview.hpp"

#include <QApplication>
#include <QMainWindow>

#include <iostream>


int main(int argc, char* argv[])
{

    try {
        QApplication app(argc, argv);

        w_gview* gview = new w_gview;

        QMainWindow mainWindow;

        mainWindow.setWindowTitle("tr(graphicsview test)");
        mainWindow.setCentralWidget(gview);
        mainWindow.show();

        return app.exec();
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }
}
