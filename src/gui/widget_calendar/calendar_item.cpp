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
    bool calendar_item_header_month::_is_initialized = false;

    QVector<QString>& calendar_item_header_month::month_long_names( )
    {
        static QVector<QString> names;
        if( calendar_item_header_month::_is_initialized )
        {
            return names;
        }
        names.append( QObject::tr( "January" ) );
        names.append( QObject::tr( "February" ) );
        names.append( QObject::tr( "March" ) );
        names.append( QObject::tr( "April" ) );
        names.append( QObject::tr( "May" ) );
        names.append( QObject::tr( "June" ) );
        names.append( QObject::tr( "July" ) );
        names.append( QObject::tr( "August" ) );
        names.append( QObject::tr( "September" ) );
        names.append( QObject::tr( "October" ) );
        names.append( QObject::tr( "November" ) );
        names.append( QObject::tr( "December" ) );

        calendar_item_header_month::_is_initialized = true;

        return names;
    }

    /// ------------------------------------------------------------------------
    /// const QString& text( ) const
    /// ------------------------------------------------------------------------
    const QString calendar_item_header_month::text( ) const
    {
        if( !this->date( ).isValid( ) )
        {
            return "";
        }

        return calendar_item_header_month::month_long_names( )[this->date( ).month( ) - 1];
    }

/// ############################################################################
///			class calendar_item_header_day
/// ############################################################################
    bool calendar_item_header_day::_is_initialized = false;

    QVector<QString>& calendar_item_header_day::day_short_names( )
    {
        static QVector<QString> names;
        if( calendar_item_header_day::_is_initialized )
        {
            return names;
        }
        names.append( QObject::tr("Mon") );
        names.append( QObject::tr("Tue") );
        names.append( QObject::tr("Wed") );
        names.append( QObject::tr("Thu") );
        names.append( QObject::tr("Fri") );
        names.append( QObject::tr("Sat") );
        names.append( QObject::tr("Sun") );

        calendar_item_header_month::_is_initialized = true;

        return names;
    }

    /// ------------------------------------------------------------------------
    /// const QString& text( ) const
    /// ------------------------------------------------------------------------
    const QString calendar_item_header_day::text( ) const
    {
        if( !this->date( ).isValid( ) )
        {
            return "";
        }

        return calendar_item_header_day::day_short_names( )[this->date( ).dayOfWeek( ) - 1];
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

