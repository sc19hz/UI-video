/**
 * @author Giant_Salted_Fish
 */

#include <QApplication>

#include "WinTomeo.h"

int main(int argc, char *argv[])
{
    // Static Qt Application
    QApplication app(argc, argv);

    if(argc < 2)
    {
        QMessageBox::information(
            nullptr,
            "Info",
            "Resource dirent path needed for launch!"
                "Please set it in run argument",
            QMessageBox::Ok
        );
        return 0;
    }

    // interactive mode - run the regular superclass
    WinTomeo window(argv[1]);
    window.show();

    // wait for the app to terminate
    return app.exec();
}
