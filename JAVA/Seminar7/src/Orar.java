import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.*;
import java.util.concurrent.atomic.AtomicReference;
import java.util.function.Function;
import java.util.stream.Collectors;


class Profesor {
    private final int idProfesor;
    private final String prenume;
    private final String nume;
    private final String departament;

    public Profesor(int idProfesor, String prenume, String nume, String departament) {
        this.idProfesor = idProfesor;
        this.prenume = prenume;
        this.nume = nume;
        this.departament = departament;
    }

    public int getIdProfesor() {
        return idProfesor;
    }

    public String getPrenume() {
        return prenume;
    }

    public String getNume() {
        return nume;
    }

    public String getNumeComplet(){
        return getNume() + " " + getPrenume();
    }

    public String getDepartament() {
        return departament;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Profesor{");
        sb.append("idProfesor=").append(idProfesor);
        sb.append(", prenume='").append(prenume).append('\'');
        sb.append(", nume='").append(nume).append('\'');
        sb.append(", departament='").append(departament).append('\'');
        sb.append('}');
        return sb.toString();
    }
}

class Programare {
    private final String ziua;
    private final String interval;
    private final Profesor profesor;
    private final String disciplina;
    private final String sala;
    private final boolean esteCurs;
    private final String formatie;

    public Programare(String ziua, String interval, Profesor profesor, String disciplina, String sala, boolean esteCurs, String formatie) {
        this.ziua = ziua;
        this.interval = interval;
        this.profesor = profesor;
        this.disciplina = disciplina;
        this.sala = sala;
        this.esteCurs = esteCurs;
        this.formatie = formatie;
    }

    public String getZiua() {
        return ziua;
    }

    public String getInterval() {
        return interval;
    }

    public Profesor getProfesor() {
        return profesor;
    }

    public String getDisciplina() {
        return disciplina;
    }

    public String getSala() {
        return sala;
    }

    public boolean esteCurs() {
        return esteCurs;
    }

    public String getFormatie() {
        return formatie;
    }

    @Override
    public String toString() {
        return "Programare{" + "ziua='" + ziua + '\'' +
                ", interval='" + interval + '\'' +
                ", profesor=" + profesor +
                ", disciplina='" + disciplina + '\'' +
                ", sala='" + sala + '\'' +
                ", esteCurs=" + esteCurs +
                ", formatie='" + formatie + '\'' +
                '}';
    }
}

public class Orar {
    public static void afisareOrarGrupa(String grupa, List<Programare> programari,
                                        Map<String, List<String>> componentaSerii) {
//        System.out.println(programari);
//        System.out.println(componentaSerii);

        // Determinarea seriei din care face parte grupa primita ca parametru
        // TODO

        // Tiparire antet
        System.out.printf("%-10s %-20s %-50s %-10s %-10s%n",
                "Ziua", "Interval orar", "Disciplina", "Sala", "Curs/Seminar");

        // Afisare orar grupa
        // TODO
    }

    public static void main(String[] args) throws Exception {

        // 1. Citire date
        Map<Integer, Profesor> profesori;
        List<Programare> programari;

        try(BufferedReader fisierProfesor = new BufferedReader(new FileReader("./data/profesori.txt"))) {
            profesori = fisierProfesor.lines().map(linie -> (new Profesor(
                    Integer.parseInt(linie.split("\t")[0]), linie.split("\t")[1], linie.split("\t")[2], linie.split("\t")[3]
            ))).collect(Collectors.toMap(Profesor::getIdProfesor, Function.identity())); // Function.identity se refera la mapul de inainte
        }

//        for (var entry: profesori.entrySet()) {
//            System.out.println(entry.getValue());
//        }

        try(BufferedReader fisierProgramari = new BufferedReader(new FileReader("./data/programari.txt"))) {
            programari = fisierProgramari.lines().map(linie -> (new Programare(
                    linie.split("\t")[0], linie.split("\t")[1], profesori.get(Integer.parseInt(linie.split("\t")[2])), linie.split("\t")[3], linie.split("\t")[4], Boolean.parseBoolean(linie.split("\t")[5]), linie.split("\t")[6]
            ))).toList();
        }

//        programari.forEach(System.out::println);

        // 2. Prelucrari
        // Afișare lista cursuri în ordine alfabetică

        programari.stream().filter(Programare::esteCurs).map(Programare::getDisciplina).distinct().sorted().forEach(System.out::println);

        // Afișare număr de activități pentru fiecare profesor
//        profesori.forEach((key, value) -> System.out.println(value.toString() + "\n Aparitii: " + programari.stream().filter(pr -> key == pr.getProfesor().getIdProfesor()).toList().size()));

        programari.stream()
                .collect(Collectors.groupingBy(Programare::getProfesor))
                .forEach((profesor, programariProfesor) -> {
                    System.out.printf("%30s %2d %2d%n",
                            profesor.getNumeComplet(),
                            programariProfesor.stream().filter(Programare::esteCurs).count(),
                            programariProfesor.stream().filter(p -> !p.esteCurs()).count());
                });
        // Lista departamentelor ordonate descrescator dupa numărul de activități
        // Definire clasa Departament
        // TODO

    }
}
