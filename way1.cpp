#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <stdio.h>

std::string in_file_name="test_case.txt";
std::string out_file_name="output.txt";
std::string out_file_time_name="_time.txt";

void func();

int main(void){
    for(int i=0;i<100;i++) func();
    return 0;
}
void func(){
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
    int first[101], second[101], third[101];
    int *first_row = first, *second_row = second, *third_row = third;
    int sum=0;
    int x[10000], y[10000];
    int row, col;
    in_file>>row>>col;

    for(int i=1;i<=col;i++){
        in_file>>first_row[i];
    }
    for(int i=1;i<=col;i++){
        int comp;
        in_file>>comp;
        if((first_row[i]>=comp)&&(i>=col||first_row[i]>=first_row[i+1])&&(i<=1||first_row[i]>=first_row[i-1])){
            x[sum]=1;//adjust
            y[sum]=i;
            sum++;
        }
        second_row[i]=comp;
    }
    for(int i=2;i<row;i++){
        for(int j=1;j<=col;j++){
            int comp;
            in_file>>comp;
            if((second_row[j]>=comp)&&(second_row[j]>=first_row[j])&&(j>=col||second_row[j]>=second_row[j+1])&&(j<=1||second_row[j]>=second_row[j-1])){
                x[sum]=i;
                y[sum]=j;
                sum++;
            }
            third_row[j]=comp;
        }
        //swap
        first_row=second_row;
        second_row=third_row;
        third_row=first_row;
    }
    for(int i=1;i<=col;i++){
        if((second_row[i]>=first_row[i])&&(i>=col||second_row[i]>=second_row[i+1])&&(i<=1||second_row[i]>=second_row[i-1])){
            x[sum]=col;
            y[sum]=i;
            sum++;
        }
    }

    ///output.
    out_file<<sum<<std::endl;
    for(int i=0;i<sum;i++){
        out_file<<x[i]<<" "<<y[i]<<std::endl;
    }
    QueryPerformanceCounter(&t2);
    std::cout<<"Execution Time : "<<(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart)<<" s."<<std::endl;
    out_file_time<<(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart)<<"\n";
}
