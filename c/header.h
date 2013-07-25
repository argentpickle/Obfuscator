/**************************************************************
**	supplies standard v1.0 encoding header
**
**	Copyright 2013 Argent Pickle Software.  Non-commercial use
**	permitted with this copyright notice retained.
**	All other rights reserved.
**
**************************************************************/
#ifndef __HEADER_H__
#define __HEADER_H__

/*	16-byte header	*/
/*
**	byte	use
**	0		the ASCII character L
**	1		the ASCII character N
**	2		the major version number of the encoding. For this format, set to one.
**	3		the minor version number of the encoding. For this format, set to one.
**	4		reserved; set to zero
**	5		reserved; set to zero
**	6		reserved; set to zero
**	7		reserved; set to zero
**	8		LSB of length of content following header
**	9		next byte of length of content following header
**	10		next byte of length of content following header
**	11		MSB of length of content following header
**	12		LSB of crc of content following header
**	13		next byte of crc of content following header
**	14		next byte of crc of content following header
**	15		MSB of crc of content following header
*/

typedef struct _s_encoding_header_01_01
{
	unsigned char leader[2];
	unsigned char major;
	unsigned char minor;
	unsigned char reserved[4];
	unsigned long length;
	unsigned long crc;
} encoding_header_01_01;

int get_header_01_01( encoding_header_01_01 ** pp_header );

#endif
