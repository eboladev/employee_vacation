/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 23-10-2013
///		Date update	: 10-12-2014
///		Comment		:
/// ============================================================================
#ifndef __DATE_PERIOD_H__
#define __DATE_PERIOD_H__

#include <QDate>
#include <QList>

namespace espira
{

namespace utils
{

/// ############################################################################
///			class date_period
/// ############################################################################
    class date_period
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
        /// --------------------------------------------------------------------
        explicit date_period( const QDate &dt_begin, const QDate &dt_end ) :
            _dt_begin( dt_begin ),
            _dt_end( dt_end )
        { }

        /// --------------------------------------------------------------------
        date_period( const date_period &rhs ) :
            _dt_begin( rhs._dt_begin ),
            _dt_end( rhs._dt_end )
        { }

        /// --------------------------------------------------------------------
        virtual ~date_period( )
        { }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
        /// --------------------------------------------------------------------
        /// date_begin
        const QDate& date_begin( ) const
        { return this->_dt_begin; }

        void date_begin( const QDate& dt )
        { this->_dt_begin = dt; }

        /// --------------------------------------------------------------------
        /// date_end
        const QDate& date_end( ) const
        { return this->_dt_end; }

        void date_end( const QDate& dt )
        { this->_dt_end = dt; }

        /// --------------------------------------------------------------------
        /// is_valid
        bool is_valid( ) const
        {
            return
                    this->_dt_begin.isValid( ) &&
                    this->_dt_end.isValid( ) &&
                    ( this->_dt_begin <= this->_dt_end );
        }

        /// --------------------------------------------------------------------
        /// days_in_period
        int days_in_period( ) const
        {
            if( !this->is_valid( ) )
            {
                return -1;
            }
            //+1 - includes date_begin
            return this->_dt_begin.daysTo( this->_dt_end ) + 1;
        }
    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    public:
        /// --------------------------------------------------------------------
        date_period& operator=( const date_period &rhs )
        {
            if( &rhs == this )
            {
                return *this;
            }
            this->_dt_begin = rhs._dt_begin;
            this->_dt_end = rhs._dt_end;

            return *this;
        }
        /// --------------------------------------------------------------------
        QString to_string( )
        {
            if( !this->_dt_begin.isValid( ) || !this->_dt_end.isValid( ) )
            {
                return QString( "" );
            }
            return this->_dt_begin.toString( "yyyy-MM-dd" ) + " / " +
                   this->_dt_end.toString( "yyyy-MM-dd" );
        }

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        QDate   _dt_begin;
        QDate   _dt_end;

	};//class date_period
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			date_period_collection
/// ############################################################################

    class date_period_collection
	{
	public:
        typedef QList<date_period *>::iterator iterator;
        typedef QList<date_period *>::const_iterator const_iterator;
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
    private:
        /// --------------------------------------------------------------------
        date_period_collection( const date_period_collection &rhs );
	public:
        /// --------------------------------------------------------------------
        date_period_collection( ) :
			_data( 0 )
		{ }
        /// --------------------------------------------------------------------
        virtual ~date_period_collection( )
		{ this->free( ); }

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
        /// --------------------------------------------------------------------
        /// size( )
		int size( ) const
		{
			if( !this->_data )
			{
				return 0;
			}
			return this->_data->size( );
		}

        /// --------------------------------------------------------------------
        /// list( )
        QList<date_period *>* list( )
		{ return this->_data; }

        /// --------------------------------------------------------------------
        /// begin( )
        iterator begin( )
        {
            if( !this->_data )
            {
                this->_data = new QList<date_period *>;
            }
            return this->_data->begin( );
        }

        /// --------------------------------------------------------------------
        /// const_begin( )
        const_iterator const_begin( ) const
        {
            if( !this->_data )
            {
                return 0;
            }
            return this->_data->constBegin( );
        }

        /// --------------------------------------------------------------------
        /// end( )
        iterator end( )
        {
            if( !this->_data )
            {
                this->_data = new QList<date_period *>;
            }
            return this->_data->end( );
        }

        /// --------------------------------------------------------------------
        /// const_end( )
        const_iterator const_end( ) const
        {
            if( !this->_data )
            {
                return 0;
            }
            return this->_data->constEnd( );
        }

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
        /// --------------------------------------------------------------------
		void free_data_pointer( )
		{
			if( !this->_data )
			{
				return;
			}
			//free pointer to list
			//but save pointers on list elements
			delete _data;
			this->_data = 0;
		}

        /// --------------------------------------------------------------------
		void free( )
		{
			if( !this->_data )
			{
				return;
			}
			while( this->_data->size( ) )
			{
				//get last element
                date_period *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

        /// --------------------------------------------------------------------
        void append( date_period *period )
		{
			if( !this->_data )
			{
                this->_data = new QList<date_period *>;
			}
			this->_data->append( period );
		}

    	/// --------------------------------------------------------------------
        void append( const date_period &period )
		{
            this->append( new date_period( period ) );
		}

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
        date_period_collection& operator=(
                                        const date_period_collection &rhs
											);
	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        QList<date_period *>	*_data;

    };//class date_period_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace utils

}//namespace espira
#endif // __DATE_PERIOD_H__
