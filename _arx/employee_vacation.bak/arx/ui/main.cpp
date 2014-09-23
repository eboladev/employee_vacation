#include <QApplication>


//#include "widget_year_calendar.h"
//#include "calendar.h"
#include "tableview_month_calendar.h"
#include "data_model_month.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //rele_auto::employee_vacation::widget_year_calendar w;
    rele_auto::employee_vacation::tableview_month_calendar w;
    rele_auto::employee_vacation::data_model_month dm;
    w.setModel(&dm);
    w.show();

    //rele_auto::employee_vacation::calendar calendar;
    //calendar.show();

    //Widget w;
    //w.show();
    
    return a.exec();
}
