#include <QApplication>
#include <QDebug>

#include <QVBoxLayout>

#include "application.h"
#include "main_window.h"

namespace ra_ev = rele_auto::employee_vacation;

int main(int argc, char *argv[])
{
    ra_ev::application a(argc, argv);

    ra_ev::main_window w;
    w.show( );

    return a.exec();
}
