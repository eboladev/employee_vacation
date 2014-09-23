/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 15-10-2013
///		Comment		:
/// ============================================================================
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include "application.h"
#include "business_logic.h"

#include "data_adapter_employee.h"
#include "qt_sqlite_command.h"
#include "qt_data_parameter.h"
#include "qt_sqlite_dbvalue.h"

namespace rele_auto
{

namespace employee_vacation
{

	const QString data_adapter_employee::_s_sql_newkey(
								"SELECT max(i_employee)+1 FROM t_employee;"
													 );
	const QString data_adapter_employee::_s_sql_insert(
								"INSERT INTO t_employee "
                                    "(i_employee, x_employee) "
                                        "VALUES(:i_employee, :x_employee);"
                        			  				  );
	const QString data_adapter_employee::_s_sql_update(
								"UPDATE t_employee"
								"   SET x_employee=:x_employee "
								"WHERE i_employee=:i_employee;"
									);
	const QString data_adapter_employee::_s_sql_delete(
								"DELETE FROM t_employee "
								"WHERE i_employee=:i_employee;"
									);
	const QString data_adapter_employee::_s_sql_select(
                                "SELECT i_employee, x_employee "
                                       "FROM t_employee "
                                                    );

/// ############################################################################
///			class data_adapter_employee
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	~data_adapter_employee( )
	/// ------------------------------------------------------------------------
	data_adapter_employee::~data_adapter_employee( )
	{
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
	///	throw_error( const char* s_msg ) const
    /// ------------------------------------------------------------------------
	void data_adapter_employee::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	/// ------------------------------------------------------------------------
	///	cmd_params_insert
    /// ------------------------------------------------------------------------
	void data_adapter_employee::cmd_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_employee &r
                                             ) const
	{
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_employee( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.employee( ) ) );
	}

    /// ------------------------------------------------------------------------
	///	cmd_params_update
    /// ------------------------------------------------------------------------
	void data_adapter_employee::cmd_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_employee &r
                                             ) const
	{
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.employee( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_employee( ) ) );
	}

	/// ------------------------------------------------------------------------
	///	select_id_new( int id_ad )
    /// ------------------------------------------------------------------------
    QVariant data_adapter_employee::select_id_new( ) const
    {
        QString s_qry( data_adapter_employee::_s_sql_newkey );

        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        QVariant val_id_new;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //open cmd
            pcmd->open( );
            //exec
            val_id_new = pcmd->execute_scalar( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            val_id_new = QVariant( );

            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
        return val_id_new;
    }

    /// ------------------------------------------------------------------------
	///	newkey( ) const
    /// ------------------------------------------------------------------------
    int data_adapter_employee::new_id( ) const
	{
        QVariant val = this->select_id_new( );
        if( val.isNull( ) || !val.isValid( ) )
        {
            return 1;
        }

		return val.toInt( );
	}

    /// ------------------------------------------------------------------------
	///	make_filter( const data_employee &r_filter )
    /// ------------------------------------------------------------------------
	QString data_adapter_employee::make_filter(
									const data_employee &criteria
											 ) const
	{
		QString s_filter( "" );
        if( criteria.id_employee( ) > 0 )
		{
			s_filter += "(i_employee=" +
                        QString::number( criteria.id_employee( ) ) +")";
            return s_filter;
		}
		if( criteria.employee( ).length( ) )
		{
			s_filter = "((x_employee='" + criteria.employee( ) + "')OR";
			s_filter += "(x_employee LIKE '%" + criteria.employee( ) + "')OR";
			s_filter += "(x_employee LIKE '%" + criteria.employee( ) + "%')OR";
			s_filter += "(x_employee LIKE '" + criteria.employee( ) + "%'))";
		}

        if( s_filter.length( ) )
        {
            s_filter.prepend('(');
            s_filter.append(')');
        }

		return s_filter;
	}

	/// ------------------------------------------------------------------------
	///	select( const data_employee &r_filter ) const
    /// ------------------------------------------------------------------------
    QString data_adapter_employee::make_select_qry(const data_employee &emp) const
    {
        QString s_qry( data_adapter_employee::_s_sql_select );

        QString s_filter = this->make_filter( emp );
        if( s_filter.length( ) )
        {
            s_qry += "WHERE " + s_filter + ";";
        }

        return s_qry;
    }

    data_employee_collection*
		data_adapter_employee::select( const data_employee &emp ) const
	{
		//make select query
        QString s_qry = make_select_qry(emp);

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_employee_collection *emp_coll = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );

            //output result
            espira::db::qt_data_row_collection &rows = pcmd->result( );
            if( rows.size( ) )
            {
                emp_coll = new data_employee_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end( ); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    emp_coll->append( new data_employee( r ) );
                }
            }

            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            if( emp_coll )
            {
                emp_coll->free( );
                delete emp_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return emp_coll;
	}

	/// ------------------------------------------------------------------------
	///	insert( const data_employee &emp ) const
	/// ------------------------------------------------------------------------
	void data_adapter_employee::insert( const data_employee &emp ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_employee::_s_sql_insert );
            //add parameters
            this->cmd_params_insert( pcmd, emp );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
	}

	/// ------------------------------------------------------------------------
	///	update( const data_employee &emp ) const
	/// ------------------------------------------------------------------------
	void data_adapter_employee::update( const data_employee &emp ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_employee::_s_sql_update );
            //add parameters
            this->cmd_params_update( pcmd, emp );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
	}

	/// ------------------------------------------------------------------------
	///	del( const int id_request ) const
    /// ------------------------------------------------------------------------
	void data_adapter_employee::del( const int id_employee ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_employee::_s_sql_delete );
            pcmd->parameters( ).append(
                        new espira::db::qt_sqlite_dbvalue_int( id_employee )
                                      );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
    }

/// ############################################################################


}//    namespace employee_vacation

}//    namespace rele_auto

