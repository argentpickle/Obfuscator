/**************************************************************
**	general utility functions
**
**	Copyright 2013 Argent Pickle Software.  Non-commercial use
**	permitted with this copyright notice retained.
**	All other rights reserved.
**
**************************************************************/
#ifndef __UTILITY_H__
#define __UTILITY_H__

int init_coder( void );
void get_word( char word[] );

int get_code_for_byte( unsigned char * const p_data, char output[] );
int get_crc32( unsigned char * const p_data, long data_len, unsigned long * p_crc );

#endif
