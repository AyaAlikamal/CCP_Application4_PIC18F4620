/* 
 * File:   mcal_std_type.h
 * Author: AyaAli
 *
 * Created on September 22, 2023, 10:45 AM
 */

#ifndef MCAL_STD_TYPE_H
#define	MCAL_STD_TYPE_H

/*Section : Includes*/
#include "std_libraries.h"
#include "compiler.h"


/*Section : Data type Declaration*/
typedef unsigned char        uint_8;
typedef unsigned short       uint_16;
typedef unsigned long         uint_32;

typedef signed char        sint_8;
typedef signed short       sint_16;
typedef signed long         sint_32;
typedef uint_8 Std_ReturnType;

/*Section : Macro Declaration*/
#define STD_HIGH          0x01
#define STD_LOW           0x00
#define STD_ON            0x01
#define STD_OFF           0x00
#define STD_ACTIVE        0x01
#define STD_IDLE          0x00
#define E_OK              (Std_ReturnType)0x01
#define E_NOT_OK          (Std_ReturnType)0x00
#define ZERO_INIT         0


/*Section : Macro Function Declaration*/

/*Section : Function Declaration*/



#endif	/* MCAL_STD_TYPE_H */

