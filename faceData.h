#ifndef FACEDATA_H
#define FACEDATA_H
class FaceData {
    double lX, lY, rX, rY;
    public:
        FaceData();
        FaceData(double, double, double, double);
        double getlX();
        void setlX(double);
        double getlY();
        void setlY(double);
        double getrX();
        void setrX(double);
        double getrY();
        void setrY(double);
} data;
#endif
