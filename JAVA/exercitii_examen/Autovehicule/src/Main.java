import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.*;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Main {

//    1) Să afișeze la consolă autovehiculele care au parcurs mai mult de 100000 km.
//    Pentru fiecare autovehicul se va afișa numărul de înmatriculare și numărul de kilometri parcurși
//    2) Să afișeze la consolă costul reviziilor pentru fiecare autovehicul.
//    Pentru fiecare autovehicul se va afișa numărul de înmatriculare și costul reviziilor.
//    3) Să se scrie în fișierul text raport.txt un raport al reviziilor pe autovehicule, de forma:
//    numar_inmatriculare_1
//    data_revizie_1,tip_revizie_1,km_1,cost_revizie_1
//    data_revizie_2,tip_revizie_2,km_2,cost_revizie_2
//    ...

    private static Map<String, Autovehicul> citireTxt() {
        Map<String, Autovehicul> res = new HashMap<>();
        try(var file = new BufferedReader(new FileReader("./date/autovehicule.txt"))) {
            res = file.lines().map(l -> new Autovehicul(l.split(",")[0], LocalDate.parse(l.split(",")[1], DateTimeFormatter.ofPattern("dd.MM.yyyy")), Integer.parseInt(l.split(",")[2]))).collect(Collectors.toMap(Autovehicul::getNumarInmatriculare, Function.identity()));
        }catch (IOException e) {
            System.out.println("Fisierul nu a putut fi citit");
        }
        return res;
    }

    private static List<Revizie> queryDb() {
        List<Revizie> res = new ArrayList<>();

        try (Connection connection = DriverManager.getConnection("jdbc:sqlite:date/examen.db");
            Statement statement = connection.createStatement();) {


            ResultSet resultSet = statement.executeQuery("SELECT * FROM REVIZII");

            // numar_inmatriculare - text - cheie primară
            // data_revizie - text - în format dd.MM.yyyy
            // tip_revizie - text - cu valori ITP pentr inspecțiile tehnice obligatorii sau TPU pentru reviziile tehnice voluntare
            // km - integer - reprezinta valoarea kilometrajului la momentul reviziei (int)
            // cost_revizie - double

//            resultSet.beforeFirst();

            while(resultSet.next()) {
                res.add(new Revizie(resultSet.getString("numar_inmatriculare"), LocalDate.parse(resultSet.getString("data_revizie"), DateTimeFormatter.ofPattern("dd.MM.yyyy")), TipRevizie.valueOf(resultSet.getString("tip_revizie")), resultSet.getInt("km"), resultSet.getDouble("cost_revizie")));
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return res;
    }

    private static int returnNrDeRevizii(Map<String, List<Revizie>> r, String s ) {
        return r.get(s).size();
    }

    public static void main(String[] args) {
        Map<String, Autovehicul> autovehicule = citireTxt();
        List<Revizie> revizii = queryDb();

        System.out.println("cerinta 1");

        autovehicule.forEach((k,v) -> {
            if (v.getKilometraj() > 100000) {
                System.out.println(v);
            }
        });

//        System.out.println("test");
//
//        revizii.forEach((v) -> System.out.println(v));

        System.out.println("Cerinta 2");

        revizii.stream().collect(Collectors.groupingBy(Revizie::getNumarInmatriculare, Collectors.summingDouble(Revizie::getCostRevizie))).forEach((s, aDouble) -> {
            System.out.println(s + " " + aDouble);
        });

        System.out.println("Cerinta 3");

        try (var file = new BufferedWriter(new FileWriter("raport.txt"))) {
            revizii.stream().collect(Collectors.groupingBy(Revizie::getNumarInmatriculare)).forEach((s, revizies) -> {
                try {
                    file.write(String.format("%s\n", s));
                    revizies.forEach(r -> {
                        try {
                            file.write(r.returnDetalii());
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }
                    });
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }

            });
            System.out.println("Scriere raport cu success");
        } catch (IOException e) {
            System.out.println("Nu s-a putut scrie in fisier");
        }

//        4) Să implementeze funcționalitățile de server și client TCP/IP și să se execute următorul scenariu: componenta client
//        trimite serverului un număr de înmatriculare iar componenta server va întoarce clientului numărul reviziilor făcute
//        pentru autovehiculul respectiv. Serverul se va opri după satisfacerea unei cereri client
//        1 punct - afișarea la consolă de către server a numărului de înmatriculare primit de la client
//        1 punct - afișarea la consolă de către client a numărului de revizii primit de la server

        System.out.println("cerinta 4");

        Map<String, List<Revizie>> reviziiGrupate = revizii.stream().collect(Collectors.groupingBy(Revizie::getNumarInmatriculare));

        try (ServerSocket s = new ServerSocket(8983)) {
            System.out.println("Se asteapta conexiuni");

            try (
                    Socket client = s.accept();
                    DataInputStream in = new DataInputStream(client.getInputStream());
                    DataOutputStream out = new DataOutputStream(client.getOutputStream());
                    ) {
                System.out.println("S-a realizat conexiunea cu: " + client.getLocalAddress());

                String nr = in.readUTF();

                System.out.println("S-a primit nr de inmatriculare: " + nr);

                if (!reviziiGrupate.containsKey(nr)) {
                    System.out.println("nr primit nu exista");
                    out.writeInt(-1);
                } else {
                    System.out.println(reviziiGrupate.get(nr));

                    out.writeInt(returnNrDeRevizii(reviziiGrupate, nr));
                }

                System.out.println("Conexiunea s-a inchis");

            }

        } catch (IOException e) {
            System.out.println("sth went wrong");
        }

    }
}
