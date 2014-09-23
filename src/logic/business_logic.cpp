/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 06-11-2013
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QThread>

#include "business_logic.h"

#include "data_model_employee.h"

#include "data_adapter_employee.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class business_logic
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

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
    ///	free_memory( )
    /// ------------------------------------------------------------------------
    void business_logic::free_memory( )
    {
        if( this->_model_employee )
        {
            delete _model_employee;
        }
    }
	/// ------------------------------------------------------------------------
	///	init( )
    /// ------------------------------------------------------------------------
	void business_logic::init( )
	{
		try
		{
            this->init_data_models( );
		}
		catch( std::exception &ex )
		{
			QString s_msg(
							"business_logic::init( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
			QString s_msg(
						"business_logic::init( )"
						":\n\t unknown error while initialize business logic"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
	}
	/// ------------------------------------------------------------------------
	///	exit( )
    /// ------------------------------------------------------------------------
	void business_logic::exit( )
	{
        this->free_memory( );

		qDebug( ) << "correctly exiting business logic";
	}
    /// ------------------------------------------------------------------------
	///	init_data_models( )
    /// ------------------------------------------------------------------------
    void business_logic::init_data_models( )
    {
        this->init_model_employee( );
    }
	/// ------------------------------------------------------------------------
	///	init_model_employee( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_employee( )
    {
        this->_model_employee = new data_model_employee;
        this->employee_select( );
    }
    /// ------------------------------------------------------------------------
	///	employee_select( )
    /// ------------------------------------------------------------------------
    void business_logic::employee_select( )
    {
        qDebug() << "employee_select in thread ID: " << this->thread( )->objectName( );
        if( !this->_db_path.length( ) )
        {
            return;
        }
        data_employee_collection *p_coll = 0;
        try
		{
            data_adapter_employee ap_emp;
			//select data
			p_coll = ap_emp.select( );
			//refresh data model
			this->_model_employee->refresh( p_coll );
		}
		catch( std::exception &ex )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
							"business_logic::employee_select( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
						"business_logic::employee_select( )"
						":\n\t unknown error while employees select"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
    }

   /// ------------------------------------------------------------------------
   ///	employee_insert( const data_employee& employee )
   /// ------------------------------------------------------------------------
   bool business_logic::employee_insert( data_employee& employee )
   {
       if( !this->_db_path.length( ) )
       {
           return false;
       }
       try
       {
           data_adapter_employee ap_employee;

           employee.id_employee( ap_employee.new_id( ) );
           ap_employee.insert( employee );
           if( this->_model_employee )
           {
                this->_model_employee->insert_employee( employee );
           }
       }
       catch( std::exception &ex )
       {
           QString s_msg(
                           "business_logic::employee_insert( )"
                           ":\n\t" + QString::fromUtf8( ex.what( ) )
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }
       catch( ... )
       {
           QString s_msg(
                       "business_logic::employee_insert( )"
                       ":\n\t unknown error while employee inserting"
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }

       return true;
   }

   /// ------------------------------------------------------------------------
   ///	employee_update( const data_employee& employee )
   /// ------------------------------------------------------------------------
   bool business_logic::employee_update( const data_employee& employee )
   {
       if( !this->_db_path.length( ) )
       {
           return false;
       }
       try
       {
           data_adapter_employee ap_employee;
           ap_employee.update( employee );
           if( this->_model_employee )
           {
                this->_model_employee->update_employee( employee );
           }
       }
       catch( std::exception &ex )
       {
           QString s_msg(
                           "business_logic::employee_update( )"
                           ":\n\t" + QString::fromUtf8( ex.what( ) )
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }
       catch( ... )
       {
           QString s_msg(
                       "business_logic::employee_update( )"
                       ":\n\t unknown error while employee updating"
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }

       return true;
   }

   /// ------------------------------------------------------------------------
   ///	employee_delete( const int id_employee )
   /// ------------------------------------------------------------------------
   bool business_logic::employee_delete( const int id_employee )
   {
       if( !this->_db_path.length( ) )
       {
           return false;
       }
       try
       {
           data_adapter_employee ap_employee;
           ap_employee.del( id_employee );
           if( this->_model_employee )
           {
                this->_model_employee->delete_employee( id_employee );
           }
       }
       catch( std::exception &ex )
       {
           QString s_msg(
                           "business_logic::employee_delete( )"
                           ":\n\t" + QString::fromUtf8( ex.what( ) )
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }
       catch( ... )
       {
           QString s_msg(
                       "business_logic::employee_delete( )"
                       ":\n\t unknown error while employee deleting"
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }

       return true;
   }

    /// ========================================================================
	///		SLOTS
    /// ========================================================================

/// ############################################################################

}//   namespace employee_vacation

}//   namespace rele_auto
