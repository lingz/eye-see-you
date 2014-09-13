#include "faceData.h"
#include <stdio.h>

FaceData::FaceData(){

}

FaceData::FaceData(double lX, double lY, double rX, double rY){
    this->lX = lX;
    this->lY = lY;
    this->rX = rX;
    this->rY = rY;
}

double FaceData::getlX() {
    return lX;
}

void FaceData::setlX(double lX) {
    this->lX = lX;
}

double FaceData::getlY() {
    return lY;
}

void FaceData::setlY(double lY) {
    this->lY = lY;
}

double FaceData::getrX() {
    return rX;
}

void FaceData::setrX(double rX) {
    this->rX = rX;
}

double FaceData::getrY() {
    return rY;
}

void FaceData::setrY(double rY) {
    this->rY = rY;
}
