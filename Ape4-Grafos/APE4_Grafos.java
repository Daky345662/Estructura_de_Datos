import java.util.*;

public class APE4_Grafos {

    // ═══════════════════════════════════════
    // Nodo
    // ═══════════════════════════════════════
    static class Nodo {
        String id;
        String nombre;

        public Nodo(String id, String nombre) {
            this.id = id;
            this.nombre = nombre;
        }
    }

    // ═══════════════════════════════════════
    // Arista
    // ═══════════════════════════════════════
    static class Arista {
        String destino;
        int peso;

        public Arista(String destino, int peso) {
            this.destino = destino;
            this.peso = peso;
        }
    }

    // ═══════════════════════════════════════
    // Grafo
    // ═══════════════════════════════════════
    static class Grafo {

        Map<String, Nodo> nodos = new HashMap<>();
        Map<String, List<Arista>> adyacencia = new HashMap<>();

        /**
         * Agrega un nodo al grafo.
         * @param id Identificador único del nodo
         * @param nombre Nombre descriptivo del nodo
         */
        public void agregarNodo(String id, String nombre) {
            // ========== IMPLEMENTACIÓN ==========
            // 1. Crear un nuevo objeto Nodo con id y nombre
            Nodo nodo = new Nodo(id, nombre);
            
            // 2. Almacenar el nodo en el mapa de nodos usando su id como clave
            nodos.put(id, nodo);
            
            // 3. Inicializar la lista de adyacencia para este nodo (vacía al principio)
            adyacencia.put(id, new ArrayList<>());
            // ====================================
        }

        /**
         * Agrega una arista no dirigida entre dos nodos con un peso específico.
         * @param origen Identificador del nodo origen
         * @param destino Identificador del nodo destino
         * @param peso Peso o distancia de la arista
         */
        public void agregarArista(String origen, String destino, int peso) {
            // ========== IMPLEMENTACIÓN ==========
            // Como es un grafo NO DIRIGIDO, debemos agregar dos aristas:
            // 1. Desde origen hacia destino
            adyacencia.get(origen).add(new Arista(destino, peso));
            
            // 2. Desde destino hacia origen (porque se puede recorrer en ambos sentidos)
            adyacencia.get(destino).add(new Arista(origen, peso));
            // ====================================
        }

        /**
         * BFS (Breadth-First Search) para encontrar la ruta con menos paradas.
         * @param inicio Identificador del nodo inicial
         * @param fin Identificador del nodo destino
         * @return Lista con los ids de los nodos que forman la ruta, o null si no existe
         */
        public List<String> bfs(String inicio, String fin) {
            // ========== IMPLEMENTACIÓN ==========
            // Cola para almacenar los caminos parciales
            Queue<List<String>> cola = new LinkedList<>();
            
            // Conjunto para rastrear nodos ya visitados
            Set<String> visitados = new HashSet<>();
            
            // Camino inicial que solo contiene el nodo de inicio
            List<String> caminoInicial = new ArrayList<>();
            caminoInicial.add(inicio);
            
            // Agregar el camino inicial a la cola
            cola.add(caminoInicial);
            
            // Marcar el nodo inicio como visitado
            visitados.add(inicio);
            
            // Mientras haya caminos por explorar
            while (!cola.isEmpty()) {
                // Obtener el primer camino de la cola
                List<String> camino = cola.poll();
                
                // Obtener el último nodo del camino actual
                String actual = camino.get(camino.size() - 1);
                
                // Si llegamos al destino, devolvemos el camino
                if (actual.equals(fin)) {
                    return camino;
                }
                
                // Explorar todos los vecinos del nodo actual
                for (Arista arista : adyacencia.get(actual)) {
                    // Si el vecino no ha sido visitado
                    if (!visitados.contains(arista.destino)) {
                        // Marcar como visitado
                        visitados.add(arista.destino);
                        
                        // Crear un nuevo camino copiando el actual y agregando el vecino
                        List<String> nuevoCamino = new ArrayList<>(camino);
                        nuevoCamino.add(arista.destino);
                        
                        // Agregar el nuevo camino a la cola
                        cola.add(nuevoCamino);
                    }
                }
            }
            
            // No se encontró ruta
            return null;
            // ====================================
        }

        /**
         * Dijkstra para encontrar la ruta con menor distancia total.
         * @param inicio Identificador del nodo inicial
         * @param fin Identificador del nodo destino
         * @return Lista con los ids de los nodos que forman la ruta óptima
         */
        public List<String> dijkstra(String inicio, String fin) {
            // ========== IMPLEMENTACIÓN ==========
            // Mapa de distancias mínimas desde el inicio a cada nodo
            Map<String, Integer> distancias = new HashMap<>();
            
            // Mapa para reconstruir el camino (nodo anterior)
            Map<String, String> anteriores = new HashMap<>();
            
            // Cola de prioridad para siempre procesar el nodo con menor distancia
            PriorityQueue<String> cola = new PriorityQueue<>(
                    Comparator.comparingInt(distancias::get)
            );
            
            // Inicializar distancias a infinito y anteriores a null
            for (String nodo : nodos.keySet()) {
                distancias.put(nodo, Integer.MAX_VALUE);
                anteriores.put(nodo, null);
            }
            
            // La distancia al nodo inicio es 0
            distancias.put(inicio, 0);
            cola.add(inicio);
            
            // Mientras haya nodos por procesar
            while (!cola.isEmpty()) {
                // Obtener el nodo con menor distancia
                String actual = cola.poll();
                
                // Si llegamos al destino, podemos parar (optimización)
                if (actual.equals(fin)) {
                    break;
                }
                
                // Explorar todos los vecinos del nodo actual
                for (Arista arista : adyacencia.get(actual)) {
                    // Calcular nueva distancia a través del nodo actual
                    int nuevaDistancia = distancias.get(actual) + arista.peso;
                    
                    // Si encontramos una distancia mejor
                    if (nuevaDistancia < distancias.get(arista.destino)) {
                        // Actualizar la distancia mínima
                        distancias.put(arista.destino, nuevaDistancia);
                        
                        // Registrar desde qué nodo llegamos (para reconstruir el camino)
                        anteriores.put(arista.destino, actual);
                        
                        // Agregar/actualizar en la cola de prioridad
                        cola.add(arista.destino);
                    }
                }
            }
            
            // Reconstruir el camino desde el destino hasta el inicio
            List<String> camino = new ArrayList<>();
            String actual = fin;
            
            while (actual != null) {
                camino.add(0, actual);  // Insertar al inicio para tener orden correcto
                actual = anteriores.get(actual);
            }
            
            // Verificar si el camino es válido (el primer nodo debe ser el inicio)
            if (camino.isEmpty() || !camino.get(0).equals(inicio)) {
                return null;  // No hay ruta
            }
            
            return camino;
            // ====================================
        }

        /**
         * Muestra la ruta de forma legible con nombres y códigos.
         * @param ruta Lista de ids de nodos que forman la ruta
         */
        public void mostrarRuta(List<String> ruta) {
            if (ruta == null) {
                System.out.println("No existe ruta");
                return;
            }

            for (int i = 0; i < ruta.size(); i++) {
                String idNodo = ruta.get(i);
                Nodo nodo = nodos.get(idNodo);
                System.out.print(nodo.nombre + " (" + nodo.id + ")");
                if (i < ruta.size() - 1) {
                    System.out.print(" -> ");
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        // Crear el grafo del campus
        Grafo grafo = new Grafo();

        // Agregar nodos (puntos de interés del campus)
        grafo.agregarNodo("uta", "Universidad");
        grafo.agregarNodo("fisei", "FISEI");
        grafo.agregarNodo("idiomas", "Idiomas");
        grafo.agregarNodo("biblioteca", "Biblioteca");
        grafo.agregarNodo("estadio", "Estadio");
        grafo.agregarNodo("comedor", "Comedor");

        // Agregar aristas (conexiones con distancias en metros)
        grafo.agregarArista("uta", "fisei", 50);
        grafo.agregarArista("fisei", "idiomas", 40);
        grafo.agregarArista("idiomas", "biblioteca", 30);
        grafo.agregarArista("biblioteca", "estadio", 70);
        grafo.agregarArista("uta", "comedor", 20);
        grafo.agregarArista("comedor", "estadio", 200);

        System.out.println("═══════════════════════════════════════");
        System.out.println("   MAPA DEL CAMPUS UTA - ANÁLISIS     ");
        System.out.println("═══════════════════════════════════════");
        System.out.println("\n Origen: Universidad (uta)");
        System.out.println(" Destino: Estadio (estadio)\n");

        // ===== BFS: Ruta con menos paradas =====
        System.out.println("===== BFS =====");
        System.out.println(" Buscando ruta con MENOR NÚMERO DE PARADAS...");
        List<String> rutaBFS = grafo.bfs("uta", "estadio");
        System.out.print(" Ruta encontrada: ");
        grafo.mostrarRuta(rutaBFS);
        System.out.println(" Criterio: Mínimo de nodos intermedios\n");

        // ===== DIJKSTRA: Ruta con menor distancia =====
        System.out.println("===== DIJKSTRA =====");
        System.out.println(" Buscando ruta con MENOR DISTANCIA TOTAL...");
        List<String> rutaDijkstra = grafo.dijkstra("uta", "estadio");
        System.out.print(" Ruta encontrada: ");
        grafo.mostrarRuta(rutaDijkstra);
        System.out.println(" Criterio: Mínimo de metros recorridos\n");
    }
}