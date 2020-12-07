#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class dgl{
    public: 
    //h = Schrittweite delta
    double h_t;
    double h_x;
    //start und ende
    double x_s;
    double x_e;
    //aktuelle Zeit
    double t;
    double t_s;
    double t_e;
    //ab hier Programmcode, oben veränderbare Parameter
    int N;
    //zu berechnende Stützstellen im nächsten Zeitschritt
    //N+1 Stützstellen wegen Rand ("Zaunpfahlprobelm")
    vector<double> u_j1;
    //aktueller, schon berechneter (bekannter) Zeitschritt
    vector<double> u_j;


    //konstruktor
    dgl(double x_s, double x_e, double h_t, double h_x, double t_s, double t_e){
        this->x_s = x_s;
        this->x_e = x_e;
        this->h_t = h_t;
        this->h_x = h_x;
        this->t_s = t_s;
        this->t_e = t_e;

        N = (x_e-x_s)/h_x;

        //mit t beim Startwert anfengen

        t = t_s;
        //Vektor mit N+1 vielen double Werten, der u_j1 zugewiesen wird
        u_j1 = vector<double>(N+1);
        u_j = vector<double>(N+1);
        for (int i=0; i<N+1; i++){
            u_j[i] = this->anfangswert(x_s+i*h_x);
        }

    }

    //Randbedingung als 0 gegeben
    double randbed(double x, double t){
        return 0;
    }

    /**
     bei t=0 den Anfangswert zurückgeben, daher wird nur x als Funktionsparameter benötigt
    **/
    double anfangswert(double x){
        double u_x_0 = 1000 - fabs(1000*x);
        return u_x_0;
    }
    /** 
     * löst einen Schritt der Interation 
     * erhalten einen Pointer auf Speicher, um die berechneten Werte zu speichern
     **/
    void step_solver(){
        //t um einen Schritt erhöhen
        t += h_t;
        //die äußeren Werte sind schon durch die Randbedingung gegeben, daher berechnen wir nur die inneren Werte der Stüzstellen (von i=1 bis i<N)
        u_j1[0] = randbed(x_s,t);
        for(int i=1;i < N;i++) {
            u_j1[i] = u_j[i] + h_t/h_x*h_x*(2*u_j[i]-u_j[i-1]-u_j[i+1]);
        }
        u_j = u_j1;
        
        
    }
};




int main(int argc, const char * argv[]) {
    //dgl(double x_s, double x_e, double h_t, double h_x, double t_s, double t_e)
    dgl mydgl(-1, 1, 0.01, 0.2, 0, 0.2);
    while(mydgl.t < mydgl.t_e){
        mydgl.step_solver();
        cout<<mydgl.t<<endl;
    }
    return 0;
}