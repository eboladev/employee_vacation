/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 25-03-2013
///		Date update	: 25-03-2013
///		Comment		:
/// ============================================================================
#include <QPainter>
#include <QBrush>
#include <QPen>

#include "calendar_item_painter.h"
#include "calendar_item.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class calendar_item_painter_nothing
/// ############################################################################
/// global
/// ----------------------------------------------------------------------------
/// the_painter_nothing( )
/// ----------------------------------------------------------------------------
calendar_item_painter_nothing * the_painter_nothing( )
{
    static calendar_item_painter_nothing painter;
    return &painter;
}

/// ========================================================================
///		FUNCTIONS
/// ========================================================================
void calendar_item_painter_nothing::paint(
                                    QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QString &//text
                                  ) const
{
    painter->save( );

    painter->fillRect( option.rect, option.palette.window( ) );

    painter->restore( );
}

/// ############################################################################
///			class calendar_item_painter_day
/// ############################################################################
/// global
/// ----------------------------------------------------------------------------
/// the_painter_day( )
/// ----------------------------------------------------------------------------
calendar_item_painter_day * the_painter_day( )
{
    static calendar_item_painter_day painter;
    return &painter;
}

/// ========================================================================
///		FUNCTIONS
/// ========================================================================
void calendar_item_painter_day::paint(
                                    QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QString &text
                                  ) const
{
    painter->save( );

    if( option.state & QStyle::State_Selected )
    {
        painter->fillRect( option.rect, option.palette.highlight( ) );
    }
    QTextOption text_opt;
    text_opt.setAlignment(Qt::AlignCenter);
    painter->drawText(option.rect, text, text_opt );

    painter->restore( );
}

/// ############################################################################
///			class calendar_item_painter_holiday
/// ############################################################################
/// global
/// ----------------------------------------------------------------------------
/// the_painter_holiday( )
/// ----------------------------------------------------------------------------
calendar_item_painter_holiday * the_painter_holiday( )
{
    static calendar_item_painter_holiday painter;
    return &painter;
}

/// ========================================================================
///		FUNCTIONS
/// ========================================================================
void calendar_item_painter_holiday::paint(
                                    QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QString &text
                                  ) const
{
    painter->save( );

    if( option.state & QStyle::State_Selected )
    {
        painter->fillRect( option.rect, option.palette.highlight( ) );
    }
    else
    {
        //light pink
        QRgb rgb_brush = 0xFFE1F0;
        QBrush brush( QColor::fromRgb( rgb_brush ) );
        painter->fillRect( option.rect, brush );
    }
    QTextOption text_opt;
    text_opt.setAlignment(Qt::AlignCenter);

    //bordo
    QRgb rgb_pen = 0x800040;
    painter->setPen( QColor::fromRgb( rgb_pen ) );
    painter->drawText( option.rect, text, text_opt );

    painter->restore( );
}

/// ############################################################################
///			class calendar_item_painter_vacation
/// ############################################################################
/// global
/// ----------------------------------------------------------------------------
/// the_painter_vacation( )
/// ----------------------------------------------------------------------------
calendar_item_painter_vacation * the_painter_vacation( )
{
    static calendar_item_painter_vacation painter;
    return &painter;
}

/// ========================================================================
///		FUNCTIONS
/// ========================================================================
void calendar_item_painter_vacation::paint(
                                    QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QString &text
                                  ) const
{
    painter->save( );

    if( option.state & QStyle::State_Selected )
    {
        painter->fillRect( option.rect, option.palette.highlight( ) );
    }
    else
    {
        //light green
        QRgb rgb_brush = 0xD4FFE4;
        QBrush brush( QColor::fromRgb( rgb_brush ) );
        painter->fillRect( option.rect, brush );
    }
    QTextOption text_opt;
    text_opt.setAlignment(Qt::AlignCenter);

    //dark green
    QRgb rgb_pen = 0x004010;
    painter->setPen( QColor::fromRgb( rgb_pen ) );
    painter->drawText( option.rect, text, text_opt );

    painter->restore( );
}

/// ############################################################################
///			class calendar_item_painter_header_month
/// ############################################################################
/// global
/// ----------------------------------------------------------------------------
/// the_painter_vacation( )
/// ----------------------------------------------------------------------------
calendar_item_painter_header_month * the_painter_header_month( )
{
    static calendar_item_painter_header_month painter;
    return &painter;
}

/// ========================================================================
///		FUNCTIONS
/// ========================================================================
void calendar_item_painter_header_month::paint(
                                    QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QString &text
                                  ) const
{
    painter->save( );

    //navy
    QRgb rgb_brush = 0x000050;
    QBrush brush( QColor::fromRgb( rgb_brush ) );
    painter->fillRect( option.rect, brush );
    QTextOption text_opt;
    text_opt.setAlignment(Qt::AlignCenter);

    //light blue
    QRgb rgb_pen = 0xD4E4FF;
    painter->setPen( QColor::fromRgb( rgb_pen ) );
    QFont fnt = painter->font( );
    fnt.setBold( true );
    painter->setFont( fnt );
    painter->drawText( option.rect, text, text_opt );

    painter->restore( );
}

/// ############################################################################
///			class calendar_item_painter_header_day
/// ############################################################################
/// global
/// ----------------------------------------------------------------------------
/// the_painter_vacation( )
/// ----------------------------------------------------------------------------
calendar_item_painter_header_day * the_painter_header_day( )
{
    static calendar_item_painter_header_day painter;
    return &painter;
}

/// ========================================================================
///		FUNCTIONS
/// ========================================================================
void calendar_item_painter_header_day::paint(
                                    QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QString &text
                                  ) const
{
    painter->save( );

    //blue
    QRgb rgb_brush = 0x0080FF;
    QBrush brush( QColor::fromRgb( rgb_brush ) );
    painter->fillRect( option.rect, brush );
    QTextOption text_opt;
    text_opt.setAlignment(Qt::AlignCenter);

    //white
    QRgb rgb_pen = 0xFFFFFF;
    painter->setPen( QColor::fromRgb( rgb_pen ) );
    QFont fnt = painter->font( );
    fnt.setBold( true );
    painter->setFont( fnt );
    painter->drawText( option.rect, text, text_opt );

    painter->restore( );
}

}//namespace employee_vacation

}//namespace rele_auto

