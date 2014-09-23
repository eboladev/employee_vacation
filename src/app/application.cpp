/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 06-11-2013
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QIcon>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMap>
#include <QTextStream>
#include <QMessageBox>
#include <QTranslator>
#include <stdexcept>

#include "application.h"
#include "business_logic.h"

namespace rele_auto
{

namespace employee_vacation
{
		bool application::_is_logic_initialized = false;
/// ############################################################################
///			class application
/// ############################################################################
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
	///	application( int & argc, char ** argv )
    /// ------------------------------------------------------------------------
	application::application( int & argc, char ** argv ) :
		QApplication( argc, argv )
	{
		this->initialize( );
	}


    /// ------------------------------------------------------------------------
	///	~application( )
    /// ------------------------------------------------------------------------
	application::~application( )
	{
		this->closeAllWindows( );

         //close all threads
		if( application::_is_logic_initialized )
		{
			the_business_logic( ).exit( );
		}

		if( this->_logic_thread.isRunning( ) )
		{
            this->_logic_thread.exit( );
            this->_logic_thread.wait( );
		}

		qDebug( ) << "application object destroyed correctly";
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
	/// -----------------------------------------------------------------------
	///	the_business_logic( )
    /// -----------------------------------------------------------------------
    business_logic& application::the_business_logic( )
	{
		static business_logic logic;

        return logic;
    }

	/// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
	void application::initialize( )
	{
        this->thread( )->setObjectName( "APP Thread" );
        qDebug( ) << "application thread ID:" << this->thread( )->objectName( );
		try
		{
            this->setWindowIcon(
							*( new QIcon( ":/image/images/32x32/app_icon.png" ) )
							   );
            this->load_translation( );
            this->load_config( );
            this->init_db( );
            this->init_logic( );

            this->connect(
                         this, SIGNAL(aboutToQuit( )),
                         this, SLOT(save_config( ))
                         );
		}
		catch( std::exception &ex )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "app init error" ),
									QString::fromUtf8( ex.what( ) )
								  );
		}
		catch( ... )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "critical" ),
									QObject::tr(
												"unexpected error while "
												"program initializing"
												)
								  );
		}
	}

    /// ------------------------------------------------------------------------
	///	init_logic( )
    /// ------------------------------------------------------------------------
    void application::init_logic( )
    {
        if( !application::_is_logic_initialized )
		{
			application::_is_logic_initialized = true;

            //creating business logic and put it into separate process
            this->_logic_thread.title( "LOGIC" );
			the_business_logic( ).moveToThread( &( this->_logic_thread ) );
			this->_logic_thread.start( );

			//init logic dynamic memory allocated objects
			the_business_logic( ).init( );
		}
    }

    /// ------------------------------------------------------------------------
	///	load_translation( )
    /// ------------------------------------------------------------------------
    void application::load_translation( )
    {
        this->_translator.load(
                        "russian.lng",
                        QApplication::applicationDirPath( )
                       );
        //translation
        this->installTranslator( &( this->_translator ) );
    }

	/// ------------------------------------------------------------------------
	///	load_config( )
    /// ------------------------------------------------------------------------
	void application::load_config( )
	{
        this->_params.parse_cfg_file(
                    //QApplication::applicationDirPath( )+"/employee_vacation.cfg"
                    QDir::currentPath( ) + "/employee_vacation.cfg"
                    );
    }

    /// ------------------------------------------------------------------------
	///	find_db_file( )
    /// ------------------------------------------------------------------------
    void application::find_db_file( )
    {
        //если файл БД есть - выходим
        if( this->check_db_file( ) )
        {
            return;
        }
        //если нет - пытаемся выбрать
        QString s_file = QFileDialog::getOpenFileName(
                                           0,tr("select db file"),
                                           QApplication::applicationDirPath( ),
                                           QString("*.sqlite3")
                                                        );

        if( s_file.length( ) )
        {
            this->_params.parameter("db_path", s_file );
        }
        //проверяем есть ли он после выбора
        if( !this->check_db_file( ) )
        {
            //если его нет - сообщение
            QMessageBox::warning(
                                 0, tr("warning"),
                                 tr("Database file wasn\'t selected")
                                );
        }

    }
    /// ------------------------------------------------------------------------
	///	check_db_file( )
    /// ------------------------------------------------------------------------
    bool application::check_db_file( )
    {
        QString s_db_path = this->_params.parameter("db_path");
        if( s_db_path.length( ) )
        {
            QFile f_db(s_db_path);
            if( f_db.exists( ) )
            {
                return true;
            }
        }
        return false;
    }

    /// ------------------------------------------------------------------------
	///	init_db( )
    /// ------------------------------------------------------------------------
    void application::init_db( )
    {
        this->find_db_file( );
        application::the_business_logic( ).db_path( this->_params.parameter("db_path") );
    }

    /// ========================================================================
	///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	save_config( )
    /// ------------------------------------------------------------------------
    void application::save_config( )
    {
        try
        {
            this->_params.save_cfg_file( );
        }
        catch( std::exception &ex )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "app exiting error" ),
									QString::fromUtf8( ex.what( ) )
								  );
		}
		catch( ... )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "critical" ),
									QObject::tr(
												"unexpected error while "
												"program exiting"
												)
								  );
        }
    }

//#############################################################################

}//namespace employee_vacation

}//namespace rele_auto
