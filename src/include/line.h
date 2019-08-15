#include"root.h"
/*
    rappresenta una riga dell'area di gioco
    - si limita a contenere una rappresentazione minimale dei vari oggetti
        - identificativo per il tipo + lungezza dell'oggetto   
            - si potrebbero usare anche oggetti a dimensione fissa
    - può verificare se in una data posizione si verifica una collisione

    interfaccia leggera e semplice, così da nascondere la complessità interna
*/
class Line {

    private:
        //pixel length of a Line on screen
        static float dim;
        //numero di elementi della Line
        const size_t n;
        //array di elementi: ogni char corrisponde a un elemento
        const char elements[];
        //array di posizioni: elements[i] sarà in posizione positions[i] (con head = 0)
        float positions[];
        //offset sulle posizioni: in ogni momento, la posizione reale di ogni elemento sarà ( positions[i] + head ) % dim
        float head;

    protected:
    
    public:
        Line();
        Line(const Line&);
        //getter for the length of a line
        static const float& getLineDimension();
        //setter for the length of a line
        static void setLineDimension(const float&);
};