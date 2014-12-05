/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-01-2013
///		Date update	: 05-12-2014
///		Comment		:
/// ============================================================================

#include <QHeaderView>
#include <QMenu>
#include <QMessageBox>

#include <QPaintEngine>
#include <QPaintDevice>
#include <QPainter>
#include <QResizeEvent>

#include "tableview_month_calendar.h"
#include "calendar_item_delegate.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class tableview_month_calendar
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	tableview_month_calendar( )
    /// ------------------------------------------------------------------------
    tableview_month_calendar::tableview_month_calendar(
                                                        int year, int month,
                                                        QWidget *parent /*= 0*/
                                                      ) :
        QTableView( parent )
    {
        try
        {
            this->_model = new data_model_month( year, month );
            this->setModel( this->_model );
        }
        catch( std::exception &ex )
        {
            this->_model = 0;
            this->setModel( 0 );

            QMessageBox::warning(
                                0, QObject::tr( "Warning" ),
                                QString::fromStdString( ex.what( ) )
                                );
        }

        this->initialize( );
    }

    /// ------------------------------------------------------------------------
    ///	~tableview_month_calendar( )
    /// ------------------------------------------------------------------------
    tableview_month_calendar::~tableview_month_calendar( )
    {
        if( this->_model )
        {
            delete _model;
        }
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
    /// initialize( )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::initialize( )
    {
        this->init_layout( );

        this->init_signal_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::init_layout()
    {
        this->setShowGrid( true );
        this->setGridStyle( Qt::DotLine );
        this->horizontalHeader( )->setVisible( false );
        this->verticalHeader( )->setVisible( false );

        this->setSpan( 0, 0, 1, Qt::Sunday );
        this->setItemDelegate( new calendar_item_delegate );

        this->setBackgroundRole( QPalette::Window );
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::init_signal_connections( )
    {
        if( this->selectionModel( ) )
        {
            this->connect(
                            this->selectionModel( ),
                            SIGNAL( selectionChanged( QItemSelection, QItemSelection ) ),
                            this,
                            SLOT( periods_changed( ) )
                         );
        }
    }

    /// ------------------------------------------------------------------------
    /// min_column_width( )
    /// ------------------------------------------------------------------------
    int  tableview_month_calendar::min_column_width( ) const
    {
        return this->fontMetrics( ).boundingRect("WWW").width( );
    }

    /// ------------------------------------------------------------------------
    /// min_row_height( )
    /// ------------------------------------------------------------------------
    int  tableview_month_calendar::min_row_height( ) const
    {
        return this->fontMetrics( ).boundingRect("WgplQЁЙ").height( );
    }

    /// ------------------------------------------------------------------------
    /// correct_columns_width( )
    /// ------------------------------------------------------------------------
    int tableview_month_calendar::correct_columns_width( )
    {
        QAbstractItemModel *model = this->model( );
        if( !model )
        {
            return 0;
        }

        int n_widget_width = 0;
        int n_new_width = this->min_column_width( );
        for( int i = 0; i < model->columnCount( ); ++i )
        {
            this->setColumnWidth( i, n_new_width );
            n_widget_width += n_new_width + 1;//+1 for cell frame
        }
        this->setMinimumWidth(n_widget_width);

        return n_widget_width;
    }

    /// ------------------------------------------------------------------------
    /// correct_rows_height( )
    /// ------------------------------------------------------------------------
    int tableview_month_calendar::correct_rows_height( )
    {
        QAbstractItemModel *model = this->model( );
        if( !model )
        {
            return 0;
        }

        int n_widget_height = 0;
        int n_new_height = this->min_row_height( );
        for( int i = 0; i < model->rowCount( ); ++i )
        {
            this->setRowHeight( i, n_new_height );
            n_widget_height += n_new_height + 1; //+ 1 for cell frame
        }
        this->setMinimumHeight(n_widget_height);

        return n_widget_height;
    }

    /// ------------------------------------------------------------------------
    /// correct_size( )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::correct_size( )
    {
        QAbstractItemModel *model = this->model( );
        if( this->isVisible( ) && model )
        {
            this->resize(
                         this->correct_columns_width( ),
                         this->correct_rows_height( )
                        );
        }
    }

    /// ------------------------------------------------------------------------
    /// set_vacation( const QDate &dt_begin, const QDate &dt_end )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::set_vacation( const QDate &dt_begin, const QDate &dt_end )
    {
        QAbstractItemModel *model = this->model( );
        if( model )
        {
            data_model_month *dmm = static_cast<data_model_month*>( model );
            dmm->set_vacation_days( dt_begin, dt_end );
        }
    }

    /// ------------------------------------------------------------------------
    /// unset_vacation( const QDate &dt_begin, const QDate &dt_end )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::unset_vacation( const QDate &dt_begin, const QDate &dt_end )
    {
        QAbstractItemModel *model = this->model( );
        if( model )
        {
            data_model_month *dmm = static_cast<data_model_month*>( model );
            dmm->unset_vacation_days( dt_begin, dt_end );
        }
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// resizeEvent( QResizeEvent *event )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::resizeEvent( QResizeEvent *event )
    {
        QTableView::resizeEvent( event );
        this->correct_size( );
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// show_context_menu( const QPoint &/*pos*/ )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::show_context_menu( const QPoint &pos )
    {
        // this->_menu_context->popup( this->mapToGlobal(pos) );
    }

    /// ------------------------------------------------------------------------
    /// periods_changed( )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::periods_changed( )
    {
        //save selected periods into collection
    }

    /// ------------------------------------------------------------------------
    /// set_vacation( )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::set_vacation( )
    {
        QAbstractItemModel *model = this->model( );
        if( model )
        {
            data_model_month *dmm = static_cast<data_model_month*>( model );
            dmm->set_vacation_days( this->selectionModel( )->selectedIndexes( ) );
            this->selectionModel( )->clear( );
        }
    }

    /// ------------------------------------------------------------------------
    /// unset_vacation( )
    /// ------------------------------------------------------------------------
    void tableview_month_calendar::unset_vacation( )
    {
        QAbstractItemModel *model = this->model( );
        if( model )
        {
            data_model_month *dmm = static_cast<data_model_month*>( model );
            dmm->unset_vacation_days( this->selectionModel( )->selectedIndexes( ) );
            this->selectionModel( )->clear( );
        }
    }

/// ############################################################################

}// namespace employee_vacation

}//namespace rele_auto
