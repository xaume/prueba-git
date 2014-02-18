using namespace std;

class mfSet {
  int *mfs;
  int n;
  int nSubconjuntos;
 public:
  mfSet(int talla); 
  ~mfSet(); 
  int find(int x);
  void merge(int x, int y); // Hace una union por altura. La altura 
                            // de x es -mfs[x]+1 y la de y es -mfs[y]+1.
                            // En caso de empate enlaza el nodo y al nodo x.
  int numSubconjuntos();
  int * obtenRepresentantes();
 int  obtenRepresentanteCompMayor();  //ej adicional 
};
