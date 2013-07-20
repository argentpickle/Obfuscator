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

#define WORD_LENGTH		4

static const char * word_list[] = { "nuke", "bomb", "kill", "maim", 
									"hurt", "plan", "plot" };
static unsigned int randval;

int init_coder( void )
{
	if ( NULL == word_list ) { return 1; }

	/*	make sure the random number generator is working	*/
	if ( 0 != rand_s( &randval ) ) { return 1; }

	return 0;
}

void _get_word( char word[] )
{
	int index;

	/*	assign an index value into wordlist.  this operation must succeed. */
	index = ( 0 == rand_s( &randval ) ) ? (int)((double)randval * 7.0 / (double)UINT_MAX) : 0 ;
	strcpy_s( word, WORD_LENGTH, word_list[index] );
}

int _get_word_for_nibble( unsigned char nibble, char out[] )
{
	/*	sanity check	*/
	if ( 0 != (0xF0 & nibble) ) { return 1; }

	/*	get random word from wordlist	*/
	_get_word( out );

	/*	set case of letters in nibble according to bit values in the high nibble of *p_data */
	/*	where data bits are 1, clear the corresponding 0x20 bit in the character to cast the character to upper-case	*/
	if ( nibble & 0x08 )
	{
		out[0] &= 0xe0;
	}
	if ( nibble & 0x04 )
	{
		out[1] &= 0xe0;
	}
	if ( nibble & 0x02 )
	{
		out[2] &= 0xe0;
	}
	if ( nibble & 0x01 )
	{
		out[3] &= 0xe0;
	}

	return 0;
}

int get_code_for_byte( unsigned char * const p_data, char output[] )
{
	char nibble_code[2][WORD_LENGTH];
	unsigned char nibble_data;

	/*	sanity check	*/
	if ( NULL == p_data || NULL == output ) { return 1; }

	/*	do high nibble	*/
	nibble_data = (*p_data & 0xF0) >> 4;
	_get_word_for_nibble( nibble_data, nibble_code[0] );
	/*	do low nibble	*/
	nibble_data = *p_data & 0x0F;
	_get_word_for_nibble( nibble_data, nibble_code[1] );

	/*	build return value	*/
	memcpy( &(output[0]), nibble_code[0], WORD_LENGTH );
	output[4] = ' ';
	memcpy( &(output[5]), nibble_code[1], WORD_LENGTH );
	output[9] = ' ';

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
