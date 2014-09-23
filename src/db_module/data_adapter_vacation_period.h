/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 15-10-2013
///		Date update	: 15-10-2013
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_VACATION_PERIOD_H__
#define __DATA_ADAPTER_VACATION_PERIOD_H__

#include <QDebug>
#include <QString>
#include <QDate>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace rele_auto
{

namespace employee_vacation
{

/// ############################################################################
///			class data_vacation_period
/// ############################################################################
    class data_vacation_period
	{
        enum field_data_vacation_period
        {
            num_field_employee_id = 0,
            num_field_dtfrom = 1,
            num_field_dtto = 2,
            fields_count = 3
        };
    /// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_vacation_period( ) :
            _i_employee( 0 ),
            _x_dt_begin( "" ),
            _x_dt_end( "" )
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_vacation_period( const data_vacation_period &rhs ) :
            _i_employee( rhs._i_employee ),
            _x_dt_begin( rhs._x_dt_begin ),
            _x_dt_end( rhs._x_dt_end )
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_vacation_period( const QVector<QVariant> &row )
        {
            this->clear_data( );

            int i_fields_num = row.size( );

            if( i_fields_num < num_field_employee_id ) return;
            _i_employee = row[num_field_employee_id].toInt( );

            if( i_fields_num < num_field_dtfrom ) return;
            _x_dt_begin = row[num_field_dtfrom].toString( );

            if( i_fields_num < num_field_dtto ) return;
            _x_dt_begin = row[num_field_dtto].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_vacation_period( espira::db::qt_data_row *p_row )
		{
            this->clear_data( );

            int i_fields_num = p_row->columns_count( );

            if( i_fields_num < num_field_employee_id ) return;
            _i_employee = (*p_row)[num_field_employee_id].toInt( );

            if( i_fields_num < num_field_dtfrom ) return;
            _x_dt_begin = (*p_row)[num_field_dtfrom].toString( );

            if( i_fields_num < num_field_dtto ) return;
            _x_dt_begin = (*p_row)[num_field_dtto].toString( );
		}
    /// ------------------------------------------------------------------------
        ~data_vacation_period( )
		{
            qDebug( ) << "deleted : " << this->_i_employee << " "
                        << this->_x_dt_begin << " " << this->_x_dt_end;
		}

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            _i_employee = 0;
            _x_dt_begin.clear( );
            _x_dt_end.clear( );
        }

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	id_employee
        int id_employee( ) const
        { return this->_i_employee; }

        void id_employee( const int &i_employee )
        { this->_i_employee = i_employee; }

    /// ------------------------------------------------------------------------
    ///	date_begin
        QDate date_begin( ) const
        { return QDate::fromString( this->_x_dt_begin, "yyyy-MM-dd" ); }

        const QString text_date_begin( ) const
        { return this->_x_dt_begin; }

        void date_begin( const QDate &dt )
        { this->_x_dt_begin = dt.toString( "yyyy-MM-dd" ); }

    /// ------------------------------------------------------------------------
    ///	date_end
        QDate date_end( ) const
        { return QDate::fromString( this->_x_dt_end, "yyyy-MM-dd" ); }

        const QString text_date_end( ) const
        { return this->_x_dt_end; }

        void date_end( const QDate &dt )
        { this->_x_dt_end = dt.toString( "yyyy-MM-dd" ); }

    /// ========================================================================
	///		OPERATORS
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_vacation_period& operator=( const data_vacation_period &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            _i_employee = rhs._i_employee;
            _x_dt_begin = rhs._x_dt_begin;
            _x_dt_end = rhs._x_dt_end;

			return *this;
		}

    /// ------------------------------------------------------------------------
        QString to_string( ) const
        {
            QString s_result( "" );
            s_result += QString::number( this->_i_employee ) + "\n";
            s_result += this->_x_dt_begin + "\t";
            s_result += this->_x_dt_end;

            return s_result;
        }
	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        int     _i_employee;    //--id сотрудника
        QString _x_dt_begin;      //--дата начала периода отпуска
        QString _x_dt_end;        //--дата окончания периода отпуска

    };//class data_vacation_period
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_vacation_period_collection
/// ############################################################################
    class data_vacation_period_collection
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
    /// ------------------------------------------------------------------------
    private:
        data_vacation_period_collection( const data_vacation_period_collection &rhs );

	public:
    /// ------------------------------------------------------------------------
        data_vacation_period_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_vacation_period_collection( )
		{ this->free( ); }

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		int size( ) const
		{
			if( !this->_data )
			{
				return 0;
			}
			return this->_data->size( );
		}

    /// ------------------------------------------------------------------------
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

    /// ------------------------------------------------------------------------
		void free( )
		{
			if( !this->_data )
			{
				return;
			}
			while( this->_data->size( ) )
			{
				//get last element
                data_vacation_period *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_vacation_period *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_vacation_period *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_vacation_period *>* list( )
		{ return this->_data; }

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
        data_vacation_period_collection& operator=(
                                        const data_vacation_period_collection &rhs
											);
	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        QList<data_vacation_period *>	*_data;

    };//class data_vacation_period_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_vacation_period
/// ############################################################################
	class data_adapter_vacation_period
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		data_adapter_vacation_period( const data_adapter_vacation_period &rhs );

	public:
    /// ------------------------------------------------------------------------
		explicit data_adapter_vacation_period( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
		~data_adapter_vacation_period( );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        QString make_select_qry( const int id_employee, const int n_year ) const;
    /// ------------------------------------------------------------------------
        QString make_filter( const int id_employee, const int n_year ) const;
    /// ------------------------------------------------------------------------
		void append_cmd_params(
                          espira::db::qt_sqlite_command *pcmd,
                          const data_vacation_period &r
                        ) const;
    /// ------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_vacation_period &r ) const;

	public:
    /// ------------------------------------------------------------------------
        data_vacation_period_collection*
                        select( const int id_employee, int n_year ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_vacation_period &e ) const;
    /// ------------------------------------------------------------------------
        void del( const data_vacation_period &e ) const;

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	private:

	public:

	/// ========================================================================
	///		OPERATORS
    /// ========================================================================
    private:
		data_adapter_vacation_period& operator=( const data_adapter_vacation_period &rhs );

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;

	};//class data_adapter_vacation_period

/// ############################################################################
/// ----------------------------------------------------------------------------

}//    namespace employee_vacation

}//    namespace rele_auto

#endif // __DATA_ADAPTER_VACATION_PERIOD_H__
