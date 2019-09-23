#include <vector>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "K-NN.h"
#include "Relief.h"

using namespace std ;

int main(int argc, char** argv){
	srand(75573052) ;
	int bd = 3 ;

	//for(int i = 1 ; i < 5 ; i++)
		EjecutarRelief(1,bd) ;
}