/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-09-2013
///		Date update	: 01-10-2013
///		Comment		:
/// ============================================================================
#include <QApplication>
#include <QDesktopWidget>

#include "main_window.h"
#include "widget_central.h"

namespace rele_auto
{

namespace employee_vacation
{

/// ############################################################################
///			class main_window
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
	///	main_window( )
	/// ------------------------------------------------------------------------
	main_window::main_window( QWidget *parent ) :
		QMainWindow( parent )
	{
		this->initialize( );
	}


	/// ------------------------------------------------------------------------
	///	~main_window( )
	/// ------------------------------------------------------------------------
	main_window::~main_window( )
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
	///	initialize( )
	/// ------------------------------------------------------------------------
	void main_window::initialize( )
	{
        this->setWindowTitle( tr("app_employee_vacation") );

        this->setMinimumSize( 1025, 820 );
		this->window_center( );
		//_workspace
        this->_workspace = new widget_central( this );
		this->setCentralWidget( this->_workspace );
	}

	/// ------------------------------------------------------------------------
	///	window_center( )
	/// ------------------------------------------------------------------------
	void main_window::window_center( )
	{
		QDesktopWidget *desktop = QApplication::desktop( );
		this->move(
					( desktop->geometry( ).width( ) -
						this->frameGeometry( ).width( ) )/2,
					( desktop->geometry( ).height( ) -
						this->frameGeometry( ).height( ) )/2
				  );
	}

	/// ========================================================================
	///		SLOTS
	/// ========================================================================

/// ############################################################################

}//namespace employee_vacation

}//namespace rele_auto