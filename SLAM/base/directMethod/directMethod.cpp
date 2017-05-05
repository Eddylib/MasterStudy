#include <iostream>
#include <string>
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
// read image 1 depth map 1
// read image 2
//
// select good points on image 1.
//
// calculated se3 with Gauss-Newton.
using namespace std;
int main(int argc, char *argv[]){
    if(argc != 4){
        cout<<"usage: ./command img1 depth1 img2"<<endl;
        exit(0);
    }
    string img1path = argv[1];
    string depth1path = argv[2];
    string img2path = argv[3];
    boost::filesystem::path des(img1path);
    if(!boost::filesystem::is_regular(boost::filesystem::path(img1path))){
        printf("bad fail path!\n");
        exit(0);
    }
    cout<<"hello world!"<<endl;
}