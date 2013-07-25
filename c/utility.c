/**************************************************************
**	general utility functions
**
**	Copyright 2013 Argent Pickle Software.  Non-commercial use
**	permitted with this copyright notice retained.
**	All other rights reserved.
**
**************************************************************/

#include "stdafx.h"
#include "utility.h"

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

	/*	make sure at least one word in the word list has at least four letters	*/
	for ( i = 0; i < word_count; i++ )
	{
		if ( 4 <= _tcslen( word_list[i] ) )
		{
			break;
		}
	}
	if ( i >= word_count ) { return 1; }

	/*	make sure the random number generator is working	*/
	if ( 0 != rand_s( &randval ) ) { return 1; }

	return 0;
}

static void _get_word( _TCHAR ** p_word )
{
	int index, len;

	/*	assign an index value into wordlist.  this operation must succeed. */
	index = ( 0 == rand_s( &randval ) ) ? (int)((double)randval * (double)word_count / (double)UINT_MAX) : 0 ;
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
/*
	if ( nibble & 0x08 )
	{
		(*p_out)[0] = _totupper( (*p_out)[0] );
	}
	if ( nibble & 0x04 )
	{
		(*p_out)[1] = _totupper( (*p_out)[1] );
	}
	if ( nibble & 0x02 )
	{
		(*p_out)[2] = _totupper( (*p_out)[2] );
	}
	if ( nibble & 0x01 )
	{
		(*p_out)[3] = _totupper( (*p_out)[3] );
	}
*/

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

int get_crc32( unsigned char * const p_data, long data_len, unsigned long * p_crc )
{
	int retval = 0;

	/*	sanity check the parameters */
	if ( NULL == p_data || NULL == p_crc ) { goto error; }

	/*	dummy return value pending actual implementation	*/
	*p_crc = 0xDEADBEEF;

	/*	TODO: actual CRC implementation	*/

	/*	return success	*/
	return 0;

error:
	/*	unwind local state and exit with error code	*/
	return ( retval != 0 ? retval : 1 );
}
