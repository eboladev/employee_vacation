/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 01-10-2014
///		Comment		:
/// ============================================================================
#include <QAbstractItemView>
#include <QHeaderView>
#include <QItemDelegate>
#include <QScrollBar>

#include "application.h"
#include "business_logic.h"

#include "data_model_employee.h"

#include "listview_employee.h"
#include "delegate_line_edit.h"

namespace rele_auto
{

namespace employee_vacation
{

/// ############################################################################
///			class listview_employee
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
	///	listview_employee( )
	/// ------------------------------------------------------------------------
	listview_employee::listview_employee( QWidget *parent ) :
		QTableView( parent )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
	///	~listview_employee( )
	/// ------------------------------------------------------------------------
	listview_employee::~listview_employee( )
	{
		this->setModel( 0 );
	}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	/// -----------------------------------------------------------------------
	///	current_employee( )
	/// -----------------------------------------------------------------------
    const data_employee* listview_employee::current_employee( )
	{
		QModelIndex idx = this->selectionModel( )->currentIndex( );
		if( !idx.isValid( ) )
		{
			return 0;
		}
		return application::the_business_logic( ).
							model_employee( )->employee( idx.row( ) );
	}

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	initialize( )
	/// ------------------------------------------------------------------------
    void listview_employee::initialize( )
	{
		this->init_view( );

		this->init_connections( );
	}

	/// ------------------------------------------------------------------------
	///	init_view( )
	/// ------------------------------------------------------------------------
    void listview_employee::init_view( )
    {
        this->setShowGrid( true );
		this->setGridStyle( Qt::DotLine );
		this->horizontalHeader( )->setVisible( true );
		this->horizontalHeader( )->setClickable( true );
		this->verticalHeader( )->setVisible( true );
		this->verticalHeader( )->setClickable( true );

		this->setModel(
				application::the_business_logic( ).model_employee( )
					  );

		this->setSelectionMode( QAbstractItemView::SingleSelection );
		this->setSelectionBehavior( QAbstractItemView::SelectRows );

		this->setItemDelegate( new espira::gui::delegate_line_edit );
    }

	/// ------------------------------------------------------------------------
	///	init_connections( )
	/// ------------------------------------------------------------------------
    void listview_employee::init_connections( )
    {
        if( this->selectionModel( ) )
        {
            this->connect(
                       this->selectionModel( ), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                       this, SLOT( selected_item_changed( ) )
                         );
        }
    }

	/// ========================================================================
	///		SLOTS
	/// ========================================================================
    void listview_employee::selected_item_changed( )
    {
        const data_employee *employee = this->current_employee( );
        if( employee != 0 )
        {
            emit current_item_changed( employee );
        }
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    void listview_employee::resizeEvent( QResizeEvent *event )
    {
        QTableView::resizeEvent( event );
        if( !this->model( ) )
        {
            return;
        }
        int i_correct = 0;
        if( this->verticalScrollBar( ) )
        {
            i_correct = this->verticalScrollBar( )->width( ) - 1;
        }
        this->setColumnWidth( 0, this->width( ) - i_correct );
    }

/// ############################################################################

}//namespace employee_vacation

}//namespace rele_auto
