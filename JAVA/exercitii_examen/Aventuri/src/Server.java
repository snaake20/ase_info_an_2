import org.json.JSONArray;
import org.json.JSONTokener;

import java.io.*;
import java.net.ServerSocket;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Server {

    private static Map<Integer, Aventura> citireJSON() {
        Map<Integer,Aventura> res = new HashMap<>();

        try (
                var file = new FileReader("./date/aventuri.json")
                ) {
            var json = new JSONArray(new JSONTokener(file));

            for (int i = 0; i < json.length(); i++) {
                var obj = json.getJSONObject(i);
                res.put(obj.getInt("cod_aventura"), new Aventura(obj.getInt("cod_aventura"), obj.getString("denumire"), obj.getDouble("tarif"), obj.getInt("locuri_disponibile")));
            }


        } catch (IOException e) {
            System.out.println("Eroare la parsarea json-ului");
        }

        return res;
    }

    private static Map<String, Rezervare> citireTxt() {
        Map<String, Rezervare> res = new HashMap<>();

        try (
                var file = new BufferedReader(new FileReader("./date/rezervari.txt"))
                ) {

            res = file.lines().map(l -> new Rezervare(l.split(",")[0], Integer.parseInt(l.split(",")[1]), Integer.parseInt(l.split(",")[2]))).collect(Collectors.toMap(Rezervare::getIdRezervare, Function.identity()));

        } catch (IOException e) {
            System.out.println("Nu s-a putut parsa fisierul txt");
        }

        return res;
    }

    public static void main(String[] args) {
        Map<Integer, Aventura> aventuri = citireJSON();
        Map<String, Rezervare> rezervari = citireTxt();

//        1) Pentru a afișa pe consolă lista aventurilor care au un număr de locuri disponibile mai mare sau egal cu 20.

        System.out.println("Cerinta 1");

        aventuri.forEach((k,v) -> {
            if (v.getLocuriDisponibile() >= 20) {
                System.out.println(v);
            }
        });

//        2) Sa afiseze pe consola lista aventurilor care, in urma rezervarilor facute, mai au cel putin 5 locuri disponibile.
//        Pentru fiecare aventură, codul aventurii, numele, numărul de locuri disponibile sunt afișate.

        System.out.println("Cerinta 2");

        var nrDeLocuriRezervatePerAventura = rezervari.values().stream().collect(Collectors.groupingBy(Rezervare::getCodAventura, Collectors.summingInt(Rezervare::getNrLocuriRezervate)));

        aventuri.forEach((k,v) -> {
            if (nrDeLocuriRezervatePerAventura.containsKey(k)) {
                int nrLocuri = v.getLocuriDisponibile()- nrDeLocuriRezervatePerAventura.get(k);
                if (nrLocuri >= 5) {
                    System.out.println(v + "\nNumarul de locuri libere in urma rezervarilor este: " + nrLocuri);
                }
            } else {
                System.out.println(v + "\nNumarul de locuri libere in urma rezervarilor este: " + v.getLocuriDisponibile());
            }
        });

//        3) Salvați în fișierul text venituri, trimiteți prin txt valoarea obținută din fiecare activitate a parcului de aventură ca urmare a rezervărilor efectuate. Aventurile sunt scrise în dosar în ordinea alfabetică a denumirii. Pentru fiecare aventură, o linie este scrisă în fișierul in formatul: numele aventurii, numărul_de locuri rezervate, valoarea

        System.out.println("Cerinta 3");

        var aventuriSortateAlfabetic = aventuri.entrySet().stream().sorted(Comparator.comparing(a -> a.getValue().getDenumire())).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (oldV, newV) -> oldV, LinkedHashMap::new));

        try (
                var file = new BufferedWriter(new FileWriter("revenue.txt"))
                ) {

                    aventuriSortateAlfabetic.forEach((k,v) -> {
                        if (nrDeLocuriRezervatePerAventura.containsKey(k)) {
                            try {
                                file.write(String.format("%s,%d,%.2f\n", v.getDenumire(), nrDeLocuriRezervatePerAventura.get(k),v.getTarif() * nrDeLocuriRezervatePerAventura.get(k)));
                            } catch (IOException e) {
                                System.out.println("Nu s-a putut scrie randul corespunzator aventurei: " + v.getCodAventura());
                            }
                        } else {
                            try {
                                file.write(String.format("%s,%d,%.2f\n", v.getDenumire(),0,0.0));
                            } catch (IOException e) {
                                System.out.println("Nu s-a putut scrie randul corespunzator aventurei: " + v.getCodAventura());
                            }
                        }
                    });
                    System.out.println("Raport scris cu succes");
        } catch (IOException e) {
            System.out.println("Nu s-a putut scrie in fisier");
        }

//        4) Să implementeze serverul TCP/IP și funcționalitățile client și să execute următorul scenariu:
//        componenta client trimite numele unei aventuri către server, iar componenta server va returna clientului numărul de locuri                  disponibil pentru acea aventură. Serverul poate răspunde la orice solicitare din partea clientului.

        System.out.println("Cerinta 4");

        try (var server = new ServerSocket(8983)) {

            System.out.println("Server pornit se asteapta conexiunea clientilor...");

            try (
                    var client = server.accept();
                    var in = new DataInputStream(client.getInputStream());
                    var out = new DataOutputStream(client.getOutputStream())
                    ) {
                System.out.println("S-a conectat un client");

                String nume = in.readUTF();

                System.out.println("Clientul a trimis numele (aventurei): " + nume);


                int cod = -1;

                for (var a:
                     aventuri.values()) {
                    if (a.getDenumire().compareToIgnoreCase(nume) == 0) {
                        cod = a.getCodAventura();
                        break;
                    }
                }

                if (cod != -1) {
                    System.out.printf("Aventura cu numele: %s are %d locuri disponibile%n", aventuri.get(cod).getDenumire(), nrDeLocuriRezervatePerAventura.containsKey(cod) ? aventuri.get(cod).getLocuriDisponibile() - nrDeLocuriRezervatePerAventura.get(cod) : aventuri.get(cod).getLocuriDisponibile());
                    out.writeInt(nrDeLocuriRezervatePerAventura.containsKey(cod) ? aventuri.get(cod).getLocuriDisponibile() - nrDeLocuriRezervatePerAventura.get(cod) : aventuri.get(cod).getLocuriDisponibile());

                } else {
                    System.out.println("Numele furnizat este invalid");
                    out.writeInt(-1);
                }
            }

        } catch (IOException e) {
            System.out.println("Nu s-a putut porni server-ul");
        }

//        Implementarea serverului multithreaded aventură 1 punct: fiecare conexiune client este servită într-un fir separat TODO

    }
}
