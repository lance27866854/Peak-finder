#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]){

    char buffer1[35], buffer2[35];
    std::ifstream in_file1, in_file2;
    sprintf(buffer1, "./%s/afinal.peak", argv[1]);
    sprintf(buffer2, "./%s/final.peak", argv[1]);

    in_file1.open(buffer1,std::ios::in);
    in_file2.open(buffer2,std::ios::in);

    if(!in_file1||!in_file2){std::cout<<"FALL TO READ FILE.\n";return 1;}

    int sum1, sum2;
    in_file1>>sum1;
    in_file2>>sum2;
    if(sum1!=sum2) std::cout<<"sum different.\n";
    else{
        int flag=0;
        int i=0;
        while(!in_file1.eof()&&!in_file2.eof()){
            int x1, y1, x2, y2;
            in_file1>>x1;in_file1>>y1;
            in_file2>>x2;in_file2>>y2;
            if(x1!=x2||y1!=y2){flag=1;std::cout<<"contains wrong. index: "<<i<<"\n";break;}
            i++;
        }
         if(flag==0) std::cout<<"Compare complete.\n";
    }

    return 0;
}
