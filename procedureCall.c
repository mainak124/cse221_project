#include<stdio.h>
#include<stdint.h>
#include "armpmu_lib.h"

uint32_t addZero() {
//        int result = rdtsc32();
//        return result;
	return rdtsc32();
}

uint32_t addOne(int one) {
//        int result = rdtsc32();
//	volatile int r1 = result + one;
//        return result;
	return rdtsc32();
}

uint32_t addTwo(int one, int two) {
//        int result = rdtsc32();
//	volatile int r1 = result + one + two;
//        return result;
	return rdtsc32();
}

uint32_t addThree(int one, int two, int three) {
//        int result = rdtsc32();
//	volatile int r1 = result + one + two + three;
//        return result;
	return rdtsc32();
}

uint32_t addFour(int one, int two, int three, int four) {
//        int result = rdtsc32();
//	volatile int r1 = result + one + two + three + four;
//        return result;
	return rdtsc32();
}

uint32_t addFive(int one, int two, int three, int four, int five) {
//        int result = rdtsc32();
//	volatile int r1 = result + one + two + three + four + five;
//        return result;
	return rdtsc32();
}

uint32_t addSix(int one, int two, int three, int four, int five, int six) {
//        int result = rdtsc32();
//	volatile int r1 = result + one + two + three + four + five + six;
//        return result;
	return rdtsc32();
}

uint32_t addSeven(int one, int two, int three, int four, int five, int six, int seven) {
//        int result = rdtsc32();
//	volatile int r1 = result + one + two + three + four + five + six + seven;
//        return result;
	return rdtsc32();
}


int main () {
	uint32_t time, result;
	uint32_t timeArr[8];
	int i,j;

	for(i = 0; i < 8; i++) {
		timeArr[i] = 0;
	}
//for(j=0; j<1000; j++){
	time = rdtsc32();
	result = addZero();
	timeArr[0] = (result-time);
	time = rdtsc32();      
	result = addOne(3);
	timeArr[1] = (result - time);
	time = rdtsc32();    
	result = addTwo(3,4);
	timeArr[2] = (result - time);  
	time = rdtsc32();      
	result = addThree(3,4,5);
	timeArr[3] = (result - time);  
	time = rdtsc32(); 
	result = addFour(3,4,5,6);
	timeArr[4] = (result - time);  
	time = rdtsc32();
	result = addFive(3,4,5,6,7);
	timeArr[5] = (result - time);
	time = rdtsc32(); 
	result = addSix(3,4,5,6,7,8);
	timeArr[6] = (result - time);
	time = rdtsc32(); 
	result = addSeven(3,4,5,6,7,8,9);
	timeArr[7] = (result - time);
//}
	for(i = 0; i < 8; i++) {
		printf("Count for %d arguements = %u\n", i, timeArr[i]);
	}
	return 0;
}
