/**************************************************************
**	supplies standard v1.0 encoding header
**
**	Copyright 2013 Argent Pickle Software.  Non-commercial use
**	permitted with this copyright notice retained.
**	All other rights reserved.
**
**************************************************************/

#include "stdafx.h"
#include "header.h"

/*
**	standard encoding header documents leading bytes,
**	major and minor version numbers of the encoding itself,
**	and the length and crc of the encoded content.
**
**	the get function instantiates a header and initializes 
**	that header with values appropriate to this implementation.
*/

int get_header( encoding_header ** pp_header )
{
	encoding_header headstruct;

	/*	sanity check the parameter	*/
	if ( NULL == pp_header ) { return 1; }

	/*	standard initialization for this version of the implementation	*/
	/*	file format version 01.01: CRC contained in header	*/
	headstruct.leader[0] = 'L';
	headstruct.leader[1] = 'N';
	headstruct.major = 1;
	headstruct.minor = 1;
	headstruct.reserved[0] = '\0';
	headstruct.reserved[1] = '\0';
	headstruct.reserved[2] = '\0';
	headstruct.reserved[3] = '\0';
	headstruct.crc = 0;
	headstruct.length = 0;

	//	set return value 
	*pp_header = (encoding_header *)malloc( sizeof( encoding_header ) );
	if ( NULL == *pp_header ) { return 1; }

	memcpy( *pp_header, &headstruct, sizeof( encoding_header ) );
	return 0;
}