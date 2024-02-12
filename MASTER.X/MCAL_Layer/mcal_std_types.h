/* 
 * File:   mcal_std_types.h
 * Author: Mohamed Elghzaly
 *
 * Created on September 3, 2023, 12:21 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes */
#include "std_libraries.h"
#include "compiler.h"
 


/* Section : Data Type Declaration */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef float float32;

typedef uint8 Std_ReturnType;

/* Section : Macro Declaration */
#define STD_HIGH        0X01
#define STD_LOW         0X00

#define STD_ON          0X01
#define STD_OFF         0X00

#define STD_ACTIVE      0X01
#define STD_IDLE        0X00

#define E_OK            (Std_ReturnType)0X01
#define E_NOT_OK        (Std_ReturnType)0X00

/* Section : Macro Functions Declaration */


/* Section : Function Declaration */

#endif	/* MCAL_STD_TYPES_H */

