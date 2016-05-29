//Here are some switches and adjusted parameters for the program.
//Need C++ 11.

#ifndef _HEAD_H_
#define _HEAD_H_
#pragma once

//Parameters:
#define $LATTICE_LENGTH		36
#define $VECTOR_PLOT_NUMBER	10
#define $AVERAGE_NUMBER		50

//Switches:
#define NORMAL_RUN
#ifndef NORMAL_RUN
#define VECTOR_TEST_ON
//#define AMP_TEST_ON
#endif

#define INPUT_PARAMETERS_ON
#define FLIP_DATA_OUTPUT_ON
//#define VECTOR_PLOT_OUTPUT_ON

//#define CPP11_RANDOM

#endif