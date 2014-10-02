/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 15-10-2013
///		Date update	: 02-10-2014
///		Comment		:
/// ============================================================================

#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>

#include "widget_employee_vacation.h"
#include "widget_year_calendar.h"

#include "data_adapter_employee.h"

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
    /// slot_set_employee(const data_employee *)
    /// ------------------------------------------------------------------------
    void widget_employee_vacation::refresh_calendar( )
    {
        if( this->_employee == 0 )
        {
            return;
        }
        QMessageBox::information(
                                 0, tr("info"),
                                 this->_employee->to_string( )
                                );
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
