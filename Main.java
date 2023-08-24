import java.io.File;
import java.util.Scanner;

public class Main {
    public static int[] vertexSet(int vertex, boolean[][] matrix, int size, String type)  {
        int[] joint = new int[size];
        int counter = 0;

        if(type.equals("sucessor")) {
            for(int i = 0; i < size; i++) {
                if(matrix[vertex][i]) {
                    joint[counter++] = i;
                }
            }
        } else if(type.equals("predecessor")) {
            for(int i = 0; i < size; i++) {
                if(matrix[i][vertex]) {
                    joint[counter++] = i;
                }
            }
        }

        return joint;
    }

    public static int vertexDegree(int vertex, boolean[][] matrix, int size, String type) {
        int counter = 0;

        if(type.equals("sucessor")) {
            for(int j = 0; j < size; j++) {
                if(matrix[vertex][j]) {
                    counter++;
                }
            }
        } else if(type.equals("predecessor")) {
            for(int j = 0; j < size; j++) {
                if(matrix[j][vertex]) {
                    counter++;
                }
            }
        }

        return counter;
    }

    public static int highestDegreeVertex(boolean[][] matrix, int size, String type) {
        int vertex = 0, degree = 0, counter = 0;

        for(int i = 0; i < size; i++) {
            counter = vertexDegree(i, matrix, size, type);

            if(degree < counter) {
                degree = counter;
                vertex = i;
            }
        }

        return vertex;
    } 
    
    public static void sucessor(boolean[][] matrix, int size) {
        typesOfVertice(matrix, size, "sucessor");
    }

    public static void predecessor(boolean[][] matrix, int size) {
        typesOfVertice(matrix, size, "predecessor");
    }

    public static void typesOfVertice(boolean[][] matrix, int size, String type) {
        int highestVertex = highestDegreeVertex(matrix, size, type);
        int degree = vertexDegree(highestVertex, matrix, size, type);
        int[] joint = vertexSet(highestVertex, matrix, size, type);
        
        System.out.println("Vertice de maior Grau (" + type + "): " + highestVertex + " Grau: " + degree);
        System.out.print("Conjunto: {");
        
        for(int i = 0; i < degree; i++) {
            if(i == degree - 1) {
                System.out.println(joint[i] + "}");
            } else {
                System.out.print(joint[i] + ", ");
            }
        }

        System.out.println();
    }

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("graph-test-100.txt"));
        int vertices, edge, sucessor, predecessor;
        boolean[][] matrix;

        vertices = sc.nextInt();
        edge = sc.nextInt();
        matrix = new boolean[vertices + 1][vertices + 1];

        for(int i = 0; i < edge; i++) {
            sucessor = sc.nextInt();
            predecessor = sc.nextInt();
            matrix[sucessor][predecessor] = true;
        }

        sucessor(matrix, vertices);
        predecessor(matrix, vertices);

        sc.close();
    }
}