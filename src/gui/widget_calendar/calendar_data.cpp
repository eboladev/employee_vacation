/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-03-2013
///		Date update	: 08-12-2014
///		Comment		:
/// ============================================================================

#include "calendar_data.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class calendar_data
/// ############################################################################
    const int calendar_data::DAYS_IN_WEEK = 7;
    const int calendar_data::START_DAY_ROW = 2;

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	calendar_data( )
    /// ------------------------------------------------------------------------
    calendar_data::calendar_data( int year, month_type month  ) :
        _year( year ),
        _month( month ),
        _calendar_rows( 0 )
	{
        //normalize year if it crazy
        if( this->_year < 1900 || this->_year > 10000 )
        {
            this->_year = 1900;
        }
        this->initialize( );
	}

    /// ------------------------------------------------------------------------
    ///	~calendar_data( )
    /// ------------------------------------------------------------------------
    calendar_data::~calendar_data( )
	{
        this->clear( );
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
    ///	clear( )
    /// ------------------------------------------------------------------------
    void calendar_data::clear( )
    {
        QList<unsigned int> keys = this->_items.keys( );
        QList<unsigned int>::iterator it = keys.begin( );
        for( ;it < keys.end( ); ++it )
        {
            calendar_item *item = this->_items.value( *it );
            this->_items.remove( *it );
            if( item )
            {
                qDebug( ) << QString::number( *it, 16 ) << 't' << item->text( ) << " deleted";
                delete item;
            }
        }
    }

    /// ------------------------------------------------------------------------
    ///	initialize( )
    /// ------------------------------------------------------------------------
    void calendar_data::initialize( )
    {
        try
        {
            //month header
            this->init_month_header();
            //days header
            this->init_days_header( );
            //init items
            this->init_day_items( );
        }
        catch( std::exception &ex )
        {
            qDebug() << QString::fromStdString( ex.what() );
        }
    }
    /// ------------------------------------------------------------------------
    ///	init_header( )
    /// ------------------------------------------------------------------------
    void calendar_data::init_month_header()
    {
        QDate dt(this->_year, this->_month, 1);

        //month header in the 0-th row of calendar
        this->_items.insert( 0, new calendar_item_header_month( dt ) );
    }

    void calendar_data::init_days_header( )
    {
        QDate dt(this->_year, this->_month, 1);
        //first seven month's days give us weekdays header
        for( int i = 0; i < calendar_data::DAYS_IN_WEEK; ++i )
        {
            //headers of days are in the first row of calendar
            unsigned int index = hash_index( 1, dt.dayOfWeek( ) - 1 );
            this->_items.insert( index, new calendar_item_header_day( dt ) );
            //next day
            dt = dt.addDays( 1 );
        }
    }

    /// ------------------------------------------------------------------------
    ///	init_day_items( )
    /// ------------------------------------------------------------------------
    void calendar_data::init_day_items( )
    {
        int week_num = 0;

        unsigned int index = 0;
        QDate dt(this->_year, this->_month, 1);
        while( dt.month( )==this->_month )
        {
            int day = dt.dayOfWeek( );
            index = hash_index( START_DAY_ROW+week_num, day - 1 );

            this->_items.insert(
                                 index,
                                 calendar_item_creator::create( dt )
                               );

            qDebug( ) << QString::number( index, 16 )  << '\t' << dt;

            if( day == Qt::Sunday )
            {
                ++week_num;
            }
            dt = dt.addDays( 1 );
        }
        //keep calendar rows
        this->_calendar_rows = (index>>16) + 1;
        qDebug( ) << "_calendar_rows :\t" << this->_calendar_rows;
    }

    /// ------------------------------------------------------------------------
    ///	hash_index( const int row, const int column)
    /// ------------------------------------------------------------------------
    unsigned int calendar_data::hash_index(
                                            const int row,
                                            const int column
                                          ) const
    {
        //make compound date index
        //as two 16-bit words in dword
        unsigned int index = row << 16;
        index |= column;

        return index;
    }

    /// ------------------------------------------------------------------------
    ///	hash_index( const QDate &dt )
    /// ------------------------------------------------------------------------
    unsigned int calendar_data::hash_index( const QDate &dt ) const
    {
        int n_row = this->calendar_row( dt );
        int n_column = this->calendar_column( dt );

        if( n_row == -1 )
        {
            return 0xFFFFFFFF;
        }

        return this->hash_index( n_row, n_column );
    }

    /// ------------------------------------------------------------------------
    ///	calendar_row( const QDate &dt )
    /// ------------------------------------------------------------------------
    int calendar_data::calendar_row( const QDate &dt ) const
    {
        if( this->_month != dt.month( ) || this->_year != dt.year( ) )
        {
            return -1;
        }
        QDate dt_month_start( dt.year( ), dt.month( ), 1 );
        //date cell number in one-dimension row starting with
        //previous month last week Monday
        int cell_number = (dt.day( ) - 1) + (dt_month_start.dayOfWeek( ) - 1);
        //calculate row in calendar table
        int n_row = (cell_number / DAYS_IN_WEEK) + START_DAY_ROW;
        //n_row += (cell_number % DAYS_IN_WEEK) > 0 ? 1 : 0;

        return n_row;
    }

    /// ------------------------------------------------------------------------
    ///	calendar_column( const QDate &dt )
    /// ------------------------------------------------------------------------
    int calendar_data::calendar_column( const QDate &dt ) const
    {
        if( this->_month != dt.month( ) || this->_year != dt.year( ) )
        {
            return -1;
        }
        return dt.dayOfWeek( ) - 1;
    }

    /// ------------------------------------------------------------------------
    ///	item( const int calendar_row, const int calendar_column )
    /// ------------------------------------------------------------------------
    const calendar_item*
        calendar_data::item( const int calendar_row, const int calendar_column ) const
    {
        calendar_item *item = this->_items[ hash_index(calendar_row,calendar_column) ];

        return item ? item : &_item_nothing;
    }

    /// ------------------------------------------------------------------------
    ///	item( const int calendar_row, const int calendar_column, calendar_item *item )
    /// ------------------------------------------------------------------------
    void
        calendar_data::item(
                              const int calendar_row, const int calendar_column,
                              calendar_item *item
                           )
    {
        const unsigned int item_index = hash_index(calendar_row,calendar_column);
        this->replace_item( item_index, item );
    }

    /// ------------------------------------------------------------------------
    ///	replace_item( const unsigned index, calendar_item *new_item )
    /// ------------------------------------------------------------------------
    void
    calendar_data::replace_item( const unsigned item_index, calendar_item *new_item )
    {
        if( !new_item )
        {
            return;
        }
        //get old item
        calendar_item *old_item = this->_items[item_index];
        //delete old item
        if( !old_item )
        {
            return;
        }
        //set new_item date
        new_item->date( old_item->date( ) );
        delete old_item;

        //assign new item
        this->_items[item_index] = new_item;
    }

    /// ------------------------------------------------------------------------
    ///	set_vacation( const int calendar_row, const int calendar_column )
    /// ------------------------------------------------------------------------
    void
    calendar_data::set_vacation( const int calendar_row, const int calendar_column )
    {
        this->item( calendar_row, calendar_column, new calendar_item_vacation );
    }

    /// ------------------------------------------------------------------------
    ///	unset_vacation( const int calendar_row, const int calendar_column )
    /// ------------------------------------------------------------------------
    void
    calendar_data::unset_vacation( const int calendar_row, const int calendar_column )
    {
        const unsigned int item_index = hash_index(calendar_row,calendar_column);
        //get old item
        calendar_item *old_item = this->_items[item_index];
        if( !old_item )
        {
            return;
        }
        calendar_item *item = calendar_item_creator::create( old_item->date( ) );
        this->replace_item( item_index, item );

    }

    /// ------------------------------------------------------------------------
    ///	set_vacation( const QDate &dt )
    /// ------------------------------------------------------------------------
    void calendar_data::set_vacation( const QDate &dt )
    {
        int calendar_row = this->calendar_row( dt );
        int calendar_column = this->calendar_column( dt );
        if( calendar_row < 0 )
        {
            //invalid date
            return;
        }
        this->set_vacation( calendar_row, calendar_column );
    }

    /// ------------------------------------------------------------------------
    ///	unset_vacation( const QDate &dt )
    /// ------------------------------------------------------------------------
    void calendar_data::unset_vacation( const QDate &dt )
    {
        int calendar_row = this->calendar_row( dt );
        int calendar_column = this->calendar_column( dt );
        if( calendar_row < 0 )
        {
            //invalid date
            return;
        }
        this->unset_vacation( calendar_row, calendar_column );
    }

/// ############################################################################

}//namespace employee_vacation

}//namespace rele_auto

