/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 15-10-2013
///		Comment		:
/// ============================================================================
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QKeyEvent>

#include "application.h"
#include "business_logic.h"

#include "widget_central.h"
#include "widget_employee_vacation.h"
#include "widget_employee.h"

namespace rele_auto
{

namespace employee_vacation
{

/// ############################################################################
///			class widget_central
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	widget_central( )
    /// ------------------------------------------------------------------------
    widget_central::widget_central(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_central( )
    /// ------------------------------------------------------------------------
    widget_central::~widget_central( )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_central::initialize( )
    {
        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_central::init_layout( )
    {
        QHBoxLayout *hl = new QHBoxLayout;

        hl->addWidget( this->init_widget_employee( ), 400 );
        hl->addWidget( this->init_widget_employee_vacation( ), 1000 );

        this->setLayout( hl );

        if( this->_w_employee )
        {
            this->_w_employee->setFocus( );
        }
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_central::init_connections( )
    {
    }

    /// ------------------------------------------------------------------------
    /// init_widget_year_calendar( )
    /// ------------------------------------------------------------------------
    QWidget* widget_central::init_widget_employee_vacation( )
    {
        this->_w_calendar = new widget_employee_vacation( this );

        return this->_w_calendar;
    }

    /// ------------------------------------------------------------------------
    /// init_listview_employee( )
    /// ------------------------------------------------------------------------
    QWidget* widget_central::init_widget_employee( )
    {
        this->_w_employee = new widget_employee( this );

        return this->_w_employee;
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// keyPressEvent ( QKeyEvent * event )
    /// ------------------------------------------------------------------------

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /*
    /// ------------------------------------------------------------------------
    /// slot_add_request( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_add_request( )
    {
        dialog_request_data w_data_add;
        w_data_add.exec( );
    }

    /// ------------------------------------------------------------------------
    /// slot_edit_request( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_edit_request( )
    {
        const data_request *request = this->_lv_employee->current_request( );
        if( request )
        {
            dialog_request_data w_data_edit( 0, dialog_request_data::mode_edit_request );
            w_data_edit.request( *request );
            w_data_edit.exec( );
        }
    }

    /// ------------------------------------------------------------------------
    /// slot_del_request( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_del_request( )
    {
        const data_request *r = this->_lv_employee->current_request( );
        if( !r )
        {
            return;
        }
        int i_reply = QMessageBox::question(
                                    0, tr("apply action"),
                                    tr( "Press Yes if you're want delete request" ),
                                    QMessageBox::No|QMessageBox::Yes
                                           );
        if( i_reply == QMessageBox::Yes)
        {
            business_logic &logic = app_mac_mediator::the_business_logic( );
            if( logic.request_delete( r->id_request( ) ) )
            {
                QMessageBox::information(
                                         0, tr("info"),
                                         r->id_request_string( ) +
                                         tr(" request successful deleted from db")
                                        );
            }
        }

    }
*/
}//    namespace employee_vacation

}//    namespace rele_auto
