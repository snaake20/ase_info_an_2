package tcp_ip;

import java.io.IOException;
import java.net.ServerSocket;

// Sa se defineasca clasa GenericTCPMultiClientServer
// care sa implementeze un server TCP/IP ce poate sustine multiple conexiuni client,
// respectiv fiecare conexiune client este gestionata intr-un fir de executie distinct.
// Firul de executie care gestioneaza conexiune la server a unui client este implementat
// in clasa ServerThread.
// Sa se defineasca clasa GenericTCPClient, care sa implementeze un client TCP/IP pentru
// interactiunea cu serverul.
// API-ul de comunicatie intre server si client necesita urmatoarele functionalitati:
// 1. serverul asteapta de la clienti mesaje the tip text pe care le afiseaza la consola serverului
// 2. clientii pot trimite catre server mesaje de tip text, mesaje preluate de la tastatura; cate
// o linie de text la un moment dat
// 3. utilizatorul poate termina o aplicatie client prin introducerea de la tastatura in consola clientului
// a textului EXIT
// 4 mesajul text trimis ca cerere catre server este afisat in consola serverului
// 5. serverul functioneaza indefinit si asteapa conexiuni noi conexiuni client
// 6. serverul raspunde la mesajul text primit de la client prin textul: Ecou server: <mesaj primit de la client>
// 7. mesajul de ecou primit de la server este afisat la consola clientului care a trimit mesajul.

public class GenericTCPMultiClientServer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Utilizare: java GenericTCPMultiClientServer <port>");
            System.exit(-1);
        }

        int port = Integer.parseInt(args[0]);

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Aşteaptă conexiuni client la portul " +
                    serverSocket.getLocalPort() + "...");

            while (true) {
                new ServerThread(serverSocket.accept()).start();
            }
        } catch (IOException e) {
            System.err.println("Conexiune eşuată pe portul " + port);
            System.exit(-2);
        }
    }
}
