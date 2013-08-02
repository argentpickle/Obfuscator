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

static const _TCHAR * word_list[] = { _T( "dogs" ), _T( "cats" ), _T( "ford" ), _T( "mars" ), 
										_T( "toys" ), _T( "joys" ), _T( "bird" ), _T( "clam" ) };

static const int word_count = ( sizeof word_list ) / ( sizeof word_list[0] );

static unsigned int randval;

int init_coder( void )
{
	int i;

	/*	make sure the word list exists	*/
	if ( NULL == word_list ) { return 1; }
	
	/*	make sure the word list has elements	*/
	if ( 0 == word_count ) { return 1; }

	/*	make sure every word in the word list has at least four letters	*/
	/*	this is a simple word salad implementation, and does not handle **
	 *	shorter words													*/
	for ( i = 0; i < word_count; i++ )
	{
		if ( 4 > _tcslen( word_list[i] ) )
		{
			return 1;
		}
	}

	/*	make sure the random number generator is working	*/
	if ( 0 != rand_s( &randval ) ) { return 1; }

	return 0;
}

static void _get_word( _TCHAR ** p_word )
{
	int index, len;

	/*	assign an index value into wordlist.  this operation must succeed. */
	index = ( 0 == rand_s( &randval ) ) ? (int)((double)randval * (double)word_count / (double)UINT_MAX) : 0 ;
	/*	allocate memory and copy word	*/
	len = _tcslen( word_list[index] ) + 1;
	len *= sizeof( _TCHAR );
	*p_word = (char *)malloc( len );
	_tcscpy_s( *p_word, len, word_list[index] );
}

static int _get_word_for_nibble( unsigned char nibble, _TCHAR ** p_out )
{
	/*	sanity check	*/
	if ( 0 != (0xF0 & nibble) ) { return 1; }

	/*	get random word from wordlist	*/
	_get_word( p_out );

	/*	capitalize letters in nibble according to bit values in the high nibble of *p_data */
	(*p_out)[0] = ( nibble & 0x08 ) ? _totupper( (*p_out)[0] ) : _totlower( (*p_out)[0] ) ;
	(*p_out)[1] = ( nibble & 0x04 ) ? _totupper( (*p_out)[1] ) : _totlower( (*p_out)[1] ) ;
	(*p_out)[2] = ( nibble & 0x02 ) ? _totupper( (*p_out)[2] ) : _totlower( (*p_out)[2] ) ;
	(*p_out)[3] = ( nibble & 0x01 ) ? _totupper( (*p_out)[3] ) : _totlower( (*p_out)[3] ) ;

	return 0;
}

int get_code_for_byte( unsigned char * const p_data, _TCHAR ** p_outstr )
{
	_TCHAR * nibble_code[2];
	unsigned char nibble_data;
	int ilen = 0, mag = 0, checklen = 0;

	/*	sanity check	*/
	if ( NULL == p_data || NULL == p_outstr ) { return 1; }

	/*	do high nibble	*/
	nibble_data = (*p_data & 0xF0) >> 4;
	_get_word_for_nibble( nibble_data, &nibble_code[0] );
	/*	do low nibble	*/
	nibble_data = *p_data & 0x0F;
	_get_word_for_nibble( nibble_data, &nibble_code[1] );

	/*	build return value	*/
	ilen = _tcslen( nibble_code[0] ) + _tcslen( nibble_code[1] ) + 3;	/*	spaces and trailing null	*/
	mag = ilen * sizeof( _TCHAR );										/*	expansion for character size	*/
	mag += 4;															/*	padding	*/
	*p_outstr = (_TCHAR *)malloc( mag + 2 );							/*	more padding	*/
	if ( NULL == *p_outstr ) { return 1; }
	checklen = _stprintf_s( *p_outstr, ilen, _T( "%s %s " ), nibble_code[0], nibble_code[1] );

	return 0;
}

int encode( _TCHAR * pFilename )
{
	encoding_header_01_01 * p_header = NULL;
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
	retval = get_header_01_01( &p_header );
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
	for ( i = 0; i < sizeof( encoding_header_01_01 ); i++ )
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
