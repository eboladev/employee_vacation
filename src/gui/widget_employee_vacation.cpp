/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 15-10-2013
///		Date update	: 08-12-2014
///		Comment		:
/// ============================================================================

#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>

#include "widget_employee_vacation.h"
#include "widget_year_calendar.h"

#include "data_adapter_vacation_period.h"

#include "business_logic.h"
#include "application.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class widget_employee_vacation
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	widget_employee_vacation( )
    /// ------------------------------------------------------------------------
    widget_employee_vacation::widget_employee_vacation( QWidget *parent /*= 0*/ ) :
        QWidget( parent ),
        _employee( 0 )
    {
        this->initialize( );
    }

    /// ------------------------------------------------------------------------
    ///	~widget_employee_vacation( )
    /// ------------------------------------------------------------------------
    widget_employee_vacation::~widget_employee_vacation( )
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
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_employee_vacation::initialize( )
    {
        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_employee_vacation::init_layout( )
    {
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        vl->addWidget( this->init_label_total( ), 20 );
        vl->addWidget( this->init_widget_calendar( ), 1000 );
        vl->addWidget( this->init_buttons( ), 20 );

        this->setLayout( vl );
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_employee_vacation::init_connections( )
    {
    }

    /// ------------------------------------------------------------------------
    /// init_label_total( )
    /// ------------------------------------------------------------------------
    QWidget *widget_employee_vacation::init_label_total( )
    {
        this->_lbl_total = new QLabel;
        return this->_lbl_total;
    }

    /// ------------------------------------------------------------------------
    /// init_widget_calendar( )
    /// ------------------------------------------------------------------------
    QWidget *widget_employee_vacation::init_widget_calendar( )
    {
        this->_w_calendar = new widget_year_calendar;
        return this->_w_calendar;
    }

    /// ------------------------------------------------------------------------
    /// init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget *widget_employee_vacation::init_buttons()
    {
        QWidget *w = new QWidget;
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 5 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );
        //_btn_save
        this->_btn_save = new QPushButton;
        this->_btn_save->setIcon(
                        *( new QIcon( ":/image/images/32x32/media-floppy.png" ) )
                                        );
        this->_btn_save->setToolTip( QObject::tr( "save vacation periods" ) );
        hl->addWidget( this->_btn_save );

        //_btn_clear
        this->_btn_clear = new QPushButton;
        this->_btn_clear->setIcon(
                        *( new QIcon( ":/image/images/32x32/edit-clear.png" ) )
                                        );
        this->_btn_clear->setToolTip( QObject::tr( "clear vacation periods" ) );
        hl->addWidget( this->_btn_clear );

        w->setLayout( hl );

        return w;
    }

    /*
    /// ------------------------------------------------------------------------
    /// init_context_menu( )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::init_context_menu( )
    {
        this->setContextMenuPolicy(Qt::CustomContextMenu);
        this->connect(
                       this, SIGNAL( customContextMenuRequested(QPoint) ),
                       this, SLOT( show_context_menu(QPoint) )
                     );
        this->_menu_context = new QMenu;
        QAction *action = this->_menu_context->addAction( "Set vacation days" );
        action->connect(
                        action, SIGNAL( triggered( ) ),
                        this, SLOT( set_vacation( ) )
                       );
        action = this->_menu_context->addAction( "Unset vacation days" );
        action->connect(
                        action, SIGNAL( triggered( ) ),
                        this, SLOT( unset_vacation( ) )
                       );
    }
*/
    /// ------------------------------------------------------------------------
    /// refresh_calendar( )
    /// ------------------------------------------------------------------------
    void widget_employee_vacation::refresh_calendar( )
    {
        //empty calendar vacation periods
        this->_w_calendar->year_changed( );

        //check employee
        if( this->_employee == 0 )
        {
            return;
        }

        //get vacation periods data
        business_logic &logic = application::program_instance( )->the_business_logic( );
        data_vacation_period_collection *p_coll = 0;
        p_coll = logic.vacation_period_select(
                                            this->_employee->id_employee( ),
                                            this->_w_calendar->year( )
                                             );
        if( !p_coll )
        {
            //set total days text
            this->total_days( 0 );
            return;
        }

        int n_total_days = 0;
        //paint vacation days
        data_vacation_period_collection::iterator it = p_coll->begin( );
        for( ;it != p_coll->end( ); ++it )
        {
            data_vacation_period *period = *it;
            if( period )
            {
                QDate dt_begin = period->date_begin( );
                QDate dt_end = period->date_end( );
                this->_w_calendar->set_vacation( dt_begin, dt_end );

                //+1 includes begining period date
                n_total_days += dt_begin.daysTo( dt_end ) + 1;
            }
        }
        //remove collection pointer
        delete p_coll;
        //set total days text
        this->total_days( n_total_days );
    }
    /// ========================================================================
    ///		EVENTS
    /// ========================================================================

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// slot_set_employee(const data_employee *)
    /// ------------------------------------------------------------------------
    void widget_employee_vacation::slot_set_employee( const data_employee *employee )
    {
        this->_employee = const_cast<data_employee *>( employee );
        this->refresh_calendar( );
    }

/// ############################################################################

}// namespace employee_vacation

}//namespace rele_auto
