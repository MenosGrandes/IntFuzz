#include <gb/gb.h>
#include <stdint.h>
#include <gbdk/platform.h>
#include <stdint.h>
#include <stdio.h>      // Just for printf()
#include <gb/emu_debug.h> // Use this include to add the Emu debug functions


#define TEST_FOR_MACRO(T) \
{ \
    T t; \
    T *t_ptr; \
    EMU_printf(" [%s] ", #T); \
    EMU_printf(" sizeof(T) =  %d", sizeof(t)); \
    EMU_printf(" sizeof t_ptr = %d" ,sizeof(t_ptr)); \
    EMU_printf(" sizeof *t_ptr =  %d",sizeof(*t_ptr)); \
    EMU_printf(" sizeof &t_ptr =  %d",sizeof(&t_ptr)); \
}



void main(void)
{
    // Loop forever
   // while(1) {
   TEST_FOR_MACRO(uint8_t);
    TEST_FOR_MACRO(uint16_t);
    TEST_FOR_MACRO(uint32_t);
    TEST_FOR_MACRO(uint64_t);

    TEST_FOR_MACRO(int8_t);
    TEST_FOR_MACRO(int16_t);
    TEST_FOR_MACRO(int32_t);
    TEST_FOR_MACRO(int64_t);

    TEST_FOR_MACRO(signed char);
    TEST_FOR_MACRO(unsigned char);
    TEST_FOR_MACRO(short);
    TEST_FOR_MACRO(short int);
    TEST_FOR_MACRO(signed short);
    TEST_FOR_MACRO(signed short int);
    TEST_FOR_MACRO(unsigned short);
    TEST_FOR_MACRO(unsigned short int);
    TEST_FOR_MACRO(int);
    TEST_FOR_MACRO(signed);
    TEST_FOR_MACRO(signed int);
    TEST_FOR_MACRO(unsigned);
    TEST_FOR_MACRO(unsigned int);
    TEST_FOR_MACRO(long);
    TEST_FOR_MACRO(long int);
    TEST_FOR_MACRO(signed long);
    TEST_FOR_MACRO(signed long int);
    TEST_FOR_MACRO(unsigned long);
    TEST_FOR_MACRO(unsigned long int);
    TEST_FOR_MACRO(long long);
    TEST_FOR_MACRO(long long int);
    TEST_FOR_MACRO(signed long long);
    TEST_FOR_MACRO(signed long long int);
    TEST_FOR_MACRO(unsigned long long);
    TEST_FOR_MACRO(unsigned long long int);

		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
       // vsync();
   // }
}
