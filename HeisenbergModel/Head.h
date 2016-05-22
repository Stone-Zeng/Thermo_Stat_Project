//Here are some switches and adjusted parameters for
//the program.
//TODO: Do not add functions here.
//TODO: Do not add .h files here.

#ifndef _HEAD_H_
#define _HEAD_H_
#pragma once

#define $LATTICE_LENGTH 36
//TODO: would be delete
#define $DATA_NUMBER 100
//TODO: would be delete
#define $LAST_10_PERCENT 1000 // 1/1000
#define $AVERAGE_NUMBER 50

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