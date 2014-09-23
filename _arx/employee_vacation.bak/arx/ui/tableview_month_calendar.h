//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 29-01-2013
//		Date update	: 29-01-2013
//		Comment		:
//=============================================================================
#ifndef __EV_TABLEVIEW_MONTH_CALENDAR_H__
#define __EV_TABLEVIEW_MONTH_CALENDAR_H__

#include <QtGui/QTableView>

namespace rele_auto
{

namespace employee_vacation
{

//#############################################################################
//			class tableview_month_calendar
//#############################################################################
    class tableview_month_calendar : public QTableView
    {
    Q_OBJECT
    //=========================================================================
    //		CONSTRUCTORS/DESTRUCTOR
    //=========================================================================
    private:
        tableview_month_calendar( const tableview_month_calendar &rhs );

    public:
        explicit tableview_month_calendar( QWidget *parent = 0 );
        virtual ~tableview_month_calendar( );

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
        tableview_month_calendar& operator=( const tableview_month_calendar &rhs );

    public:

    //=========================================================================
    //			FIELDS
    //=========================================================================
    private:

    };//class tableview_month_calendar
//#############################################################################
//-----------------------------------------------------------------------------

}//namespace employee_vacation

}//namespace rele_auto
#endif // __EV_TABLEVIEW_MONTH_CALENDAR_H__
