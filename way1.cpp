#include <iostream>
#include <fstream>
#include <stdio.h>
#define MAX_MATRIXSIZE 1000

int coordinate[MAX_MATRIXSIZE*MAX_MATRIXSIZE+1];

int main(int argc, char *argv[]){
    ///file settings.
    std::ifstream in_file;
    std::ofstream out_file;

    char buffer[30];
    sprintf(buffer, "./%s/matrix.data", argv[1]);
    in_file.open(buffer,std::ios::in);
    sprintf(buffer, "./%s/final.peak", argv[1]);
    out_file.open(buffer,std::ios::out);
    //if(!in_file||!out_file){std:: cout<<"FAIL"; return 1;}

    ///get inputs.
    int first[MAX_MATRIXSIZE+1], second[MAX_MATRIXSIZE+1], third[MAX_MATRIXSIZE+1];
    int *first_row = first, *second_row = second, *third_row = third;
    int sum=0;
    int stop_pt[MAX_MATRIXSIZE+1];
    int row, col;
    in_file>>row>>col;

    //row == 1
    if(row == 1){
        for(int i=1;i<=col;i++){
            in_file>>first_row[i];
        }
        for(int i=1;i<=col;i++){//examine row 1
            if((i>=col||first_row[i]>=first_row[i+1])&&(i<=1||first_row[i]>=first_row[i-1])){
                coordinate[sum]=i+1;
                sum++;
            }
        }
        //stop_pt[1]=sum;
    }
    
    //row == 2
    else if(row == 2){
        for(int i=1;i<=col;i++){
            in_file>>first_row[i];
        }
        for(int i=1;i<=col;i++){//examine row 1
            int comp;
            in_file>>comp;
            if((first_row[i]>=comp)&&(i>=col||first_row[i]>=first_row[i+1])&&(i<=1||first_row[i]>=first_row[i-1])){
                coordinate[sum]=1+i;//adjust
                sum++;
            }
            second_row[i]=comp;
        }
        stop_pt[1]=sum;
        for(int i=1;i<=col;i++){
            if((second_row[i]>=first_row[i])&&(i>=col||second_row[i]>=second_row[i+1])&&(i<=1||second_row[i]>=second_row[i-1])){
                coordinate[sum]=2+i;//adjust
                sum++;
            }
        }
    }
    
    //row >= 3
    else if(row >= 3){
        for(int i=1;i<=col;i++){
            in_file>>first_row[i];
        }
        for(int i=1;i<=col;i++){//examine row 1
            int comp;
            in_file>>comp;
            if((first_row[i]>=comp)&&(i>=col||first_row[i]>=first_row[i+1])&&(i<=1||first_row[i]>=first_row[i-1])){
                coordinate[sum]=1+i;//adjust
                sum++;
            }
            second_row[i]=comp;
        }
        stop_pt[1]=sum;

        for(int i=2;i<row;i++){//examine row 2 to row n
            for(int j=1;j<=col;j++){
                int comp;
                in_file>>comp;
                if((second_row[j]>=comp)&&(second_row[j]>=first_row[j])&&(j>=col||second_row[j]>=second_row[j+1])&&(j<=1||second_row[j]>=second_row[j-1])){
                    coordinate[sum]=i+j;
                    sum++;
                }
                third_row[j]=comp;
            }
            //swap
            first_row=second_row;
            second_row=third_row;
            third_row=first_row;
            stop_pt[i]=sum;
        }
        for(int i=1;i<=col;i++){
            if((second_row[i]>=first_row[i])&&(i>=col||second_row[i]>=second_row[i+1])&&(i<=1||second_row[i]>=second_row[i-1])){
                coordinate[sum]=row+i;
                sum++;
            }
        }
    }

    ///output.
    out_file<<sum<<"\n";
    stop_pt[0]=0;
    stop_pt[row]=sum;
    for(int i=1;i<=row;i++){
        for(int j=stop_pt[i-1];j<stop_pt[i];j++){
            out_file<<i<<" "<<coordinate[j]-i<<"\n";
        }
    }
    return 0;
}
