/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 17-04-2013
///		Date update	: 05-12-2014
///		Comment		:
/// ============================================================================

#include <QGridLayout>
#include <QMessageBox>

#include "widget_year_calendar.h"

#include "tableview_month_calendar.h"
#include "data_model_month.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class widget_year_calendar
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	widget_year_calendar( )
    /// ------------------------------------------------------------------------
    widget_year_calendar::widget_year_calendar( QWidget *parent /*= 0*/ ) :
        QWidget( parent )
    {
        this->initialize( );
    }

    /// ------------------------------------------------------------------------
    ///	~widget_year_calendar( )
    /// ------------------------------------------------------------------------
    widget_year_calendar::~widget_year_calendar( )
    {
    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// init_month_calendar( )
    /// ------------------------------------------------------------------------
    tableview_month_calendar*
    widget_year_calendar::init_month_calendar( int year, calendar_data::month_type month )
    {
        tableview_month_calendar *calendar = 0;
        try
        {
            calendar = new tableview_month_calendar(year, month, this);
            this->_calendars.append(calendar);
        }
        catch( std::exception &ex )
        {
            qDebug( ) << "widget_year_calendar::init_month_calendar\t"
                      << year << '\t' << static_cast<int>( month )
                      << QString::fromStdString( ex.what( ) );
        }

        return calendar;
    }

    /// ------------------------------------------------------------------------
    /// init_spinbox( )
    /// ------------------------------------------------------------------------
    QWidget* widget_year_calendar::init_spinbox( )
    {
        QWidget *w = new QWidget( this );
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin(0);
        hl->setSpacing(0);

        this->_yearbox = new QSpinBox;
        this->_yearbox->setMinimum( 1998 );
        this->_yearbox->setMaximum( 0x7fffffff );
        hl->addWidget( this->_yearbox );

        hl->addStretch( 1000 );

        w->setLayout( hl );

        return w;
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_year_calendar::init_layout( )
    {
        QGridLayout *gl = new QGridLayout(this);

        int n_year = QDate::currentDate( ).year( );

        int n_row = 0, n_column = 0;
        gl->addWidget( this->init_spinbox( ), n_row, n_column, 1, 3 );
        this->_yearbox->setValue(n_year);

        int i_max_height = 0, i_max_width = 0;
        n_row++;n_column = 0;
        //Jan
        tableview_month_calendar*
              calendar = this->init_month_calendar( n_year, calendar_data::Jan );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        //Feb
        calendar = this->init_month_calendar( n_year, calendar_data::Feb );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        //Mar
        calendar = this->init_month_calendar( n_year, calendar_data::Mar );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        gl->setRowMinimumHeight( n_row, i_max_height );
        i_max_height = 0;
        n_row++;n_column = 0;
        //Apr
        calendar = this->init_month_calendar( n_year, calendar_data::Apr );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        //May
        calendar = this->init_month_calendar( n_year, calendar_data::May );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        //Jun
        calendar = this->init_month_calendar( n_year, calendar_data::Jun );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        gl->setRowMinimumHeight( n_row, i_max_height );
        i_max_height = 0;
        n_row++;n_column = 0;
        //Jul
        calendar = this->init_month_calendar( n_year, calendar_data::Jul );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        //Aug
        calendar = this->init_month_calendar( n_year, calendar_data::Aug );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        //Sep
        calendar = this->init_month_calendar( n_year, calendar_data::Sep );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        gl->setRowMinimumHeight( n_row, i_max_height );
        i_max_height = 0;
        n_row++;n_column = 0;
        //Oct
        calendar = this->init_month_calendar( n_year, calendar_data::Oct );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        //Nov
        calendar = this->init_month_calendar( n_year, calendar_data::Nov );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        //Dec
        calendar = this->init_month_calendar( n_year, calendar_data::Dec );
        gl->addWidget(calendar, n_row, n_column++);
        i_max_height = std::max(i_max_height, calendar->geometry( ).height( ) );
        i_max_width = std::max(i_max_width,calendar->geometry( ).width( ) );
        gl->setRowMinimumHeight( n_row, i_max_height );

        gl->setColumnMinimumWidth( 0, i_max_width );
        gl->setColumnMinimumWidth( 1, i_max_width );
        gl->setColumnMinimumWidth( 2, i_max_width );

        gl->setColumnStretch( 3, 1000 );
        gl->setRowStretch( 5, 1000 );

        gl->setSpacing(5);


        this->setLayout(gl);
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_year_calendar::init_connections( )
    {
        this->connect(
                      this->_yearbox, SIGNAL(valueChanged(int)),
                      this, SIGNAL(calendar_changed(int))
                     );
        this->connect(
                      this->_yearbox, SIGNAL(valueChanged(int)),
                      this, SLOT(year_changed())
                     );
    }

    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_year_calendar::initialize( )
    {
        this->init_layout( );
        this->init_connections( );
    }
    /// ------------------------------------------------------------------------
    /// set_vacation( const QDate &dt_begin, const QDate &dt_end )
    /// ------------------------------------------------------------------------
    void widget_year_calendar::set_vacation( const QDate &dt_begin, const QDate &dt_end )
    {
        int n_calendar_index = dt_begin.month( ) - 1;
        tableview_month_calendar *p_calendar = this->_calendars[n_calendar_index];
        p_calendar->set_vacation( dt_begin, dt_end );
        p_calendar->repaint( );

        this->repaint( );
    }

    /// ------------------------------------------------------------------------
    /// unset_vacation( const QDate &dt_begin, const QDate &dt_end )
    /// ------------------------------------------------------------------------
    void widget_year_calendar::unset_vacation( const QDate &dt_begin, const QDate &dt_end )
    {
        int n_calendar_index = dt_begin.month( ) - 1;
        tableview_month_calendar *p_calendar = this->_calendars[n_calendar_index];
        p_calendar->unset_vacation( dt_begin, dt_end );
        p_calendar->repaint( );

        this->repaint( );
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    void widget_year_calendar::year_changed( )
    {
        const int n_year = this->_yearbox->value( );
        vector_calendars::iterator it = this->_calendars.begin( );
        for( ;it < this->_calendars.end( ); ++it )
        {
            tableview_month_calendar *calendar = *it;
            calendar->year( n_year );
            calendar->requery( );
        }
    }

/// ############################################################################

}// namespace employee_vacation

}//namespace rele_auto
