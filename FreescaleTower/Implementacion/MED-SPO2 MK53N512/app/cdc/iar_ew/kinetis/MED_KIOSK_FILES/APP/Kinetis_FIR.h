/****************************************************************************
*                            FIR for Kinetis
*****************************************************************************
* @file: Kinetis_FIR.h
* 
* @author : Santiago Lopez [SL]  Freescale Americas
*
* @version: 1.0
*
* @date: 13/01/11
*
* @description: Program to implement Finite Impulse Response Filters on Kinetis
*******************************************************************************
* @changes:
*
*    Date       Author         Version               Description of Change
*
*  13/01/11       SL             1.0                    Initial Version
******************************************************************************/

#ifndef _KINETIS_FIR_H_
#define _KINETIS_FIR_H_

#define IAR_COMPILER

#if   (defined IAR_COMPILER)
  #include "derivative.h"
  #include "dsp.h"
#elif (defined CW_COMPLIER)
  #include "derivative.h"
  /*CW does not support MAC yet*/
#else
  #error "No valid compiler defined"
#endif

#include "DAC.h"
#include "ADC.h"
#include "Types.h"
#include "HeartRate.h"

/******************************************************************************
*                                 Definitions
*******************************************************************************/
#define INA_GAIN_100      //MED_EKG Jumpers J3 & J4  1-2

#define FILTER_ORDER      51
#define MAC               //Processing type  1.-CODE    2.-MAC
#ifdef INA_GAIN_100
  #define INPUT_DIVISOR     300
  #define INPUT_OFFSET      -18000   //Remove DC component
  #define OUTPUT_DIVISOR    7500
#else
  #define INPUT_DIVISOR     200
  #define INPUT_OFFSET      -25000//-25000   //Remove DC component
  #define OUTPUT_DIVISOR    3000//3000
#endif

#define FIR_DATA_TO_SEND    32

//#define BYPASS     //Uncoment this for Bypass mode it means no filter execution
//#define DAC0_TEST  //Uncoment this for DAC output Test

#define SPO2_FILTER_ORDER     100   //100
#define SPO2_INPUT_OFFSET     0     //300
#define SPO2_OUTPUT_DIV       8000 //5000

#define SPO2_BASELINE_FILTER_ORDER     51 //51
#define SPO2_BASELINE_INPUT_OFFSET     0 //0
#define SPO2_BASELINE_OUTPUT_DIV       62000 //60000

/******************************************************************************
*                                  Globals
*******************************************************************************/


/* Include your global data buffers here */
extern unsigned long gu16FIR_Data[FIR_DATA_TO_SEND];
extern unsigned char gu8FilterDataReady;

extern unsigned long gu16IR_Samples[SPO2_FILTER_ORDER];
extern unsigned long gu16IR_Base[SPO2_BASELINE_FILTER_ORDER];
extern unsigned long gu16R_Samples[SPO2_FILTER_ORDER];
extern unsigned long gu16R_Base[SPO2_BASELINE_FILTER_ORDER];

/*****************************************************************************
*                             Function Definitions
******************************************************************************/

/******************************************
* Function: Filter Periodic Task
* Description: Periodic task for the FIR filter
* Input:
*   -Void
* Output:
*   -Void
******************************************/

extern void vfnFilter_Periodic_Task (void);

/******************************************
* Function: Filter Execution
* Description: CPU processing of the signal
* Input:
*   *pi32ActualSample: Pointer to the actual sample on the circular buffer
*   *pi32BufferLimit: Pointer to the last element on the buffer
*   *pi32Coefptr: Pointer to the list of coeficients
* Output:
*   -i32 result of the filter for the actual sample
******************************************/

int i32Filter_Execution (int *pi32ActualSample, int *pi32BufferLimit, int *pi32Coefptr, unsigned char u8Filter_Order);

/******************************************
* Function: SPO2 Filter Execution
* Description: CPU processing of the signal
* Input:
*   u16NewSample: New Sample
* Output:
*    i32 result of the filter for the actual sample
******************************************/

extern int u32SPO2_Filter(unsigned long u16NewSample, int* LEDBuffer);

/******************************************
* Function: SPO2 Baseline Filter Execution
* Description: CPU processing of the signal
* Input:
*   u16NewSample: New Sample
* Output:
*    i32 result of the filter for the actual sample
******************************************/

extern int u32SPO2_BaselineFilter(unsigned long u16NewSample, int* LEDBuffer);

#endif