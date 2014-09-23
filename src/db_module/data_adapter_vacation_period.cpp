/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 15-10-2013
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

#include "data_adapter_vacation_period.h"
#include "qt_sqlite_command.h"
#include "qt_data_parameter.h"
#include "qt_sqlite_dbvalue.h"

namespace rele_auto
{

namespace employee_vacation
{

	const QString data_adapter_vacation_period::_s_sql_insert(
								"INSERT INTO t_employee_vacation_period "
                                    "(i_employee, dt_begin, dt_end) "
                                        "VALUES(:i_employee, :dt_begin, :dt_end);"
                        			  				  );
	const QString data_adapter_vacation_period::_s_sql_delete(
								"DELETE FROM t_employee_vacation_period "
								"WHERE ((i_employee=:i_employee)AND"
                                        "(dt_begin=:dt_begin)AND"
                                        "(dt_end=:dt_end));"
									);
	const QString data_adapter_vacation_period::_s_sql_select(
                                "SELECT i_employee, dt_begin, dt_end "
                                       "FROM t_employee_vacation_period "
                                                    );

/// ############################################################################
///			class data_adapter_vacation_period
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	~data_adapter_vacation_period( )
	/// ------------------------------------------------------------------------
	data_adapter_vacation_period::~data_adapter_vacation_period( )
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
	void data_adapter_vacation_period::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

	/// ------------------------------------------------------------------------
	///	cmd_params_insert
    /// ------------------------------------------------------------------------
	void data_adapter_vacation_period::append_cmd_params(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_vacation_period &r
                                             ) const
	{
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_employee( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.text_date_begin( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.text_date_end( ) ) );
	}

    /// ------------------------------------------------------------------------
	///	make_filter( const int id_employee ) const
    /// ------------------------------------------------------------------------
	QString data_adapter_vacation_period::make_filter(
                                                        const int id_employee,
                                                        const int n_year
                                                     ) const
	{
		QString s_filter = "((i_employee=" +
                            QString::number( id_employee ) +")AND";

        QDate dt_begin( n_year, 1, 1 );
        s_filter += "(dt_begin >= \'" + dt_begin.toString( "yyyy-MM-dd" ) + "\')AND";

        QDate  dt_end( n_year, 12, 31 );
        s_filter += "(dt_end <= \'" + dt_end.toString( "yyyy-MM-dd" ) + "\'))";

		return s_filter;
	}

	/// ------------------------------------------------------------------------
	///	make_select_qry(const int id_employee, const int n_year) const
    /// ------------------------------------------------------------------------
    QString data_adapter_vacation_period::make_select_qry(
                                                          const int id_employee,
                                                          const int n_year
                                                         ) const
    {
        QString s_qry( data_adapter_vacation_period::_s_sql_select );

        QString s_filter = this->make_filter( id_employee, n_year );
        if( s_filter.length( ) )
        {
            s_qry += "WHERE " + s_filter + ";";
        }

        return s_qry;
    }

	/// ------------------------------------------------------------------------
	///	select( const int id_employee ) const
    /// ------------------------------------------------------------------------
    data_vacation_period_collection*
		data_adapter_vacation_period::select( const int id_employee, const int n_year ) const
	{
		//make select query
        QString s_qry = make_select_qry( id_employee, n_year );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_vacation_period_collection *emp_coll = 0;
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
                emp_coll = new data_vacation_period_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end( ); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    emp_coll->append( new data_vacation_period( r ) );
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
	///	insert( const data_vacation_period &vp ) const
	/// ------------------------------------------------------------------------
	void data_adapter_vacation_period::insert( const data_vacation_period &vp ) const
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
            pcmd = cnn.create_command( data_adapter_vacation_period::_s_sql_insert );
            //add parameters
            this->append_cmd_params( pcmd, vp );
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
	///	del( const data_vacation_period &vp ) const
    /// ------------------------------------------------------------------------
	void data_adapter_vacation_period::del( const data_vacation_period &vp ) const
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
            pcmd = cnn.create_command( data_adapter_vacation_period::_s_sql_delete );
            this->append_cmd_params( pcmd, vp );
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

