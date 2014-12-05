/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-01-2013
///		Date update	: 05-12-2014
///		Comment		:
/// ============================================================================

#include <QDebug>
#include <QDate>
#include <QMessageBox>

#include "data_model_month.h"

namespace rele_auto
{

namespace employee_vacation
{
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
        _month( QDate::currentDate( ).month( ) ),
        _data( 0 )
	{
		this->initialize( );
	}

    /// ------------------------------------------------------------------------
    ///	data_model_month( int year, int month )
    /// ------------------------------------------------------------------------
    data_model_month::data_model_month(  int year, int month,
                                         QObject *pobj/* = 0*/ ) :
        QAbstractTableModel( pobj ),
        _year( year ),
        _month( month ),
        _data( 0 )
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

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	clear( )
    /// ------------------------------------------------------------------------
    void data_model_month::clear( )
	{
        if( this->_data )
        {
            delete _data;
        }
        this->_data = 0;
	}

    /// ------------------------------------------------------------------------
    ///	requery( )
    /// ------------------------------------------------------------------------
    void data_model_month::requery( )
    {
        this->clear( );
        try
        {
            calendar_data::month_type month =
                    static_cast<calendar_data::month_type>( this->_month );
            this->_data = new calendar_data( this->_year, month );
        }
        catch( std::exception &ex )
        {
            QMessageBox::warning(0, QObject::tr( "Warning" ), QString( ex.what( ) ) );
            this->_data = 0;
        }
        catch( ... )
        {
            QMessageBox::warning(0, QObject::tr( "Warning" ), QString( "ups-s..." ) );
        }
    }

    /// ------------------------------------------------------------------------
    ///	initialize( )
    /// ------------------------------------------------------------------------
    void data_model_month::initialize( )
	{
        this->requery( );
	}

    /// ------------------------------------------------------------------------
    ///	initialize( )
    /// ------------------------------------------------------------------------
    const calendar_item* data_model_month::item( const QModelIndex &index ) const
    {
        if( !index.isValid( ) || !this->_data )
        {
            return 0;
        }
        return this->_data->item( index.row( ), index.column( ) );
    }

    /// ------------------------------------------------------------------------
    /// virtual
	///	data( )
    /// ------------------------------------------------------------------------
    QVariant data_model_month::data(
                                    const QModelIndex &index,
                                    int /*role //= Qt::DisplayRole*/
                                   ) const
	{
        const calendar_item *ci = this->item( index );
        if( !ci )
        {
            return QVariant( );
        }
        return ci->text( );
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
    Qt::ItemFlags data_model_month::flags(const QModelIndex &index ) const
	{
        if( !index.isValid( ) )
        {
            return Qt::NoItemFlags;
        }
        const int header_rows = 2;
        if( index.row() < header_rows )
        {
            return Qt::ItemIsEnabled;
        }
        const calendar_item *ci = this->item( index );
        if( !ci )
        {
            return Qt::NoItemFlags;
        }

        if( ci->text( ).length( ) )
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }

        return Qt::ItemIsEnabled;
	}

    /// ------------------------------------------------------------------------
    ///	set_vacation_days( const QModelIndexList &list_indexes )
    /// ------------------------------------------------------------------------
    void data_model_month::set_vacation_days( const QModelIndexList &list_indexes )
    {
        if( !this->_data )
        {
            return;
        }
        try
        {
            QModelIndexList::const_iterator it = list_indexes.begin();
            for( ; it < list_indexes.end( ); ++it )
            {
                const QModelIndex &idx = *it;
                if( idx.isValid( ) )
                {
                    this->_data->set_vacation( idx.row( ), idx.column( ) );
                }
            }
        }
        catch( std::exception &ex )
        {
            qDebug( ) << "data_model_month::set_vacation_days\t"
                   << QString::fromStdString( ex.what( ) );
        }
    }

    /// ------------------------------------------------------------------------
    ///	unset_vacation_days( const QModelIndexList &list_indexes )
    /// ------------------------------------------------------------------------
    void data_model_month::unset_vacation_days( const QModelIndexList &list_indexes )
    {
        if( !this->_data )
        {
            return;
        }
        try
        {
            QModelIndexList::const_iterator it = list_indexes.begin();
            for( ; it < list_indexes.end( ); ++it )
            {
                const QModelIndex &idx = *it;
                if( idx.isValid( ) )
                {
                    this->_data->unset_vacation( idx.row( ), idx.column( ) );
                }
            }
        }
        catch( std::exception &ex )
        {
            qDebug( ) << "data_model_month::set_vacation_days\t"
                   << QString::fromStdString( ex.what( ) );
        }
    }

    /// ------------------------------------------------------------------------
    ///	set_vacation_days( const QDate &dt_begin, const QDate &dt_end )
    /// ------------------------------------------------------------------------
    void data_model_month::set_vacation_days( const QDate &dt_begin, const QDate &dt_end )
    {
        if( !this->_data )
        {
            return;
        }
        try
        {
        /*
            QModelIndexList::const_iterator it = list_indexes.begin();
            for( ; it < list_indexes.end( ); ++it )
            {
                const QModelIndex &idx = *it;
                if( idx.isValid( ) )
                {
                    this->_data->set_vacation( idx.row( ), idx.column( ) );
                }
            }
            */
        }
        catch( std::exception &ex )
        {
            qDebug( ) << "data_model_month::set_vacation_days\t"
                   << QString::fromStdString( ex.what( ) );
        }
    }

    /// ------------------------------------------------------------------------
    ///	unset_vacation_days( const QDate &dt_begin, const QDate &dt_end )
    /// ------------------------------------------------------------------------
    void data_model_month::unset_vacation_days( const QDate &dt_begin, const QDate &dt_end )
    {

    }

/// ############################################################################
}//namespace employee_vacation

}//namespace rele_auto

