/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-02-2013
///		Date update	: 04-02-2013
///		Comment		:
/// ============================================================================
#include <QPainter>

#include "calendar_item_delegate.h"

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
        painter->save( );
        if( option.state & QStyle::State_Selected )
        {
            painter->fillRect( option.rect, option.palette.highlight( ) );
        }
        QTextOption text_opt;
        text_opt.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect, model->data( index ).toString( ), text_opt );
        painter->restore( );
    }

/// ############################################################################

}//namespace employee_vacation

}//namespace rele_auto

