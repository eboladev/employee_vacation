/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 11-04-2013
///		Date update	: 11-04-2013
///		Comment		:
/// ============================================================================

#include "calendar_item.h"

namespace rele_auto
{

namespace employee_vacation
{
/// ############################################################################
///			class calendar_item_header_month
/// ############################################################################
    QString calendar_item_header_month::_month_long_names[]
    {
        QObject::tr( "January" ),
        QObject::tr( "February" ),
        QObject::tr( "March" ),
        QObject::tr( "April" ),
        QObject::tr( "May" ),
        QObject::tr( "June" ),
        QObject::tr( "July" ),
        QObject::tr( "August" ),
        QObject::tr( "September" ),
        QObject::tr( "October" ),
        QObject::tr( "November" ),
        QObject::tr( "December" )
    };
    /// ------------------------------------------------------------------------
    /// const QString& text( ) const
    /// ------------------------------------------------------------------------
    const QString calendar_item_header_month::text( ) const
    {
        if( !this->date( ).isValid( ) )
        {
            return "";
        }

        return calendar_item_header_month::_month_long_names[this->date( ).month( ) - 1];
    }

/// ############################################################################
///			class calendar_item_header_day
/// ############################################################################
    QString calendar_item_header_day::_day_short_names[]
    {
        QObject::tr("Mon"),
        QObject::tr("Tue"),
        QObject::tr("Wed"),
        QObject::tr("Thu"),
        QObject::tr("Fri"),
        QObject::tr("Sat"),
        QObject::tr("Sun")
    };

    /// ------------------------------------------------------------------------
    /// const QString& text( ) const
    /// ------------------------------------------------------------------------
    const QString calendar_item_header_day::text( ) const
    {
        if( !this->date( ).isValid( ) )
        {
            return "";
        }

        return calendar_item_header_day::_day_short_names[this->date( ).dayOfWeek( ) - 1];
    }

/// ############################################################################
///			class calendar_item_creator
/// ############################################################################
    /// ------------------------------------------------------------------------
    /// calendar_item_creator::create( const QDate &dt )
    /// ------------------------------------------------------------------------
    calendar_item* calendar_item_creator::create( const QDate &dt )
    {
        if( !dt.isValid( ) )
        {
            return new calendar_item_nothing;
        }
        if( dt.dayOfWeek( ) >= Qt::Saturday )
        {
            return new calendar_item_holiday( dt );
        }
        return new calendar_item_day( dt );
    }

/// ############################################################################

}//namespace employee_vacation

}//namespace rele_auto

