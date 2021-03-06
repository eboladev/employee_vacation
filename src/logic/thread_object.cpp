/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 06-11-2013
///		Date update	: 06-11-2013
///		Comment		:
/// ============================================================================

#include <QDebug>

#include "thread_object.h"

namespace espira
{

/// ############################################################################
///			class thread_object
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	thread_object( )
    /// ------------------------------------------------------------------------
	thread_object::thread_object( ) :
        QThread( 0 ),
        _x_title( "" )
	{
        qDebug( ) << "thread_object created";

        this->connect(
                      this, SIGNAL( started( ) ),
                      this, SLOT( thread_started( ) )
                     );
        this->connect(
                      this, SIGNAL( finished( ) ),
                      this, SLOT( thread_finished( ) )
                     );
        this->connect(
                      this, SIGNAL( terminated( ) ),
                      this, SLOT( thread_terminated( ) )
                     );
	}

    /// ------------------------------------------------------------------------
	///	~thread_object( )
    /// ------------------------------------------------------------------------
	thread_object::~thread_object( )
	{
        qDebug( ) << "thread_object destroyed";
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

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	thread_started( )
    /// ------------------------------------------------------------------------
    void thread_object::thread_started( )
    {
        qDebug( ) << "thread " << this->_x_title << " is started";
    }

    /// ------------------------------------------------------------------------
	///	thread_finished( )
    /// ------------------------------------------------------------------------
    void thread_object::thread_finished( )
    {
        qDebug( ) << "thread " << this->_x_title << " is finished";
    }

    /// ------------------------------------------------------------------------
	///	thread_terminated( )
    /// ------------------------------------------------------------------------
    void thread_object::thread_terminated( )
    {
        qDebug( ) << "thread " << this->_x_title << " is terminated";
    }

/// ############################################################################

}//namespace espira
