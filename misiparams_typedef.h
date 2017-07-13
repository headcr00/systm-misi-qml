#ifndef MISIPARAMS_TYPEDEF_H
#define MISIPARAMS_TYPEDEF_H

typedef struct{
    double refvolt;
    double supvolt;
    double shuntres;
    double protres;
    double lineres;
    double submres;
    double cblockres;
    double mcuVolt;
    bool useMcuVolt;
} MisiParams;

#endif // MISIPARAMS_TYPEDEF_H
