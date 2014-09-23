//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 28-01-2013
//		Date update	: 28-01-2013
//		Comment		:
//=============================================================================

#include <QtCore/QDate>
#include <QtCore/QLocale>
#include <QtGui/QGridLayout>

#include "widget_year_calendar.h"

namespace rele_auto
{

namespace employee_vacation
{
//#############################################################################
//			class calendar
//#############################################################################

    //=========================================================================
    //		CONSTRUCTORS/DESTRUCTOR
    //=========================================================================

    ///-------------------------------------------------------------------------
    ///	widget_year_calendar( )
    ///
    widget_year_calendar::widget_year_calendar( QWidget *parent /*= 0*/ ) :
        QWidget( parent )
    {
        this->initialize( );
    }

    ///------------------------------------------------------------------------
    ///	~widget_year_calendar( )
    ///
    widget_year_calendar::~widget_year_calendar( )
    {
    }

    //=========================================================================
    //		PROPERTIES
    //=========================================================================

    //=========================================================================
    //		OPERATORS
    //=========================================================================

    //=========================================================================
    //		FUNCTIONS
    //=========================================================================
    void widget_year_calendar::initialize( )
    {
        QGridLayout *gl = new QGridLayout;
        calendar *month = 0;

        //1st quarter
        //Jan
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 1, 1 ) );
        gl->addWidget( month, 0, 0 );
        this->_calendars.append( month );
        //Feb
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 2, 1 ) );
        gl->addWidget( month, 0, 1 );
        this->_calendars.append( month );
        //Mar
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 3, 1 ) );
        gl->addWidget( month, 0, 2 );
        this->_calendars.append( month );
        //2nd quarter
        //Apr
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 4, 1 ) );
        gl->addWidget( month, 1, 0 );
        this->_calendars.append( month );
        //May
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 5, 1 ) );
        gl->addWidget( month, 1, 1 );
        this->_calendars.append( month );
        //Jun
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 6, 1 ) );
        gl->addWidget( month, 1, 2 );
        this->_calendars.append( month );
        //3rd quarter
        //Jul
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 7, 1 ) );
        gl->addWidget( month, 2, 0 );
        this->_calendars.append( month );
        //Aug
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 8, 1 ) );
        gl->addWidget( month, 2, 1 );
        this->_calendars.append( month );
        //Sep
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 9, 1 ) );
        gl->addWidget( month, 2, 2 );
        this->_calendars.append( month );
        //4th qurter
        //Oct
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 10, 1 ) );
        gl->addWidget( month, 3, 0 );
        this->_calendars.append( month );
        //Nov
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 11, 1 ) );
        gl->addWidget( month, 3, 1 );
        this->_calendars.append( month );
        //Dec
        month = new calendar( this );
        month->setSelectedDate( QDate(QDate::currentDate( ).year( ), 12, 1 ) );
        gl->addWidget( month, 3, 2 );
        this->_calendars.append( month );

        this->setLayout( gl );

        this->setLocale( QLocale( QLocale::Russian ) );
    }

//#############################################################################

}// namespace employee_vacation

}//namespace rele_auto
