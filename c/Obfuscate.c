/***************************************************************************
**	Obfuscate.c : Defines the entry point for the console application.
**
**	Copyright 2013 Argent Pickle Software.  Non-commercial use permitted
**	with this copyright notice included.  All other rights reserved.
**
**	transforms arbitrary binary data into case variation in the letters
**	of words drawn from a built-in word list.  
**
*****************************************************************************/

#include "stdafx.h"
#include "Obfuscate.h"
#include "decode.h"
#include "encode.h"

int usage( void )
{
	_ftprintf_s( stdout, _T( "%s" ), _T( "usage:     [-d|-e|-h] [filename]\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( " -d        reads and decodes contents of the specified file\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( " --decode  and directs output to the console.\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( "\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( " -e        reads and encodes contents of the specified file\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( " --encode  and directs output to the console.\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( "\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( " -h,--help displays this message.\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( "\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( " filename  specifies the file. Required for encoding or decoding.\n" ) );
	_ftprintf_s( stdout, _T( "%s" ), _T( "\n" ) );
	/*	a more complex function could return various non-zero codes	**
	**	indicating errors of various kinds							*/
	return 0;
}

int _tmain( int argc, _TCHAR* argv[] )
{
	int retval = 0;
	e_opmode opmode = E_OPMODE_NONE;
	_TCHAR * pFilename = NULL;

	/*	sanity checks	*/
	if ( 1 >= argc || NULL == argv || NULL == argv[1] )
	{
		_ftprintf_s( stdout, _T( "%s" ), _T( "error:  parameter not found!\n" ) );
		retval = usage();
		exit( retval > 1 ? retval : 1 );
	}

	/*	argument check, collect operating parameters	*/
	if ( 0 == _tcsicmp( _T( "--help" ), argv[1] ) ||
			0 == _tcsicmp( _T( "-h" ), argv[1] ) )
	{
		retval = usage();
		exit( retval );
	}
	if ( 0 == _tcsicmp( _T( "-d" ), argv[1] ) ||
			0 == _tcsicmp( _T( "--decode" ), argv[1] ) )
	{
		opmode = E_OPMODE_DECODE;
	}
	else if ( 0 == _tcsicmp( _T( "-e" ), argv[1] ) ||
				0 == _tcsicmp( _T( "--encode" ), argv[1] ) )
	{
		opmode = E_OPMODE_ENCODE;
	}
	else if ( 0 == _tcsncmp( _T( "-" ), argv[1], 1 ) )
	{
		_ftprintf_s( stdout, _T( "%s" ), _T( "error:  parameter not recognized!\n" ) );
		retval = usage();
		exit( retval > 1 ? retval : 1 );
	}

	/*	some operating modes require a filename;	**
	**	for such modes, retrieve it					*/
	if ( E_OPMODE_NONE != opmode )
	{
		if ( 2 >= argc || NULL == argv[2] )
		{
			_ftprintf_s( stdout, _T( "%s" ), _T( "error:  filename parameter not found!\n" ) );
			retval = usage();
			exit( retval > 1 ? retval : 1 );
		}
		pFilename = argv[2];
	}

	/*	a program with more complex parameter sets would	**
	**	further validate its retrieved parameters here;		**
	**	this program is content with existing processing	*/

	/*	do useful work	*/
	switch ( opmode )
	{
		case E_OPMODE_DECODE:
			retval = decode( pFilename );
			break;
		case E_OPMODE_ENCODE:
			retval = encode( pFilename );
			break;
		default:
			/*	this is redundant only until	**
			**	a new operating mode is added	**
			**	to the parameter parsing.		*/
			_ftprintf_s( stdout, _T( "%s" ), _T( "error:  unrecognized operating mode!\n" ) );
			retval = usage();
			exit( retval > 1 ? retval : 1 );
			break;
	}

	/*	done	*/
	exit( retval );
	return retval;
}

