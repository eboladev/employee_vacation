//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 29-01-2013
//		Date update	: 29-01-2013
//		Comment		:
//=============================================================================
#ifndef __EV_TABLEVIEW_YEAR_CALENDAR_H__
#define __EV_TABLEVIEW_YEAR_CALENDAR_H__

#include <QtGui/QTableView>

namespace rele_auto
{

namespace employee_vacation
{

//#############################################################################
//			class tableview_year_calendar
//#############################################################################
    class tableview_year_calendar : public QTableView
    {
    Q_OBJECT
    //=========================================================================
    //		CONSTRUCTORS/DESTRUCTOR
    //=========================================================================
    private:
        tableview_year_calendar( const tableview_year_calendar &rhs );

    public:
        explicit tableview_year_calendar( QWidget *parent = 0 );
        virtual ~tableview_year_calendar( );

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
        tableview_year_calendar& operator=( const tableview_year_calendar &rhs );

    public:

    //=========================================================================
    //			FIELDS
    //=========================================================================
    private:

    };//class tableview_year_calendar
//#############################################################################
//-----------------------------------------------------------------------------

}//namespace employee_vacation

}//namespace rele_auto
#endif // __EV_TABLEVIEW_YEAR_CALENDAR_H__
