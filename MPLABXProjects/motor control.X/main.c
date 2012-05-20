/* 
 * File:   main.c
 * Author: Vinay
 *
 * Created on April 22, 2012, 10:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33ep64mc202.h"
#include <libpic30.h>
#include <math.h>
_FOSCSEL(PWMLOCK_OFF);
/*
 * 
 */
int main(int argc, char** argv) {

// all the initial values
// have to be changed according to the final model
    float R_motor = 2.5;
    int L_shaft = 6;
    int C_spring = 50; //has to be determined according to the spring used
    int L_wishbone = 8;
    int F_zero = 100;//has to be changed

    float base_Ceff = 23.6285; //calculated from matlab

    //get inputs from accelerometer and encoder
    //take movement of spring from the encoder
    //take x and z inputs from accelerometer


    //according to how much the spring has been compressed
    //that will be the z
    //look for that specific z and the x input in the matrix and look for the one with the closest Ceff



    return (EXIT_SUCCESS);
}

