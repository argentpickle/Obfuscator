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
