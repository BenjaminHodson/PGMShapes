#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include "math.h"

#define HW 400
using namespace std;

ofstream output;
ifstream input;

//2d array for canvas
int pixels[HW][HW];

string magic = "P2";    //Magic Number
int maxpix = 255;   //Max pixels


int gsvError(int gsv){      //Function to check if Grey scale value is out of bounds
    if (gsv > 255 || gsv < 0){
        gsv = 125;
    }
    return gsv;
}

//Draw Rectangle
int rect() {
    int xcoord;
    int ycoord;
    int height;
    int width;
    int gsv;

    input >> xcoord >> ycoord >> width >> height >> gsv;     //taking values in text file in order to generate shape

    int xscale = xcoord + width;                             //point where the shape starts + width of the shape being drawn
    int yscale = ycoord + height;                            //point where the shape starts + length of the shape being drawn

    for (int y = ycoord; y < yscale; ++y) {

        for (int x = xcoord; x < xscale; ++x) {
            if(x < 0 || x > 399 || y < 0 || y > 399){       //If outside of 400x400 canvas Stop drawing
                break;
            }
            pixels[y][x] = gsv;                             //fill pixel array with
        }
    }
    return 0;
}

int square() {
    int xcoord;
    int ycoord;
    int size;
    int gsv;

    input >> xcoord >> ycoord >> size >> gsv;               //taking values in text file in order to generate shape

    for (int y = ycoord; y < ycoord + size; ++y) {

        for (int x = xcoord; x < xcoord + size; ++x) {

            if(x < 0 || x > 399 || y < 0 || y > 399){       //If outside of 400x400 canvas Stop drawing
                break;
            }
            pixels[y][x] = gsv;

        }
    }
    return 0;
}

//Draw Triangle
int tri() {
    int xcoord;
    int ycoord;
    int size;
    int gsv;
    int inc = 0;

    input >> xcoord >> ycoord >> size >> gsv;              //taking values in text file in order to generate shape

    int xcent = xcoord + (size / 2);
    int ycent = ycoord + (size / 2);


    for (int y = ycoord; y < ycent; ++y) {

        for (int x = xcoord; x < xcent + size; ++x) {

            if (x < 0 || x > 399 || y < 0 || y > 399) {     //If outside of 400x400 canvas Stop drawing
                break;
            }
            if (x <= xcent + inc && x >= xcent - inc) {
                pixels[y][x] = gsv;
            }
        }
        inc++;
    }
    return 0;
}

//Draw Circle
int circ() {
    int radius;
    int xcoord;
    int ycoord;
    int gsv;

    input >> xcoord >> ycoord >> radius >> gsv;

    int xcirc = xcoord + radius;
    int ycirc = ycoord + radius;

    gsv = gsvError(gsv);



    for (int y = ycoord; y < ycoord + (radius * 2); ++y) {

        for (int x = xcoord; x < xcoord + (radius * 2); ++x) {
            if(x < 0 || x > 399 || y < 0 || y > 399){               //If outside of 400x400 canvas Stop drawing
                break;
            }
                if(sqrt(pow(x - xcirc, 2) + pow(y - ycirc, 2)) <= radius) {
                    pixels[y][x] = gsv;
            }
        }
    }
    return 0;
}

//Draws shapes
int draw(){
    for (int i = 0; i < HW; ++i) {
        for (int j = 0; j < HW; ++j) {

            output << pixels[i][j] << " ";
        }
    }
    return 0;
}

//Reset Canvas
int reset(){
    for (int x = 0; x < HW; ++x) {
        for (int y = 0; y < HW; ++y) {

            pixels[x][y] = 255;
        }
    }
    return 0;
}

int argCounter(int argc){                   //function to throw an error if too many or too little arguments are entered
    if (argc != 3){
        cerr << "Incorrect number of arguments";
    }
}

 ifstream inputF(char *argv){               //function to handle all input
    ifstream inputs;
    inputs.open(argv, ifstream::in);

    if(!inputs.is_open()){
        cerr << "File: " << argv << " Cant be opened";
        exit(1);
    }
    return inputs;
}

ofstream outputF(char *argv){               //function to handle all output
    ofstream outputs;
    outputs.open(argv, ofstream::out);

    if(!outputs.is_open()){
        cerr << "File: " << argv << " Cant be opened";
        exit(1);
    }
    return outputs;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {

    string shape;

    input = inputF(argv[1]);
    output = outputF(argv[2]);

    argCounter(argc);

    reset();
    while(input >> shape){                  //handles generating the correct shapes
        if (shape == "rectangle" ){
            rect();
        }
        if (shape == "square"){
            square();
        }
        if (shape == "triangle"){
            tri();
        }
        if(shape == "circle"){
            circ();

        }

    }

    //Outputs the header information
    output << magic << endl << HW << " " << HW << endl << maxpix << endl ;


    draw();
    output.close();
    input.close();

}