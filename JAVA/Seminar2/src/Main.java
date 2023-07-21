import java.util.Scanner;

public class Main {
    private static Scanner scanner = new Scanner(System.in);
    public static void main(String[] args) {
        Examen e1 = new Examen();
        e1.setDisciplina("PAW");
        e1.setTip(Tip.ORAL);
        Subiect[] subiects = new Subiect[3];
//        for (var s:
//             subiects) {
//            s = new Subiect();
//        }
        for (int i=0; i<subiects.length; i++)
            subiects[i] = new Subiect((20+i+1), "Intrebare " + (i+1));
        e1.setSubiecte(subiects);
        System.out.println("e1: " + e1.toString());

        // Indirectam tastatura catre fisierul intrare.txt

        Examen e2 = new Examen();
//        System.out.println("Introduceti disciplina:");
        e2.setDisciplina((scanner.nextLine()));
//        System.out.println("Introduceti tipul:");
        String tip = scanner.nextLine();
        if (tip.equalsIgnoreCase("ORAL")) {
            e2.setTip(Tip.ORAL);
        }
//        System.out.println("Introduceti nr de subiecte:");
        var nrSubiecte = Integer.parseInt(scanner.nextLine());
        var subiects2 = new Subiect[nrSubiecte];
        for (int i=0;i<subiects2.length;i++) {
//            System.out.println("Introduceti nr si subiectul");
            subiects2[i] = new Subiect(scanner.nextInt(), scanner.nextLine().trim());
        }
        e2.setSubiecte(subiects2);

        System.out.println("e2: " + e2.toString());


        System.out.println(e1 == e2 ? "subiectele sunt identice" : "subiectele sunt diferite");
        Examen e3 = new Examen();
        try {
            e3 = (Examen) e1.clone();
            System.out.println("e1: " + e1);
            System.out.println("e3: " + e3.toString());
            // modificare subiecte in e1
            Subiect[] subiects3 = new Subiect[2];
            for (int i=0; i<subiects3.length; i++)
                subiects3[i] = new Subiect((i+1), "Intrebare " + (i+1));
            e1.setSubiecte(subiects3);
            System.out.println("e1: " + e1);
            System.out.println("e3: " + e3);

        } catch (CloneNotSupportedException e) {
            throw new RuntimeException(e);
        }
    }
}
