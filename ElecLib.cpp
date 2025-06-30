# include "ElecLibINT.h"
// Construtor
ElecLibINT::ElecLibINT(int pinoSensorCT, int pinoSensorDDP) {
    _pinoSensorCT = pinoSensorCT;
    _pinoSensorDDP = pinoSensorDDP;
    // Definindo os pinos como entradas
    pinMode(_pinoSensorCT, INPUT);
    pinMode(_pinoSensorDDP, INPUT);
}
// Definição do método para leitura da corrente e tensão elétrica com cálculo de outras medidas
void ElecLibINT::leituraCorrenteTensao() {
    float valor1 = 0;
    float valor2 = 0;
    // Cálculo do valor máximo
    unsigned long startTime = micros();
    unsigned long duration = 16670; // 16,67 ms em microssegundos (1/60s)
    int maxValor1 = 0;
    int maxValor2 = 0;
    // Captura o valor máximo durante o intervalo
    while (micros() - startTime < duration) {
    int valor1 = analogRead(_pinoSensorCT);
    int valor2 = analogRead(_pinoSensorDDP);
    if (valor1 > maxValor1) {
    maxValor1 = valor1;
    }
     if (valor2 > maxValor2) {
    maxValor2 = valor2;
    }
    }
    // Calcula tensão de pico usando seu polinômio
    float tensao_pico = 0.0097*pow(maxValor2, 2)-10.778*maxValor2+3003.9;
    // Calcula tensão eficaz assumindo seno puro
    tensao_eficaz = tensao_pico / sqrt(2);
    // Calcula corrente de pico usando seu polinômio
    float corrente_pico = 1e-7 * pow(maxValor1,3)
                        -0.0002 * pow(maxValor1, 2)
                        +0.1503 * maxValor1
                        -18.877;
    // Calcula corrente eficaz assumindo seno puro
    corrente_eficaz = corrente_pico / sqrt(2);
    potAparente = tensao_eficaz * corrente_eficaz;
}
// Definição do método para imprimir medidas
void ElecLibINT::imprimirMedidas() {
    Serial.println("Tensão Eficaz: " + String(tensao_eficaz) + " V"+
                   "\nCorrente Eficaz: " + String(corrente_eficaz) +" A"+
                   "\nPotência Aparente: " + String(potAparente) +" VA");
}
