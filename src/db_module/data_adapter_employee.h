/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 14-10-2013
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_EMPLOYEE_H__
#define __DATA_ADAPTER_EMPLOYEE_H__

#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
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
///			class data_employee
/// ############################################################################
    class data_employee
	{
        enum field_data_employee
        {
            num_field_employee_id = 0,
            num_field_employee = 1,
            fields_count = 2
        };
    /// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        data_employee( ) :
            _i_employee( 0 ),
            _x_employee( "" )
        { }

	/// ------------------------------------------------------------------------
		explicit
        data_employee( const data_employee &rhs ) :
            _i_employee( rhs._i_employee ),
            _x_employee( rhs._x_employee )
        { }

	/// ------------------------------------------------------------------------
		explicit
        data_employee( const QVector<QVariant> &row )
        {
            this->clear_data( );

            int i_fields_num = row.size( );

            if( i_fields_num < num_field_employee_id ) return;
            _i_employee = row[num_field_employee_id].toInt( );

            if( i_fields_num < num_field_employee ) return;
            _x_employee = row[num_field_employee].toString( );
        }

	/// ------------------------------------------------------------------------
		explicit
        data_employee( espira::db::qt_data_row *p_row )
		{
            this->clear_data( );

            int i_fields_num = p_row->columns_count( );

            if( i_fields_num < num_field_employee_id ) return;
            _i_employee = (*p_row)[num_field_employee_id].toInt( );

            if( i_fields_num < num_field_employee ) return;
            _x_employee = (*p_row)[num_field_employee].toString( );
		}
	/// ------------------------------------------------------------------------
        ~data_employee( )
		{
            qDebug( ) << "deleted : " << this->_i_employee << " " +
                                         this->_x_employee;
		}

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		void clear_data( )
		{
            _i_employee = 0;
            _x_employee.clear( );
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
    ///	employee
        const QString& employee( ) const
        { return this->_x_employee; }

        void employee( const QString &x_employee )
        { this->_x_employee = x_employee; }

    /// ========================================================================
	///		OPERATORS
	/// ========================================================================
	public:
        data_employee& operator=( const data_employee &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            _i_employee = rhs._i_employee;
            _x_employee = rhs._x_employee;

			return *this;
		}

        QString to_string( ) const
        {
            QString s_result( "" );
            s_result += QString::number( this->_i_employee ) + "\n";
            s_result += this->_x_employee + "\n";

            return s_result;
        }
	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        int     _i_employee;            //--id сотрудника
        QString _x_employee;        	//--ФИО сотрудника

    };//class data_employee
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_employee_collection
/// ############################################################################
    class data_employee_collection
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
        data_employee_collection( const data_employee_collection &rhs );
	public:
	/// ------------------------------------------------------------------------
        data_employee_collection( ) :
			_data( 0 )
		{ }
	/// ------------------------------------------------------------------------
        virtual ~data_employee_collection( )
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
                data_employee *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

	/// ------------------------------------------------------------------------
        void append( data_employee *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_employee *>;
			}
			this->_data->append( r );
		}

	/// ------------------------------------------------------------------------
        QList<data_employee *>* list( )
		{ return this->_data; }

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
        data_employee_collection& operator=(
                                        const data_employee_collection &rhs
											);
	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        QList<data_employee *>	*_data;

    };//class data_employee_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_employee
/// ############################################################################
	class data_adapter_employee
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		data_adapter_employee( const data_adapter_employee &rhs );

	public:
	/// ------------------------------------------------------------------------
		explicit data_adapter_employee( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
	/// ------------------------------------------------------------------------
		~data_adapter_employee( );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
	/// ------------------------------------------------------------------------
        QString make_select_qry( const data_employee &emp ) const;
    /// ------------------------------------------------------------------------
        QString make_filter( const data_employee &filter ) const;
	/// ------------------------------------------------------------------------
		void cmd_params_insert(
                          espira::db::qt_sqlite_command *pcmd,
                          const data_employee &r
                        ) const;
    /// ------------------------------------------------------------------------
        void cmd_params_update(
                          espira::db::qt_sqlite_command *pcmd,
                          const data_employee &r
                              ) const;
	/// ------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_employee &r ) const;

	public:
	/// ------------------------------------------------------------------------
		int new_id() const;
    /// ------------------------------------------------------------------------
        QVariant select_id_new( ) const;
	/// ------------------------------------------------------------------------
        data_employee_collection*
                        select( const data_employee &e=data_employee( ) ) const;
	/// ------------------------------------------------------------------------
        void insert( const data_employee &e ) const;
	/// ------------------------------------------------------------------------
        void update( const data_employee &e ) const;
	/// ------------------------------------------------------------------------
        void del(const int id_employee ) const;

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	private:

	public:

	/// ========================================================================
	///		OPERATORS
    /// ========================================================================
    private:
		data_adapter_employee& operator=( const data_adapter_employee &rhs );

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
		static const QString _s_sql_newkey;
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;

	};//class data_adapter_employee

/// ############################################################################
/// ----------------------------------------------------------------------------

}//    namespace employee_vacation

}//    namespace rele_auto

#endif // __DATA_ADAPTER_EMPLOYEE_H__
