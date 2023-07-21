import org.json.JSONArray;
import org.json.JSONObject;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

import static java.lang.Thread.sleep;

public class Main {

    public static Map<Integer, Specializare> queryDb() {
        Map<Integer, Specializare> res = new HashMap<>();

        try (
                var conn = DriverManager.getConnection("jdbc:sqlite:data/facultate.db");
                var stmnt = conn.createStatement()
                ) {

            ResultSet query = stmnt.executeQuery("SELECT * FROM SPECIALIZARI");

            while (query.next()) {
                res.put(query.getInt("cod"), new Specializare(query.getInt("cod"), query.getString("denumire"), query.getInt("locuri")));
            }

        } catch (SQLException e) {
            System.out.println("Problema la conexiune cu baza de date");
        }

        return res;
    }

    public static Map<Long, Inscriere> citireTxt() {
        Map<Long, Inscriere> res = new HashMap<>();

        try (
                var file = new BufferedReader(new FileReader("./data/inscrieri.txt"))
                ) {

            res = file.lines().map(l -> new Inscriere(Long.parseLong(l.split(",")[0]), l.split(",")[1], Double.parseDouble(l.split(",")[2]), Integer.parseInt(l.split(",")[3]))).collect(Collectors.toMap(Inscriere::getCnpCandidat, Function.identity()));

        } catch (IOException e) {
            System.out.println("Problema la citirea fisierului");
        }

        return res;
    }

    public static void main(String[] args) throws InterruptedException {
        Map<Integer, Specializare> specializari = queryDb();

//        specializari.forEach((k, v) -> System.out.println(v));

        Map<Long, Inscriere> inscrieri = citireTxt();

        System.out.println("Cerinta 1");

//        1) Sa afiseze pe consola numarul total de locuri disponibile la facultate.

        System.out.printf("Facultatea are %d locuri\n",specializari.values().stream().mapToInt(Specializare::getLocuri).sum());

        System.out.println("Cerinta 2");

//        2) Să se afişeze pe consolă lista specializărilor care, în urma înscrierilor, au cel puţin 10 de locuri disponibile. Pentru fiecare specializare se afiseaza codul specialitatii, denumirea, numarul de locuri disponibile.

        Map<Integer, Long> nrInscrieriAgregate = inscrieri.values().stream().collect(Collectors.groupingBy(Inscriere::getCodSpecializare, Collectors.counting()));

        Map<Integer, Integer> locuriRamase = new HashMap<>();

        specializari.forEach((k, v) -> {

            int nrLocuriDisponibile;

            if (nrInscrieriAgregate.containsKey(k)) {
                nrLocuriDisponibile = (int) (v.getLocuri() - nrInscrieriAgregate.get(k));
            } else {
                nrLocuriDisponibile = v.getLocuri();
            }

            locuriRamase.put(k, nrLocuriDisponibile);

            if (nrLocuriDisponibile >= 10) {
                System.out.println(v + "\n Locuri disponibile: " + nrLocuriDisponibile);
            }

        });

        System.out.println("Cerinta 3");

//        3) Pentru a salva în fișierul json înregistrări specializari.json numărul de înregistrări pentru fiecare specializare și
//        valoarea medie a notelor de bacalaureat pentru candidaţii înscrişi la fiecare specializare.
//        Fișierul json are următorul format:
//
//        „cod de specializare”: 1,
//        „nume”: „Cibernetică”,
//        "număr de înmatriculări": 7,
//        „medie: 9,35

        Map<Integer, Double> mediiInscrieriAgregate = inscrieri.values().stream().collect(Collectors.groupingBy(Inscriere::getCodSpecializare, Collectors.averagingDouble(Inscriere::getNotaBacalaureat)));

        JSONArray jsonSpecializari = new JSONArray();

        for (var specializare:
             specializari.entrySet()) {

            var jsonSpecializare = new JSONObject();

            jsonSpecializare.put("medie", mediiInscrieriAgregate.get(specializare.getKey()) != null ? mediiInscrieriAgregate.get(specializare.getKey())  : 0);
            jsonSpecializare.put("numar_de_inmatriculari", nrInscrieriAgregate.get(specializare.getKey()) != null ? nrInscrieriAgregate.get(specializare.getKey()) : 0);
            jsonSpecializare.put("nume", specializare.getValue().getDenumire());
            jsonSpecializare.put("cod_de_specializare", specializare.getValue().getCod());

            jsonSpecializari.put(jsonSpecializare);

        }

        try (
                var file = new FileWriter("specializari.json");
                ) {

            jsonSpecializari.write(file, 3, 0);

        } catch (IOException e) {
            System.out.println("Eroare la salvarea raportului");
        }

        System.out.println("Cerinta 4");

//        4) Pentru a implementa serverul TCP/IP și funcționalitățile client pentru a executa următorul scenariu:  componenta client trimite numele unei specializări către server, iar componenta server îl va intoarce clientului, pentru specializarea respectivă, numărul de locuri rămase disponibile după înscriere.  serverul se va opri după ce răspunde la o solicitare a clientului.

        Thread server = new Thread(new Runnable() {
            @Override
            public void run() {
                try (var serverSocket = new ServerSocket(8983)) {
                    System.out.println("Se asteapta conexiune la server");
                    try (
                            var client = serverSocket.accept();
                            var in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                            var out = new PrintWriter(client.getOutputStream(), true);
                    ) {
                        System.out.println("Clientul s-a conectat");

                        String nume = in.readLine();

                        System.out.println("Numele primit este: " + nume);

                        int cod = -1;

                        for (var specializare:
                                specializari.entrySet()) {
                            int k = specializare.getKey();
                            Specializare v = specializare.getValue();

                            if (v.getDenumire().equalsIgnoreCase(nume)) {
                                cod = k;
                                break;
                            }
                        }

                        if (cod != -1) {
                            if (locuriRamase.containsKey(cod)) {
                                out.println(locuriRamase.get(cod));
                                System.out.println("Pentru numele: " + nume + " nr de locuri ramase este: " + locuriRamase.get(cod));
                            }
                        } else {
                            out.println(-1);
                            System.out.println("Nu exista");
                        }
                    }

                } catch (IOException e) {
                    System.out.println("Problema la pornirea server-ului");
                }
            }
        });

        server.start();



        Thread client = new Thread(new Runnable() {
            @Override
            public void run() {
                try (
                        var clientSocket = new Socket("localhost", 8983);
                        var in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                        var out = new PrintWriter(clientSocket.getOutputStream(), true)
                ) {

                    System.out.println("S-a realizat conectarea cu server-ul");

                    String nume = "cibernetica";

                    out.println(nume);

                    System.out.println("S-a trimis numele: " + nume);

                    System.out.println("S-a receptionat: " + in.readLine());

                } catch (IOException e) {
                    System.out.println("Problema la conectarea");
                }
            }
        });


        client.start();

        server.join();

        client.join();

    }
}
