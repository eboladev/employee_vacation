//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 28-01-2013
//		Date update	: 28-01-2013
//		Comment		:
//=============================================================================
#ifndef __EV_WIDGET_YEAR_CALENDAR_H__
#define __EV_WIDGET_YEAR_CALENDAR_H__

#include <QtGui/QWidget>
#include <QtCore/QVector>
#include "calendar.h"

namespace rele_auto
{

namespace employee_vacation
{

//#############################################################################
//			class widget_year_calendar
//#############################################################################
    class widget_year_calendar : public QWidget
    {
    Q_OBJECT
    //=========================================================================
    //		CONSTRUCTORS/DESTRUCTOR
    //=========================================================================
    private:
        widget_year_calendar( const widget_year_calendar &rhs );

    public:
        explicit widget_year_calendar( QWidget *parent = 0 );
        virtual ~widget_year_calendar( );

    //=========================================================================
    //		FUNCTIONS
    //=========================================================================
    private:
        void initialize( );

    public:

    //=========================================================================
    //		PROPERTIES
    //=========================================================================
    private:

    public:

    //=========================================================================
    //		OPERATORS
    //=========================================================================
    private:
        widget_year_calendar& operator=( const widget_year_calendar &rhs );

    public:

    //=========================================================================
    //			FIELDS
    //=========================================================================
    private:
        QVector<calendar*> _calendars;

    };//class widget_year_calendar
//#############################################################################
//-----------------------------------------------------------------------------

}//namespace employee_vacation

}//namespace rele_auto
#endif // __EV_WIDGET_YEAR_CALENDAR_H__
