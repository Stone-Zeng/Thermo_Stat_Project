//Here are some switches and adjusted parameters for the program.
//Need C++ 11.

#ifndef _HEAD_H_
#define _HEAD_H_
#pragma once

/****Parameters:****/
#define $LATTICE_LENGTH		15
#define $VECTOR_PLOT_NUMBER	100
#define $AVERAGE_NUMBER		50

#define $PARALLEL_CORES     //schedule(dynamic, 65536) num_threads(2) 

/****Switches:****/
#define NORMAL_RUN
#ifndef NORMAL_RUN
//#define VECTOR_TEST_ON
//#define AMP_TEST_ON
//#define PHASE_DIAGRAM_ON
#endif

#define INPUT_PARAMETERS_ON
#define HEISENBERG_ON
#define FLIP_DATA_OUTPUT_ON
//#define VECTOR_PLOT_OUTPUT_ON
//#define CPP11_RANDOM

#ifdef _MSC_VER
#define WIN_TIMING
#endif
#ifdef __GNUC__
#define GNU_TIMING
#endif

#endif