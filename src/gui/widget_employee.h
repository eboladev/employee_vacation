/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 11-10-2013
///		Date update	: 14-10-2013
///		Comment		:
/// ============================================================================
#ifndef __WIDGET_EMPLOYEE_H__
#define __WIDGET_EMPLOYEE_H__

#include <QWidget>
#include <QPushButton>

namespace rele_auto
{

namespace employee_vacation
{

class listview_employee;

/// ############################################################################
///			class widget_employee
/// ############################################################################
    class widget_employee : public QWidget
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_employee( const widget_employee &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit widget_employee(QWidget *parent = 0);
        /// --------------------------------------------------------------------
        virtual ~widget_employee( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        void init_layout();
        QWidget* init_listview_employee( );
        QWidget* init_buttons( );

        void init_connections( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_employee& operator=( const widget_employee &rhs );

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
	protected:

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    private slots:
        /// --------------------------------------------------------------------
        void slot_add_employee( );
        /// --------------------------------------------------------------------
        void slot_edit_employee( );
        /// --------------------------------------------------------------------
        void slot_del_employee( );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        listview_employee       *_lv_employee;

        QPushButton         *_btn_add_employee;
        QPushButton         *_btn_edit_employee;
        QPushButton         *_btn_del_employee;
        QPushButton         *_btn_vacations;

	};//class widget_employee
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace employee_vacation

}//namespace rele_auto

#endif // __WIDGET_EMPLOYEE_H__