
/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-01-2013
///		Date update	: 10-12-2014
///		Comment		:
/// ============================================================================
#ifndef __EV_TABLEVIEW_MONTH_CALENDAR_H__
#define __EV_TABLEVIEW_MONTH_CALENDAR_H__

#include <QTableView>
#include <QMenu>

#include "data_model_month.h"
#include "date_period.h"

namespace eu = espira::utils;

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class tableview_month_calendar
/// ############################################################################
    class tableview_month_calendar : public QTableView
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        tableview_month_calendar( const tableview_month_calendar &rhs );

    public:
        tableview_month_calendar( int year, int month, QWidget *parent = 0 );
        virtual ~tableview_month_calendar( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
    /// ------------------------------------------------------------------------
        void initialize( );
        void init_layout( );
        void init_signal_connections( );
        void make_periods( );
        int  min_column_width( ) const;
        int  min_row_height( ) const;
        int  correct_columns_width( );
        int  correct_rows_height( );
        void correct_size( );

    public:
    /// ------------------------------------------------------------------------
    /// requery
        void requery( )
        {
            this->setModel( 0 );
            this->_model->requery( );
            this->setModel( this->_model );
        }
    /// ------------------------------------------------------------------------
        void set_vacation( const QDate &dt_begin, const QDate &dt_end );
    /// ------------------------------------------------------------------------
        void unset_vacation( const QDate &dt_begin, const QDate &dt_end );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    public:
    /// ------------------------------------------------------------------------
    /// year
        int year( ) const
        {
            return this->_model->year( );
        }
        void year( const int yyyy )
        {
            this->_model->year( yyyy );
        }
    /// ------------------------------------------------------------------------
    /// month
        int month( ) const
        {
            return this->_model->month( );
        }
        void month( const int MM )
        {
            this->_model->month( MM );
        }

    /// ------------------------------------------------------------------------
    /// selected_periods
        eu::date_period_collection& selected_periods( )
        {
            this->make_periods( );
            return this->_periods;
        }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        tableview_month_calendar& operator=( const tableview_month_calendar &rhs );

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    private slots:
        void show_context_menu( const QPoint & pos );
        void set_vacation( );
        void unset_vacation( );

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    protected:
        virtual void resizeEvent( QResizeEvent *event );

    /// ========================================================================
    ///		FIELDS
    /// ========================================================================
    private:
        data_model_month *_model;

        eu::date_period_collection _periods;

    };//class tableview_month_calendar

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace employee_vacation

}//namespace rele_auto
#endif // __EV_TABLEVIEW_MONTH_CALENDAR_H__
