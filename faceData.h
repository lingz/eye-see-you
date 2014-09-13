#ifndef FACEDATA_H
#define FACEDATA_H
class FaceData {
    double lX, lY, rX, rY;
    public:
        FaceData() {};
        FaceData(double lX, double lY, double rX, double rY){
            this->lX = lX;
            this->lY = lY;
            this->rX = rX;
            this->rY = rY;
        };
        double getlX();
        void setlX(double);
        double getlY();
        void setlY(double);
        double getrX();
        void setrX(double);
        double getrY();
        void setrY(double);
};
#endif
