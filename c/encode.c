/**************************************************************
**	handles encoding
**
**	Copyright 2013 Argent Pickle Software.  Non-commercial use
**	permitted with this copyright notice retained.
**	All other rights reserved.
**
**************************************************************/

#include "stdafx.h"
#include "header.h"
#include "utility.h"
#include "encode.h"

int encode( _TCHAR * pFilename )
{
	encoding_header * p_header = NULL;
	FILE * p_input = NULL;
	unsigned char * p_contents = NULL;
	int retval = 0;
	errno_t err;
	long filelen = 0;
	size_t count = 0;
	unsigned long crc = 0;
	_TCHAR * outstr = NULL;
	int i = 0;
	long l = 0;

	/*	get standard header */
	retval = get_header( &p_header );
	if ( 0 != retval ) { goto error; }

	/*	extract length and binary content of file	*/
	err = _tfopen_s( &p_input, pFilename, _T( "rbR" ) );
	if ( 0 != err ) { retval = err; goto error; }
	retval = fseek( p_input, 0, SEEK_END );
	if ( 0 != retval ) { goto error; }
	filelen = ftell( p_input );
	if ( filelen < 0 ) { goto error; }
	p_contents = (unsigned char *)malloc( filelen );
	if ( NULL == p_contents ) { goto error; }
	rewind( p_input );
	count = fread( p_contents, 1, filelen, p_input );
	if ( 0 == count || count != filelen ) { goto error; }
	fclose( p_input );
	p_input = NULL;

	/*	update length value in header	*/
	p_header->length = filelen;

	/*	compute CRC, update in header	*/
	retval = get_crc32( p_contents, filelen, &crc );
	if ( 0 != retval ) { goto error; }
	p_header->crc = crc;

	/*	initialize encoder	*/
	retval = init_coder();

	/*	encode header, dump to stdout	*/
	for ( i = 0; i < sizeof( encoding_header ); i++ )
	{
		get_code_for_byte( ((unsigned char *)p_header) + i, &outstr );
		_ftprintf_s( stdout, _T( "%s" ), outstr );
		free( outstr );
	}
	/*	free header buffer	*/
	free( p_header );
	p_header = NULL;

	/*	encode content buffer, dump to stdout	*/
	for ( l = 0; l < filelen; l++ )
	{
		get_code_for_byte( p_contents + l, &outstr );
		_ftprintf_s( stdout, _T( "%s" ), outstr );
		free( outstr );
	}
	/*	free contents buffer	*/
	free( p_contents );
	p_contents = NULL;

	/*	return success	*/
	return 0;

error:
	/*	unwind local state and exit with error code	*/
	if ( NULL != p_contents )	{ free( p_contents ); }
	if ( NULL != p_input )		{ fclose( p_input ); }
	if ( NULL != p_header )		{ free( p_header ); }
	return ( retval != 0 ? retval : 1 ); 
}
