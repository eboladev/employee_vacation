/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 10-12-2014
///		Comment		:
/// ============================================================================
#ifndef __BUSINESS_LOGIC_H__
#define __BUSINESS_LOGIC_H__

#include <QObject>

namespace rele_auto
{

namespace employee_vacation
{

class data_model_employee;
class data_employee;
class data_vacation_period;
class data_vacation_period_collection;

class application;
/// ############################################################################
///			class business_logic
/// ############################################################################
	class business_logic : public QObject
	{
	Q_OBJECT

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		business_logic( const business_logic &rhs );

    public:
	/// ------------------------------------------------------------------------
		business_logic( ) :
            QObject( 0 ),
            _db_path( "" ),
            _model_employee( 0 )
		{ }

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    /// db_path( )
        const QString& db_path( ) const
        { return this->_db_path; }

        void db_path( const QString& db_path )
        { this->_db_path = db_path; }
    /// ------------------------------------------------------------------------
        data_model_employee* model_employee( ) const
        { return this->_model_employee; }
	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        void init_data_models( );
	/// ------------------------------------------------------------------------
        void init_model_employee( );
    /// ------------------------------------------------------------------------
        void free_memory( );

	public:
    /// ------------------------------------------------------------------------
        void init( );
	/// ------------------------------------------------------------------------
		void exit( );
	/// ------------------------------------------------------------------------
        void employee_select( );
    /// ------------------------------------------------------------------------
        bool employee_insert(data_employee &employee);
    /// ------------------------------------------------------------------------
        bool employee_update(const data_employee &employee);
    /// ------------------------------------------------------------------------
        bool employee_delete(const int id_employee);
    /// ------------------------------------------------------------------------
        data_vacation_period_collection* vacation_period_select(int id_employee, int n_year);
    /// ------------------------------------------------------------------------
        data_vacation_period* vacation_period_select_last(int id_employee, int n_year);
    /// ------------------------------------------------------------------------
        bool vacation_period_insert( const data_vacation_period &vp );
    /// ------------------------------------------------------------------------
        bool vacation_period_delete( const data_vacation_period &vp );

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
		business_logic& operator=( const business_logic &rhs );

	public:

	/// ========================================================================
	///		FIELDS
    /// ========================================================================
    private:
        QString _db_path;

        data_model_employee *_model_employee;

	};//class business_logic

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace employee_vacation

}//namespace rele_auto

#endif // __BUSINESS_LOGIC_H__
