#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <queue>

std::string in_file_name="matrix.data";
std::string out_file_name="final.peak";
std::string out_file_time_name="_time.txt";

struct Node{
    int x, y;
    int value;
};

int main(void){
    std::ofstream out_file_time;
    out_file_time.open(out_file_time_name,std::ios::app);
    ///start clock.
    LARGE_INTEGER t1, t2, ts;
    QueryPerformanceFrequency(&ts);
    QueryPerformanceCounter(&t1);

    std::ifstream in_file;
    std::ofstream out_file;
    in_file.open(in_file_name,std::ios::in);
    out_file.open(out_file_name,std::ios::out);

    ///get inputs.
    int matrix[100][100];
    std::queue<Node> q;
    int row, col;
    in_file>>row>>col;
    for(int i=0;i<row;i++){//O(n^2)
        for(int j=0;j<col;j+=2){
            int v1, v2;
            in_file>>v1;
            in_file>>v2;
            matrix[i][j]=v1;
            matrix[i][j+1]=v2;
            if(v1>v2){
                Node n;
                n.x=i;n.y=j;n.value=v1;
                q.push(n);
            }
            else if(v1<v2){
                Node n;
                n.x=i;n.y=j+1;n.value=v2;
                q.push(n);
            }
            else{
                Node n1, n2;
                n1.x=i;n1.y=j;n1.value=v1;
                n2.x=i;n2.y=j+1;n2.value=v2;
                q.push(n1);
                q.push(n2);
            }
        }
        if(col%2==1){
            int v;
            in_file>>v;
            Node n;
            n.x=i;n.y=col-1;n.value=v;
            q.push(n);
        }
    }

    ///operate.
    std::queue<Node> ans;
    int _size=q.size();
    for(int i=0;i<_size;i++){
        int x=q.front().x;
        int y=q.front().y;
        if((matrix[x][y]>=matrix[x-1][y]||x<1)&&
            (matrix[x][y]>=matrix[x+1][y]||x>=row-1)&&
            (matrix[x][y]>=matrix[x][y-1]||y<1)&&
            (matrix[x][y]>=matrix[x][y+1]||y>=col-1)){
                ans.push(q.front());
        }
        q.pop();
    }

    ///output.
    int sum = ans.size();
    out_file<<sum<<std::endl;
    for(int i=0;i<sum;i++){
        out_file<<ans.front().x<<" "<<ans.front().y<<std::endl;
        ans.pop();
    }
    QueryPerformanceCounter(&t2);
    std::cout<<"Execution Time : "<<(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart)<<" s."<<std::endl;

    out_file_time<<(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart)<<"\n";
    return 0;
}

