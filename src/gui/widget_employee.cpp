/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 11-10-2013
///		Date update	: 02-10-2014
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

#include "widget_employee.h"
#include "listview_employee.h"

#include "dialog_employee.h"

namespace rele_auto
{

namespace employee_vacation
{

/// ############################################################################
///			class widget_employee
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	widget_employee( )
    /// ------------------------------------------------------------------------
    widget_employee::widget_employee(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_employee( )
    /// ------------------------------------------------------------------------
    widget_employee::~widget_employee( )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_employee::initialize( )
    {
        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_employee::init_layout( )
    {
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        vl->addWidget( this->init_listview_employee( ), 1000 );
        vl->addWidget( this->init_buttons( ), 20 );

        vl->setSizeConstraint(QLayout::SetMaximumSize);

        this->setLayout( vl );

        if( this->_lv_employee )
        {
            this->_lv_employee->setFocus( );
        }
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_employee::init_connections( )
    {
        //_btn_add_employee
        this->connect(
                    this->_btn_add_employee, SIGNAL( clicked( ) ),
                    this, SLOT( slot_add_employee( ) )
                    );
        //_btn_edit_employee
        this->connect(
                    this->_btn_edit_employee, SIGNAL( clicked( ) ),
                    this, SLOT( slot_edit_employee( ) )
                    );
        //_btn_del_employee
        this->connect(
                    this->_btn_del_employee, SIGNAL( clicked( ) ),
                    this, SLOT( slot_del_employee( ) )
                    );
        //_lv_employee
        this->connect(
                     this->_lv_employee, SIGNAL(current_item_changed(const data_employee*)),
                     this, SIGNAL(employee_selected(const data_employee*))
                     );
    }

    /// ------------------------------------------------------------------------
    /// init_listview_employee( )
    /// ------------------------------------------------------------------------
    QWidget* widget_employee::init_listview_employee( )
    {
        QWidget *widget = new QWidget( this );

        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "employees list:" ), this );

        vl->addWidget( lbl );

        this->_lv_employee = new listview_employee( this );
        vl->addWidget( this->_lv_employee );

        widget->setLayout( vl );

        return widget;
    }
    /// ------------------------------------------------------------------------
    /// init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget* widget_employee::init_buttons( )
    {
        QWidget *widget = new QWidget( this );

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 5 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        //_btn_add_employee
        this->_btn_add_employee = new QPushButton;
        this->_btn_add_employee->setIcon(
                        *( new QIcon( ":/image/images/32x32/list-add.png" ) )
                                        );
        this->_btn_add_employee->setToolTip( QObject::tr( "add employee" ) );
        hl->addWidget( this->_btn_add_employee );
        //_btn_edit_employee
        this->_btn_edit_employee = new QPushButton;
        this->_btn_edit_employee->setIcon(
                    *( new QIcon( ":/image/images/32x32/package_editors.png" ) )
                                         );
        this->_btn_edit_employee->setToolTip( QObject::tr( "edit employee" ) );
        hl->addWidget( this->_btn_edit_employee );
        //_btn_del_employee
        this->_btn_del_employee = new QPushButton;
        this->_btn_del_employee->setIcon(
                    *( new QIcon( ":/image/images/32x32/list-remove.png" ) )
                                         );
        this->_btn_del_employee->setToolTip( QObject::tr( "delete employee" ) );
        hl->addWidget( this->_btn_del_employee );
        //_btn_vacations
        this->_btn_vacations = new QPushButton;
        this->_btn_vacations->setIcon(
                    *( new QIcon( ":/image/images/32x32/view-calendar-upcoming-days.png" ) )
                                         );
        this->_btn_vacations->setToolTip( QObject::tr( "employee vacations" ) );
        hl->addWidget( this->_btn_vacations );

        widget->setLayout( hl );

        return widget;
    }
    /// ========================================================================
    ///		EVENTS
    /// ========================================================================

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// slot_add_employee( )
    /// ------------------------------------------------------------------------
    void widget_employee::slot_add_employee( )
    {
        dialog_employee dlg_add_employee;
        dlg_add_employee.exec( );
    }

    /// ------------------------------------------------------------------------
    /// slot_edit_employee( )
    /// ------------------------------------------------------------------------
    void widget_employee::slot_edit_employee( )
    {
        const data_employee *employee = this->_lv_employee->current_employee( );
        if( employee )
        {
            dialog_employee dlg_edit_employee( 0, dialog_employee::mode_edit );
            dlg_edit_employee.employee( *employee );
            dlg_edit_employee.exec( );
        }
    }

    /// ------------------------------------------------------------------------
    /// slot_del_employee( )
    /// ------------------------------------------------------------------------
    void widget_employee::slot_del_employee( )
    {
        const data_employee *pe = this->_lv_employee->current_employee( );
        if( !pe )
        {
            return;
        }
        const data_employee e_copy( *pe );
        int i_reply = QMessageBox::question(
                                    0, tr("apply action"),
                                    tr( "Press Yes if you're want delete employee" ),
                                    QMessageBox::No|QMessageBox::Yes
                                           );
        if( i_reply == QMessageBox::Yes)
        {
            business_logic &logic = application::the_business_logic( );
            if( logic.employee_delete( pe->id_employee( ) ) )
            {
                QMessageBox::information(
                                         0, tr("info"),
                                         e_copy.to_string( ) +
                                         tr(" employee successful deleted from db")
                                        );
            }
        }

    }

}//    namespace employee_vacation

}//    namespace rele_auto
