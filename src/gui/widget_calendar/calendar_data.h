/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-03-2013
///		Date update	: 05-12-2014
///		Comment		:
/// ============================================================================
#ifndef __CALENDAR_DATA_H__
#define __CALENDAR_DATA_H__

#include <QString>
#include <QVector>

#include "calendar_item.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class calendar_data
/// ############################################################################
    class calendar_data
	{
    public:
        enum month_type
        {
            Jan = 1,
            Feb = 2,
            Mar = 3,
            Apr = 4,
            May = 5,
            Jun = 6,
            Jul = 7,
            Aug = 8,
            Sep = 9,
            Oct = 10,
            Nov = 11,
            Dec = 12
        };

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        calendar_data( const calendar_data &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit calendar_data( int year, month_type month );
        /// --------------------------------------------------------------------
        virtual ~calendar_data( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        /// --------------------------------------------------------------------
        void init_month_header( );
        /// --------------------------------------------------------------------
        void init_days_header( );
        /// --------------------------------------------------------------------
        void init_day_items( );
        /// --------------------------------------------------------------------
        unsigned int hash_index( const int row, const int column ) const;
        /// --------------------------------------------------------------------
        unsigned int hash_index( const QDate &dt ) const;
        /// --------------------------------------------------------------------
        int calendar_row( const QDate &dt ) const;
        /// --------------------------------------------------------------------
        int calendar_column( const QDate &dt ) const;
        /// --------------------------------------------------------------------
        void clear( );
        /// --------------------------------------------------------------------
        void replace_item( const unsigned index, calendar_item *new_item );

    public:
        /// --------------------------------------------------------------------
        const calendar_item*
            item( const int calendar_row, const int calendar_column ) const;
        /// --------------------------------------------------------------------
        void
            item(
                  const int calendar_row, const int calendar_column,
                  calendar_item *item
                );
        /// --------------------------------------------------------------------
        void
            set_vacation( const int calendar_row, const int calendar_column );
        /// --------------------------------------------------------------------
        void
            unset_vacation( const int calendar_row, const int calendar_column );
        /// --------------------------------------------------------------------
        void
            set_vacation( const QDate &dt );
        /// --------------------------------------------------------------------
        void
            unset_vacation( const QDate &dt  );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
        /// --------------------------------------------------------------------
        int year( ) const { return this->_year; }
        /// --------------------------------------------------------------------
        int calendar_rows( ) const { return this->_calendar_rows; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        calendar_data& operator=( const calendar_data &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        static const int DAYS_IN_WEEK;
        static const int START_DAY_ROW;

        int _year;
        month_type _month;
        int _calendar_rows;

        QHash<unsigned int, calendar_item*> _items;
        calendar_item_nothing _item_nothing;

    };//class calendar_data
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace employee_vacation

}//namespace rele_auto

#endif // __CALENDAR_DATA_H__
