import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class NodoN {
    public int valor;
    public List<NodoN> hijos;
    
    public NodoN(int valor) {
        this.valor = valor;
        this.hijos = new ArrayList<>();
    }
    
    public NodoN(int valor, List<NodoN> hijos) {
        this.valor = valor;
        this.hijos = hijos;
    }
}

public class Ejercicio1_Basico {
    public static int contarNodos(NodoN raiz) {
        if (raiz == null) return 0;
        int total = 1;
        for (NodoN hijo : raiz.hijos) {
            total += contarNodos(hijo);
        }
        return total;
    }

    public static void main(String[] args) {
        NodoN n5 = new NodoN(5);
        NodoN n6 = new NodoN(6);
        NodoN n2 = new NodoN(2, Arrays.asList(n5, n6));
        NodoN n3 = new NodoN(3);
        NodoN n4 = new NodoN(4);
        NodoN raiz = new NodoN(1, Arrays.asList(n2, n3, n4));
        
        System.out.println("--- Prueba Ejercicio 1 ---");
        System.out.println("Nodos esperados: 6");
        System.out.println("Nodos calculados: " + contarNodos(raiz));
    }
}