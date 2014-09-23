/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2013
///		Date update	: 15-10-2013
///		Comment		:
/// ============================================================================
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

#include "application.h"
#include "business_logic.h"

#include "dialog_employee.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class dialog_employee
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	dialog_employee( )
    /// ------------------------------------------------------------------------
    dialog_employee::dialog_employee(
                                            QWidget *parent,
                                            dialog_employee_mode mode
                                    ) :
        QDialog(parent),
        _mode(mode)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~dialog_employee( )
    /// ------------------------------------------------------------------------
    dialog_employee::~dialog_employee( )
    {
        qDebug() << "dialog_employee destroyed";
    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void dialog_employee::initialize( )
    {
        this->setModal( true );
        this->setWindowTitle( tr("dialog_employee") );

        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void dialog_employee::init_connections( )
    {
        //save employee
        this->connect(
                        this->_btn_OK, SIGNAL(clicked()),
                        this, SLOT(save_employee_data())
                     );
        //close window
        this->connect(
                        this->_btn_cancel, SIGNAL(clicked()),
                        this, SLOT(close())
                     );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void dialog_employee::init_layout( )
    {
        QRect rc_rect( this->geometry( ) );
        rc_rect.setWidth( 300 );
        rc_rect.setHeight( 150 );
        this->setGeometry( rc_rect );

        QGridLayout *gl = new QGridLayout;
        gl->setMargin( 5 );
        gl->setSpacing( 5 );

        //line 0
        //------
        //employee
        gl->addWidget( this->init_employee( ), 0, 0, 1, 2 );
        //line 2
        gl->setRowStretch( 2, 1000 );

        //line 3
        //------
        //buttons
        gl->addWidget( this->init_buttons( ), 3, 0, 1, 2 );

        gl->setSizeConstraint(QLayout::SetMinimumSize);

        this->setLayout( gl );
    }

    /// ------------------------------------------------------------------------
    /// init_employee( )
    /// ------------------------------------------------------------------------
    QWidget* dialog_employee::init_employee( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "employee:" ), widget );
        vl->addWidget( lbl );

        this->_txt_employee = new QLineEdit( widget );
        vl->addWidget( this->_txt_employee );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget* dialog_employee::init_buttons( )
    {
        QWidget *widget = new QWidget( this );
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 0 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        this->_btn_OK = new QPushButton( QObject::tr("OK") );
        hl->addWidget( this->_btn_OK );

        this->_btn_cancel = new QPushButton( QObject::tr("Cancel") );
        hl->addWidget( this->_btn_cancel );

        widget->setLayout(hl);

        return widget;
    }
    /// ------------------------------------------------------------------------
    /// set_employee_data( )
    /// ------------------------------------------------------------------------
    void dialog_employee::set_employee_data( )
    {
        if( this->_mode == mode_add )
        {
            this->_employee.clear_data( );
        }
        this->_employee.employee( this->_txt_employee->text( ) );
    }

    /// ------------------------------------------------------------------------
    /// employee_data_valid( )
    /// ------------------------------------------------------------------------
    bool dialog_employee::employee_data_valid( )
    {
        if( this->_employee.employee( ).length( ) < 5 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed employee text") );
            return false;
        }

        return true;
    }
    /// ------------------------------------------------------------------------
    /// center_to_screen( )
    /// ------------------------------------------------------------------------
    void dialog_employee::center_to_screen( )
    {
        QRect rc( QApplication::desktop( )->geometry( ) );
        if( this->parentWidget( ) )
        {
            rc= this->parentWidget( )->frameGeometry( );
        }
        QRect rc_frame( this->frameGeometry( ) );
        this->move(
                   (rc.width()-rc_frame.width())/2,
                   (rc.height()-rc_frame.height())/2
                  );
    }
    /// ------------------------------------------------------------------------
    /// update_controls( )
    /// ------------------------------------------------------------------------
    void dialog_employee::update_controls( )
    {
        this->_txt_employee->setText( this->_employee.employee( ) );
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// save_employee_data( )
    /// ------------------------------------------------------------------------
    void dialog_employee::employee_db_insert( )
    {
        bool b_success = application::the_business_logic( )
                                        .employee_insert( this->_employee );

        if( b_success )
        {
            QMessageBox::information(
                                    0,"info",
                                    tr("successful inserting employee card #" )+
                                    this->_employee.to_string( )
                                    );
            QDialog::done( QDialog::Accepted );
        }
    }

    void dialog_employee::employee_db_update( )
    {
        bool b_success = application::the_business_logic( )
                                        .employee_update( this->_employee );
        if( b_success )
        {
            QMessageBox::information(
                                    0,"info",
                                    tr("successful updating employee card #" )+
                                    this->_employee.to_string( )
                                    );
            QDialog::done( QDialog::Accepted );
        }
    }

    void dialog_employee::save_employee_data( )
    {
        this->set_employee_data( );
        if( !this->employee_data_valid( ) )
        {
            return;
        }
        if( this->_mode==mode_add )
        {
            this->employee_db_insert( );
        }
        if( this->_mode==mode_edit )
        {
            this->employee_db_update( );
        }

    }

}//    namespace employee_vacation

}//    namespace rele_auto
