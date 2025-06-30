# ifndef ELECLIBINT_H
# define ELECLIBINT_H
# include <Arduino.h>
# include <math.h>
// Número de amostragens calculado a partir do ciclo da onda demorar 16.666,67 us
const int AMOSTRAGEM = 166;
// Declaração da classe ElecLibINT
class ElecLibINT {
public:
    ElecLibINT(int pinoSensorCT, int pinoSensorDDP); // Construtor
    void leituraCorrenteTensao();
    void imprimirMedidas();
    float interpolateValue(float inputValue, int* inputPoints, float* outputPoints, int numPoints);
    float tensao_eficaz;
    float corrente_eficaz;
    float potAparente;
private:
    int _pinoSensorCT;
    int _pinoSensorDDP;
};
# endif // ELECLIBINT_H
