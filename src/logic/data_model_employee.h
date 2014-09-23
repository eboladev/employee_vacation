/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 15-10-2013
///		Comment		:
/// ============================================================================

#ifndef __DATA_MODEL_EMPLOYEE_H__
#define __DATA_MODEL_EMPLOYEE_H__

#include <QAbstractTableModel>
#include <QList>
#include <QHash>
#include <QVector>

namespace rele_auto
{

namespace employee_vacation
{
	class data_employee;
	class data_employee_collection;
	typedef QHash<int, data_employee*> data_employee_hash;
	typedef QList<data_employee*> data_employee_list;
/// ############################################################################
///			class data_model_employee
/// ############################################################################
	class data_model_employee : public QAbstractTableModel
	{

	Q_OBJECT
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		data_model_employee( QObject* pobj = 0 );
	/// ------------------------------------------------------------------------
		virtual ~data_model_employee( );

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		const data_employee* employee( int i_row ) const;

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		data_model_employee& operator=( const data_model_employee &rhs );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		virtual void initialize( void );
	/// ------------------------------------------------------------------------
		virtual void init_columns_header( void )
		{
			this -> _header.append( QObject::tr( "employee" ) );
		}
	/// ------------------------------------------------------------------------
        int find_employee_row(const int id_employee);

	public:
	/// ------------------------------------------------------------------------
		void clear( );
	/// ------------------------------------------------------------------------
		void refresh( const QVector<QVector<QVariant> > &data );
	/// ------------------------------------------------------------------------
		void refresh( data_employee_collection *data );
	/// ------------------------------------------------------------------------
        void list_into_hash( );
	/// ------------------------------------------------------------------------
        void insert_employee( const data_employee &employee );
	/// ------------------------------------------------------------------------
        void update_employee( const data_employee &employee );
	/// ------------------------------------------------------------------------
        void delete_employee(int id_employee );
	/// ------------------------------------------------------------------------
        data_employee* find_employee( const int id_employee );
	/// ------------------------------------------------------------------------
	/// override
		virtual int rowCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							) const
		{
			return this -> _list.size( );
		}
	/// ------------------------------------------------------------------------
	/// override
		virtual int columnCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							   ) const
		{
			return this -> _header.size( );
		}
	/// ------------------------------------------------------------------------
	/// override
		virtual QVariant headerData(
									int section,
									Qt::Orientation orientation,
									int role/* = Qt::DisplayRole*/
								   ) const
		{
			if( role != Qt::DisplayRole )
			{
				return QVariant( );
			}
			if(
				( section > this -> _header.size( ) ) ||
				( section < 0 )
			  )
			{
				return QVariant( );
			}

			return ( orientation == Qt::Horizontal )
					? ( this -> _header )[section]
					: " ";
		}
	/// ------------------------------------------------------------------------
	/// override
		virtual Qt::ItemFlags flags( const QModelIndex &index ) const;
	/// ------------------------------------------------------------------------
	/// override
		virtual QVariant data(
								const QModelIndex & index,
								int role = Qt::DisplayRole
							 ) const;
	/// ------------------------------------------------------------------------
	/// override
		virtual bool setData(
								const QModelIndex & index,
								const QVariant & value,
								int role = Qt::EditRole
							 );
	/// ------------------------------------------------------------------------
	/// override
		virtual bool insertRows(
								int row, int count,
								const QModelIndex &parent = QModelIndex( )
							   );
	/// ------------------------------------------------------------------------
	/// override
		virtual bool removeRows(
								int row, int count,
								const QModelIndex &parent = QModelIndex( )
							   );

	/// ========================================================================
	///		SLOTS
    /// ========================================================================
    private:
	/// ------------------------------------------------------------------------

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
		data_employee_list  _list;
		data_employee_hash  _hash;
		QVector<QString>	_header;

	};//class data_model_employee
//#############################################################################

}//namespace employee_vacation

}//namespace rele_auto


#endif // __DATA_MODEL_EMPLOYEE_H__
