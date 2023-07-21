import org.json.JSONArray;
import org.json.JSONTokener;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.*;
import java.util.stream.Collectors;

public class MainProcess {

    public static Map<Integer,Sectie> citireJSON() {
        Map<Integer,Sectie> res = new HashMap<>();

        try (var file = new FileInputStream("./date/sectii.json")) {
            var tokener = new JSONTokener(file);
            var jsonSectii = new JSONArray(tokener);

            for (int i = 0; i < jsonSectii.length() ; i++) {
                var objSectie = jsonSectii.getJSONObject(i);
                res.put(objSectie.getInt("cod_sectie"), new Sectie(objSectie.getInt("cod_sectie"), objSectie.getString("denumire"), objSectie.getInt("numar_locuri")));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return res;
    }

    public static List<Pacient> citireTxt() {
        List<Pacient> res = new ArrayList<>();
        try (var file = new BufferedReader(new FileReader("./date/pacienti.txt"))) {
            res = file.lines().map(l -> new Pacient(Long.parseLong(l.split(",")[0]), l.split(",")[1], Integer.parseInt(l.split(",")[2]), Integer.parseInt(l.split(",")[3]))).toList();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return res;
    }

//    1) Să afișeze la consolă lista secțiilor spitalului cu un număr de locuri strict mai mare decât 5
    public static void afisareSectiiCuPeste5Locuri(Map<Integer,Sectie> sectieMap) {
        sectieMap.forEach((key, value) -> {
            if (value.getNumarLocuri() > 5) {
                System.out.println(value);
            }
        });
    }

//    2) Să afișeze la consolă lista secțiilor spitalului sortată descrescător după varsta medie a pacientilor internați pe secție.
//    Pentru fiecare secție se va afișa codul, denumirea, numărul de locuri și vârsta medie a pacienților.
    public static void afisareSectiiSortateDescDupaVarstaMedie(List<Pacient> pacientList, Map<Integer,Sectie> sectieMap) {
        Map<Integer, Double> varstaMedie = pacientList.stream().collect(Collectors.groupingBy(Pacient::getCodSectie ,Collectors.averagingInt(Pacient::getVarsta)));

        if (varstaMedie.size() != sectieMap.size()) {
            // add the missing keys
            for (var key:
                    sectieMap.keySet()) {
                if (!varstaMedie.containsKey(key)) {
                    varstaMedie.put(key,0.0);
                }
            }
        }

        varstaMedie = varstaMedie.entrySet().stream()
                .sorted(Collections.reverseOrder(Map.Entry.comparingByValue()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue,
                        (oldValue, newValue) -> oldValue, LinkedHashMap::new));

        for (var v:
                varstaMedie.entrySet()) {
            double varsta;
            System.out.println(sectieMap.get(v.getKey()) + "\n varsta medie:" + v);
        }
    }

//    3) Să se scrie în fișierul text raport.txt un raport al internărilor pe secții, de forma:
//    cod_secție_1,nume secție_1,numar_pacienti_1
    public static Map<Integer, SectieSmechera> scrieRaport(List<Pacient> pacientList, Map<Integer,Sectie> sectieMap) {
        Map<Integer, Long> numarPacientiPeSectie = pacientList.stream().collect(Collectors.groupingBy(Pacient::getCodSectie,Collectors.counting()));

//        numarPacientiPeSectie.forEach((k,v) -> System.out.println(k+ " " +v));

        Map<Integer, SectieSmechera> res = new HashMap<>();

        try(var file = new BufferedWriter(new FileWriter("./date/raport.txt"))) {
            for (var sectie:
                 sectieMap.entrySet()) {

                int locuriOcupate;

                if (numarPacientiPeSectie.get(sectie.getKey()) == null) {
                    locuriOcupate = 0;
                } else {
                    locuriOcupate = Math.toIntExact(numarPacientiPeSectie.get(sectie.getKey()));
                }

                file.write(String.format("%d,%s,%d\n", sectie.getKey(), sectie.getValue().getDenumire(), numarPacientiPeSectie.get(sectie.getKey()) == null ? 0 : numarPacientiPeSectie.get(sectie.getKey())));
                res.put(sectie.getKey(), new SectieSmechera(sectie.getKey(), sectie.getValue().getDenumire(), sectie.getValue().getNumarLocuri(), locuriOcupate));
            }
            System.out.println("Scriere cu success a raportului");
        } catch (IOException e) {
            System.out.println("Scriere fara success a raportului");
        }
        return res;
    }

//    4) Să implementeze funcționalitățile de server și client TCP/IP și să se execute următorul scenariu:
//    componenta client trimite serverului codul unei secții iar componenta server va întoarce clientului numărul de locuri libere.
//    Serverul se va opri după raspunsul la o cerere client.

    public static int getLocuriLibere(Map<Integer, SectieSmechera> sectieSmecheraMap, int cod) {
        return sectieSmecheraMap.get(cod).getNumarLocuri() - sectieSmecheraMap.get(cod).getNumarLocuriOcupate();
    }

    public static void main(String[] args) {
        Map<Integer, Sectie> sectii = new HashMap<>();
        List<Pacient> pacienti = new ArrayList<>();
        Map<Integer, SectieSmechera> sectiiSmechere = new HashMap<>();

        sectii = citireJSON();

        pacienti = citireTxt();

//        sectii.forEach((key, value) -> System.out.println(value));

//        pacienti.forEach(System.out::println);

        afisareSectiiCuPeste5Locuri(sectii);

        System.out.println();

        afisareSectiiSortateDescDupaVarstaMedie(pacienti, sectii);

        System.out.println();

        sectiiSmechere = scrieRaport(pacienti, sectii);

//        final int PORT_NUMBER = 8983;
//
//        try(var serverSocket = new ServerSocket(PORT_NUMBER)) {
//            System.out.println("Asteptam conexiunea client");
//
//            try (Socket client = serverSocket.accept();
//                DataOutputStream outputStream = new DataOutputStream(client.getOutputStream());
//                DataInputStream inputStream = new DataInputStream(client.getInputStream());
//            ) {
//                System.out.println("Conexiune client realizata");
//
//                int codDeCautat = inputStream.readInt();
//
//                if (!sectiiSmechere.containsKey(codDeCautat)) {
//                    System.out.println("Nu exista codul");
//                    outputStream.writeInt(-1);
//                } else {
//                    outputStream.writeInt(getLocuriLibere(sectiiSmechere,codDeCautat));
//                    System.out.println("Am trimis " + getLocuriLibere(sectiiSmechere,codDeCautat) + " locuri libere");
//                }
//            }
//
//        } catch (IOException e) {
//            e.printStackTrace();
//        }

//        5) Să se implementeze clientul și serverul ca două fire de execuție ce sunt lansate din firul de execuție principal
//        al procesului.

        Map<Integer, SectieSmechera> finalSectiiSmechere = sectiiSmechere;
        Thread serverThread = new Thread(new Runnable() {
            final int PORT_NUMBER = 8983;
            @Override
            public void run() {

                try(var serverSocket = new ServerSocket(PORT_NUMBER)) {
                    System.out.println("Asteptam conexiunea client");

                    try (Socket client = serverSocket.accept();
                         DataOutputStream outputStream = new DataOutputStream(client.getOutputStream());
                         DataInputStream inputStream = new DataInputStream(client.getInputStream());
                    ) {
                        System.out.println("Conexiune client realizata");

                        int codDeCautat = inputStream.readInt();

                        if (!finalSectiiSmechere.containsKey(codDeCautat)) {
                            System.out.println("Nu exista codul");
                            outputStream.writeInt(-1);
                        } else {
                            outputStream.writeInt(getLocuriLibere(finalSectiiSmechere,codDeCautat));
                            System.out.println("Am trimis " + getLocuriLibere(finalSectiiSmechere,codDeCautat) + " locuri libere");
                        }
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

    }
}
