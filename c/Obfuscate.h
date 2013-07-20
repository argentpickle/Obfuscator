//	Obfuscate.h
//	Copyright 2013 Argent Pickle Software.  Non-commercial use
//	permitted with this copyright notice attached.  All other rights reserved.
//
#ifndef __OBFUSCATE_H__
#define __OBFUSCATE_H__

typedef enum _e_operational_mode
{
	E_OPMODE_NONE,
	E_OPMODE_DECODE,
	E_OPMODE_ENCODE,
	E_OPMODE_MAX
} e_opmode;

int usage( void );
int _tmain( int argc, _TCHAR* argv[] );


#endif
