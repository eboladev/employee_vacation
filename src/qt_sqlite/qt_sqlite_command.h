//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 10-06-2013
//		Date update	: 20-06-2013
//		Comment		:
//=============================================================================
#ifndef __QT_SQLITE_COMMAND_H__
#define __QT_SQLITE_COMMAND_H__

#include <QString>

#include "qt_data_row.h"
#include "qt_data_parameter.h"

class sqlite3;
class sqlite3_stmt;

namespace espira
{

namespace db
{

class qt_sqlite_connection;

//#############################################################################
//			class qt_sqlite_command
//#############################################################################
    class qt_sqlite_command
	{
        friend class qt_sqlite_connection;
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	private:
        qt_sqlite_command( const qt_sqlite_command &rhs );

		//---------------------------------------------------------------------
        qt_sqlite_command( ) :
			_conn( 0 ),
			_pdb( 0 ),
			_p_stmt( 0 )
		{
		}

	public:
		//---------------------------------------------------------------------
        virtual ~qt_sqlite_command( );

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	private:
        //---------------------------------------------------------------------
        void bind_parameters( );
        //---------------------------------------------------------------------
        void command_error( const std::string &err );
        //---------------------------------------------------------------------
        void fill_query_result( );
        //---------------------------------------------------------------------
        void fill_query_result_2( );

	public:
		//---------------------------------------------------------------------
        void open( );
		//---------------------------------------------------------------------
        void reset( );
        //---------------------------------------------------------------------
        void execute( );
        //---------------------------------------------------------------------
        void execute_2( );
        //---------------------------------------------------------------------
        const QVariant& execute_scalar( );
        //---------------------------------------------------------------------
        void close( );

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	private:

	public:
        //---------------------------------------------------------------------
        const QString& command_text( ) const
        { return this->_cmd_text; }
        //---------------------------------------------------------------------
        void command_text( const QString &s_cmd_text )
        { this->_cmd_text = s_cmd_text; }
        //---------------------------------------------------------------------
        qt_data_parameter_collection& parameters( )
        { return this->_params; }
        //---------------------------------------------------------------------
        qt_data_row_collection& result( )
        { return this->_last_result; }

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
        qt_sqlite_command& operator=( const qt_sqlite_command &rhs );

	public:

	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
		//указатель на объект соединения с БД
        const qt_sqlite_connection  *_conn;
		//указатель на объект sqlite3 API структуры соединения с БД
        sqlite3                     *_pdb;
		//указатель на структуру запроса sqlite3 API
        sqlite3_stmt                *_p_stmt;
        //command text
        QString                     _cmd_text;

        //параметры запроса
        qt_data_parameter_collection    _params;
		//результат последнего выполненного запроса
        qt_data_row_collection          _last_result;
        //результат последней выборки одного значения
        QVariant                        _last_scalar;

	};
    //class qt_sqlite_command
//#############################################################################
//-----------------------------------------------------------------------------

}//namespace db

}//namespace espira

#endif // __QT_SQLITE_COMMAND_H__