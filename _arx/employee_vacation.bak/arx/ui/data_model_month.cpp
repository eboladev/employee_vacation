/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-01-2013
///		Date update	: 30-01-2013
///		Comment		:
/// ============================================================================

#include <QDebug>
#include <QDate>

#include "data_model_month.h"

namespace rele_auto
{

namespace employee_vacation
{
    const int data_model_month::_columns_count = 7;
    const int data_model_month::_rows_count = 7;
/// ############################################################################
///			class data_model_month
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	data_model_month( )
    /// ------------------------------------------------------------------------
    data_model_month::data_model_month( QObject *pobj/* = 0*/ ) :
        QAbstractTableModel( pobj ),
        _year( QDate::currentDate( ).year( ) ),
        _month( QDate::currentDate( ).month( ) )
	{
		this->initialize( );
	}

    /// ------------------------------------------------------------------------
    ///	~data_model_month( )
    /// ------------------------------------------------------------------------
    data_model_month::~data_model_month( )
	{
		this->clear( );

        qDebug( ) << "data_model_month cleared correctly";
	}

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	recipient( int i_row )
    /// ------------------------------------------------------------------------
    /*
    const data_recipient* data_model_month::recipient( int i_row ) const
	{
		if( i_row < 0 || i_row >= this->_list.size( ) )
		{
			return 0;
		}
		return this->_list.at( i_row );
	}
*/
    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	clear( )
    /// ------------------------------------------------------------------------
    void data_model_month::clear( )
	{
        /*
		this->removeRows( 0, this->_list.size( ) );
		this->_list.clear( );
        */
	}

    /// ------------------------------------------------------------------------
    ///	initialize( )
    /// ------------------------------------------------------------------------
    void data_model_month::initialize( )
	{
//		this->init_columns_header( );
	}

    /// ------------------------------------------------------------------------
    ///	refresh( const QVector<QVector<QVariant> > &data )
    /// ------------------------------------------------------------------------
    /*
    void data_model_month::refresh(const QVector<QVector<QVariant> > &data)
	{
		this->clear( );

		if( !data.count( ) )
		{
			//if no data
			return;
		}

		this->beginInsertRows( QModelIndex( ), 0, data.count( ) - 1 );

		QVector<QVector<QVariant> >::const_iterator iter;
		for( iter = data.constBegin( ); iter != data.end( ); ++iter )
		{
			data_recipient *recipient = new data_recipient( *iter );
			this->_list.append( recipient );
		}
		this->endInsertRows( );
	}
*/
    /// ------------------------------------------------------------------------
    /*
    void data_model_month::refresh( data_recipient_collection *data )
	{
		this->clear( );

		if( !data || !data->size( ) )
		{
			//if no data
			return;
		}
		this->beginInsertRows( QModelIndex( ), 0, data->size( ) - 1 );

		this->_list.append( *( data->list( ) ) );
		data->free_data_pointer( );

		this->endInsertRows( );
	}
*/
    /// ------------------------------------------------------------------------
    /// virtual
	///	data( )
    /// ------------------------------------------------------------------------
    QVariant data_model_month::data(
										const QModelIndex &index,
										int /*role //= Qt::DisplayRole*/
									   ) const
	{
        const int row_header_month = 0;
        const int row_header_days = 1;
        const int rows_before_calendar = 2;
        const QDate date_of_calendar( this->_year, this->_month, 1 );

        if( !index.isValid( ) )
		{
			return QVariant( );
		}
        if( index.row( ) == row_header_month )
        {
            return  index.column( ) == 0
                        ?
                        QDate::longMonthName(this->_month, QDate::DateFormat )
                        :
                        QVariant( );
        }
        if( index.row( ) == row_header_days )
        {
            //days nums starting from 1
            return  QDate::shortDayName( index.column( ) + 1, QDate::DateFormat );
        }

        int row = index.row( ) - rows_before_calendar;
        const int start_month_day = date_of_calendar.dayOfWeek( );
        const int days_in_week = 7;
        int day = row * days_in_week + index.column( ) - start_month_day + 2;
        if( day <= 0 || day > date_of_calendar.daysInMonth( ) )
        {
            day = 0;
        }
        return day > 0 ? QString( "%1" ).arg( day, 2, 10, QLatin1Char('0') ) : QVariant( );
	}

    /// ------------------------------------------------------------------------
    /// virtual
	///	setData( )
    /// ------------------------------------------------------------------------
    bool data_model_month::setData(
										const QModelIndex &/*index*/,
										const QVariant &/*value*/,
										int /*role //= Qt::EditRole*/
									  )
	{
		return false;
	}

    /// ------------------------------------------------------------------------
    /// virtual
	///	flags( )
    /// ------------------------------------------------------------------------
    Qt::ItemFlags data_model_month::flags(const QModelIndex &/*index*/) const
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

/*
//remove all
		QList<data_recipient*>::iterator it = this->_list.begin( );
		while( it != this->_list.end( ) )
		{
			data_recipient *item = *it;
			delete item;
			it = this->_list.erase( it );
		}
*/


/// ############################################################################
}//namespace employee_vacation

}//namespace rele_auto

