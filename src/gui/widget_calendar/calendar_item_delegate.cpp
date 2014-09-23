/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-02-2013
///		Date update	: 25-03-2013
///		Comment		:
/// ============================================================================
#include <QPainter>

#include "calendar_item_delegate.h"
#include "data_model_month.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class calendar_item_delegate
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	calendar_item_delegate( )
    /// ------------------------------------------------------------------------
    calendar_item_delegate::calendar_item_delegate( QObject *parent/* = 0*/  ) :
        QStyledItemDelegate( parent )
	{
	}

    /// ------------------------------------------------------------------------
    ///	~calendar_item_delegate( )
    /// ------------------------------------------------------------------------
    calendar_item_delegate::~calendar_item_delegate( )
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
    void calendar_item_delegate::paint(
                                        QPainter *painter,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index
                                      ) const
    {
        const QAbstractItemModel *model = index.model( );
        if( model == 0 )
        {
            return;
        }

        const data_model_month *md = static_cast<const data_model_month*>( model );

        const calendar_item *ci = md->item( index );
        if( !ci )
        {
            return;
        }

        calendar_item_painter *ci_painter = ci->painter( );
        if( !ci_painter )
        {
            return;
        }
        ci_painter->paint( painter, option, ci->text( ) );
    }

/// ############################################################################

}//namespace employee_vacation

}//namespace rele_auto

