#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <stdio.h>

#define MAX_MATRIXSIZE 1000

std::string in_file_name="matrix.data";
std::string out_file_name="final.peak";
std::string out_file_time_name="_time.data";

void func();

int main(void){
    for(int i=0;i<20;i++) func();
    return 0;
}

//function defined here
int x[MAX_MATRIXSIZE*MAX_MATRIXSIZE], y[MAX_MATRIXSIZE*MAX_MATRIXSIZE];
int matrix[MAX_MATRIXSIZE][MAX_MATRIXSIZE];

void func(){
    ///time control
    std::ofstream out_file_time;
    out_file_time.open(out_file_time_name,std::ios::app);

    ///start clock.
    LARGE_INTEGER t1, t2, ts;
    QueryPerformanceFrequency(&ts);
    QueryPerformanceCounter(&t1);

    ///file settings.
    std::ifstream in_file;
    std::ofstream out_file;
    in_file.open(in_file_name,std::ios::in);
    out_file.open(out_file_name,std::ios::out);

    ///get inputs.
    int row, col;
    in_file>>row>>col;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            in_file>>matrix[i][j];
        }
    }

    ///operate.
    int sum=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if((matrix[i][j]>=matrix[i-1][j]||i<1)&&
            (matrix[i][j]>=matrix[i+1][j]||i>=row-1)&&
            (matrix[i][j]>=matrix[i][j-1]||j<1)&&
            (matrix[i][j]>=matrix[i][j+1]||j>=col-1)){
                x[sum]=i+1;
                y[sum]=j+1;
                sum++;
            }
        }
    }

    ///output.
    out_file<<sum<<std::endl;
    for(int i=0;i<sum;i++){
        out_file<<x[i]<<" "<<y[i]<<std::endl;
    }
    QueryPerformanceCounter(&t2);
    std::cout<<"Execution Time : "<<(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart)<<" s."<<std::endl;

    ///time control
    out_file_time<<(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart)<<"\n";
}
