/**************************************************************
**	handles encoding
**
**	Copyright 2013 Argent Pickle Software.  Non-commercial use
**	permitted with this copyright notice retained.
**	All other rights reserved.
**
**************************************************************/
#ifndef __ENCODE_H__
#define __ENCODE_H__

int init_coder( void );
void get_word( char word[] );

int get_code_for_byte( unsigned char * const p_data, _TCHAR ** p_output );
int encode( _TCHAR * pFilename );

#endif
