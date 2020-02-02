#include <stdio.h>
#include <math.h>
#include "solutions.h"

int running_total(int a){
    static int total = 0;
    return total += a;
};

void reverse_in_place(int arr[], int len){
    for (int i = 0; i < len-1-i; i++){
        int temp = arr[len-1-i]; 
        arr[len-1-i] = arr[i];
        arr[i] = temp;
    }
};


int * reverse(int arr[], int len){
    int * y = (int *) calloc(len,sizeof(int));
    for (int i = 0; i < len; i++){
        y[i] = arr[len-1-i];
    }
    return y;
};

int num_instances(int arr[], int len, int val){
    int instances = 0;
    for (int i = 0; i < len; i++){
        if (val == arr[i]){
            instances++;
        }
    }
    return instances;
};


Point * map(Point arr[], int len, Point (* func) (Point)){
    Point * y = (Point *) calloc(len,sizeof(Point));
    for (int i = 0; i < len; i++){
        y[i] = func(arr[i]);
    }
    return y;
};

