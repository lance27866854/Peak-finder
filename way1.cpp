#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

std::string in_file_name="matrix.data";
std::string out_file_name="final.peak";

int main(void){
    std::ifstream in_file;
    std::ofstream out_file;
    in_file.open(in_file_name,std::ios::in);
    out_file.open(out_file_name,std::ios::out);

    ///start clock.
    double nStart = clock();

    ///get inputs.
    int matrix[100][100];
    int miss[100][100]={0};
    int row, col;
    in_file>>row>>col;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j+=2){
            in_file>>matrix[i][j];
            in_file>>matrix[i][j+1];
            if(matrix[i][j]>matrix[i][j+1]) miss[i][j+1]=1;
            else if(matrix[i][j]<matrix[i][j+1]) miss[i][j]=1;
        }
        if(col%2==1) in_file>>matrix[i][col-1];
    }

    ///operate.
    int sum=0;
    int x[10000], y[10000];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(miss[i][j]){continue;}
            else{
                if((matrix[i][j]>=matrix[i-1][j]||i<1)&&
                    (matrix[i][j]>=matrix[i+1][j]||i>=row-1)&&
                    (matrix[i][j]>=matrix[i][j-1]||j<1)&&
                    (matrix[i][j]>=matrix[i][j+1]||j>=col-1)){
                        x[sum]=i;
                        y[sum]=j;
                        sum++;
                }
            }
        }
    }

    ///output.
    //std::cout<<"sum = "<<sum<<std::endl;
    out_file<<sum<<std::endl;
    for(int i=0;i<sum;i++){
        //std::cout<<"(x , y) = ( "<<x[i]<<" , "<<y[i]<<" )"<<std::endl;
        out_file<<x[i]<<" "<<y[i]<<std::endl;
    }
    double nEnd = clock();
    std::cout<<"Execution Time : "<<(nEnd - nStart)/ CLOCKS_PER_SEC<<" s."<<std::endl;
    return 0;
}

