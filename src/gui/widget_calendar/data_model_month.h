/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-01-2013
///		Date update	: 05-12-2014
///		Comment		:
/// ============================================================================

#ifndef __DATA_MODEL_MONTH_H__
#define __DATA_MODEL_MONTH_H__

#include <QAbstractTableModel>

#include "calendar_data.h"

namespace rele_auto
{

namespace employee_vacation
{

/// ############################################################################
///			class data_model_month
/// ############################################################################
    class data_model_month : public QAbstractTableModel
	{
	Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    public:
    /// ------------------------------------------------------------------------
        data_model_month( QObject* pobj = 0 );
    /// ------------------------------------------------------------------------
        data_model_month( int year, int month, QObject *pobj = 0 );
    /// ------------------------------------------------------------------------
        virtual ~data_model_month( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    /// year
        int year( ) const
        { return this->_year; }

        void year( const int yyyy )
        { this->_year = yyyy; }

    /// ------------------------------------------------------------------------
    /// month
        int month( ) const
        { return this->_year; }

        void month( const int MM )
        { this->_month = MM; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_model_month& operator=( const data_model_month &rhs );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		virtual void initialize( void );

	public:
    /// ------------------------------------------------------------------------
		void clear( );
    /// ------------------------------------------------------------------------
        void requery( );
    /// ------------------------------------------------------------------------
        const calendar_item* item( const QModelIndex &index ) const;
    /// ------------------------------------------------------------------------
    /// override
		virtual int rowCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							) const
		{
            return this->_data ? this->_data->calendar_rows( ) : 0;
        }
    /// ------------------------------------------------------------------------
    /// override
		virtual int columnCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							   ) const
		{
            return Qt::Sunday;
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
        void set_vacation_days( const QModelIndexList &list_indexes );
    /// ------------------------------------------------------------------------
        void unset_vacation_days( const QModelIndexList &list_indexes );
    /// ------------------------------------------------------------------------
        void set_vacation_days( const QDate &dt_begin, const QDate &dt_end );
    /// ------------------------------------------------------------------------
        void unset_vacation_days( const QDate &dt_begin, const QDate &dt_end );

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    private:
    /// ------------------------------------------------------------------------

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:

        int _year;
        int _month;
        calendar_data *_data;

    };//class data_model_month

/// ############################################################################

}//namespace employee_vacation

}//namespace rele_auto

#endif // __DATA_MODEL_MONTH_H__
