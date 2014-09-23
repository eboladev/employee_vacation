/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 15-10-2013
///		Date update	: 22-10-2013
///		Comment		:
/// ============================================================================
#ifndef __WIDGET_EMPLOYEE_VACATION_H__
#define __WIDGET_EMPLOYEE_VACATION_H__

#include <QWidget>
#include <QPushButton>

namespace rele_auto
{

namespace employee_vacation
{
    class data_employee;
    class widget_year_calendar;
/// ############################################################################
///			class widget_employee_vacation
/// ############################################################################
    class widget_employee_vacation : public QWidget
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_employee_vacation( const widget_employee_vacation &rhs );

    public:
        /// --------------------------------------------------------------------
        explicit widget_employee_vacation( QWidget *parent = 0 );
        /// --------------------------------------------------------------------
        virtual ~widget_employee_vacation( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        /// --------------------------------------------------------------------
        void init_layout( );
        /// --------------------------------------------------------------------
        void init_connections( );
        /// --------------------------------------------------------------------
        QWidget* init_widget_calendar( );
        /// --------------------------------------------------------------------
        QWidget* init_buttons( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    public:
        /// --------------------------------------------------------------------
        /// employee
        void employee( data_employee *e )
        {
            this->_employee = e;
        }
        const data_employee* employee( ) const
        {
            return this->_employee;
        }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_employee_vacation& operator=( const widget_employee_vacation &rhs );

    /// ========================================================================
    ///		SIGNALS
    /// ========================================================================
    signals:

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    private slots:

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    protected:

    /// ========================================================================
    ///		FIELDS
    /// ========================================================================
    private:
        widget_year_calendar    *_w_calendar;
        QPushButton             *_btn_save;
        QPushButton             *_btn_clear;

        data_employee           *_employee;
    };

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace employee_vacation

}//namespace rele_auto

#endif // __WIDGET_EMPLOYEE_VACATION_H__