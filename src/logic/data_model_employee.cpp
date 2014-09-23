/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 15-10-2013
///		Comment		:
/// ============================================================================
#include <QDebug>

#include "data_model_employee.h"
#include "data_adapter_employee.h"

namespace rele_auto
{

namespace employee_vacation
{

/// ############################################################################
///			class data_model_employee
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// -----------------------------------------------------------------------
	///	data_model_employee( )
    /// -----------------------------------------------------------------------
	data_model_employee::data_model_employee( QObject *pobj/* = 0*/ ) :
		QAbstractTableModel( pobj )
	{
		this->initialize( );
	}

    /// -----------------------------------------------------------------------
	///	~data_model_employee( )
    /// -----------------------------------------------------------------------
	data_model_employee::~data_model_employee( )
	{
		this->clear( );

		qDebug( ) << "data_model_employee cleared correctly";
	}

    /// ========================================================================
	///		PROPERTIES
    /// ========================================================================
    /// -----------------------------------------------------------------------
	///	employee( int i_row )
    /// -----------------------------------------------------------------------
	const data_employee* data_model_employee::employee( int i_row ) const
	{
		if( i_row < 0 || i_row >= this->_list.size( ) )
		{
			return 0;
		}
		return this->_list.at( i_row );
	}

    /// ========================================================================
	///		FUNCTIONS
    /// ========================================================================
    /// -----------------------------------------------------------------------
	///	clear( )
    /// -----------------------------------------------------------------------
	void data_model_employee::clear( )
	{
        if( !this->_list.size( ) )
        {
            return;
        }
		this->removeRows( 0, this->_list.size( ) );
		this->_list.clear( );
		this->_hash.clear( );
	}

    /// -----------------------------------------------------------------------
	///	initialize( )
    /// -----------------------------------------------------------------------
	void data_model_employee::initialize( )
	{
		this->init_columns_header( );
	}

    /// -----------------------------------------------------------------------
	///	refresh( const QVector<QVector<QVariant> > &data )
    /// -----------------------------------------------------------------------
	void data_model_employee::refresh(const QVector<QVector<QVariant> > &data)
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
			data_employee *employee = new data_employee( *iter );
			this->_list.append( employee );
			this->_hash.insert( employee->id_employee( ), employee );
		}
		this->endInsertRows( );
	}

    /// -----------------------------------------------------------------------
    ///	refresh( data_employee_collection *data )
    /// -----------------------------------------------------------------------
	void data_model_employee::refresh( data_employee_collection *data )
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
		this->list_into_hash( );

        this->endInsertRows( );
    }

    /// -----------------------------------------------------------------------
    ///	list_into_hash( )
    /// -----------------------------------------------------------------------
    void data_model_employee::list_into_hash( )
    {
        data_employee_list::iterator it = this->_list.begin( );
        for( ; it < this->_list.end( ); ++it )
        {
            data_employee *pe = *it;
            this->_hash.insert( pe->id_employee( ), pe );
		}
    }

    /// -----------------------------------------------------------------------
    ///	insert_employee(const data_employee &employee)
    /// -----------------------------------------------------------------------
    void data_model_employee::insert_employee(const data_employee &employee)
    {
        int row_count = this->_list.size( );
		this->beginInsertRows( QModelIndex( ), row_count, row_count );

        data_employee *pe = new data_employee( employee );
		this->_list.append( pe );
		this->_hash.insert( pe->id_employee( ), pe );

        this->endInsertRows( );
    }

    /// -----------------------------------------------------------------------
    ///	update_employee(const data_employee &employee)
    /// -----------------------------------------------------------------------
    void data_model_employee::update_employee(const data_employee &employee)
    {
        data_employee *pe = this->find_employee( employee.id_employee( ) );
        if( !pe )
        {
            return;
        }
        //updating
        *pe = employee;
    }

    /// -----------------------------------------------------------------------
    ///	delete_employee(const data_employee &employee)
    /// -----------------------------------------------------------------------
    void data_model_employee::delete_employee( int id_employee )
    {
        data_employee *pe = this->find_employee( id_employee );
        if( !pe )
        {
            return;
        }
        //deleting
        int n_row = this->find_employee_row( id_employee );
        if( n_row < 0 )
        {
            return;
        }
        this->removeRows( n_row, 1 );
    }

    /// -----------------------------------------------------------------------
    ///	find_employee( const int id_employee )
    /// -----------------------------------------------------------------------
    data_employee* data_model_employee::find_employee( const int id_employee )
    {
        if( !this->_hash.contains( id_employee ) )
        {
            return 0;
        }
        return this->_hash[id_employee];
    }

    /// -----------------------------------------------------------------------
    ///	find_employee_row( const int id_employee )
    /// -----------------------------------------------------------------------
    int data_model_employee::find_employee_row( const int id_employee )
    {
        data_employee *pe = this->find_employee( id_employee );
        if( !pe )
        {
            return -1;
        }
        return this->_list.indexOf( pe );
    }

    /// -----------------------------------------------------------------------
	/// virtual
	///	data( )
    /// -----------------------------------------------------------------------
	QVariant data_model_employee::data(
										const QModelIndex &index,
										int /*role //= Qt::DisplayRole*/
									   ) const
	{
		if( !index.isValid( ) )
		{
			return QVariant( );
		}
		data_employee* employee = this->_list.at( index.row( ) );

		switch( index.column( ) )
		{
			case 0:
				return employee->employee( );
			default:
				return QVariant( );
		}
		return QVariant( );
	}

    /// -----------------------------------------------------------------------
	/// virtual
	///	setData( )
    /// -----------------------------------------------------------------------
	bool data_model_employee::setData(
										const QModelIndex &/*index*/,
										const QVariant &/*value*/,
										int /*role //= Qt::EditRole*/
									  )
	{
		return false;
	}

    /// -----------------------------------------------------------------------
	/// virtual
	///	flags( )
    /// -----------------------------------------------------------------------
	Qt::ItemFlags data_model_employee::flags(const QModelIndex &/*index*/) const
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

    /// -----------------------------------------------------------------------
	/// virtual
	///	insertRows( )
    /// -----------------------------------------------------------------------
	bool data_model_employee::insertRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
		if( ( row < 0 ) || ( row > this->_list.size( ) ) )
		{
			return false;
		}

		this->beginInsertRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; i++ )
		{
			data_employee* employee = new data_employee;
			this->_list.insert( row + i, employee );
			this->_hash.insert( employee->id_employee( ), employee );
		}

		this->endInsertRows( );

		return true;
	}

    /// -----------------------------------------------------------------------
	/// virtual
	///	removeRows( )
    /// -----------------------------------------------------------------------
	bool data_model_employee::removeRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
		this->beginRemoveRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; ++i )
		{
			data_employee *item = this->_list.takeAt( row );
			this->_hash.remove( item->id_employee( ) );
			delete item;
		}

		this->endRemoveRows( );

		return true;
	}

}//    namespace employee_vacation

}//    namespace rele_auto
