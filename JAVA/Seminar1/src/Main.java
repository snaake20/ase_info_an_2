import java.util.Scanner;

public class Main {
    static void interschimb(int a, int b) {
        int aux = 0;
        aux = a;
        a = b;
        b = aux;
    }

    static void interschimbInteger(Integer a, Integer b) {
//        Integer aux = 0;
        Integer aux = Integer.valueOf(0);
        aux = a;
        a = b;
        b = a;
    }

    static void interschimbMasiv(int[] vector) {
        int aux = 0;
        aux = vector[0];
        vector[0] = vector[1];
        vector[1] = aux;
    }

    static void interschimbIntregulMeu(MyInteger a, MyInteger b) {
        int aux = 0;
        aux = a.getInteger();
        a.setInteger(b.getInteger());
        b.setInteger(aux);
    }
    public static void main(String[] args) {
        System.out.println("Hello world!");

        if (args.length != 2) {
            System.out.println("Numar invalid de argumente. Lanseaza Main <arg1 <arg2>");
            System.exit(-1);
        }
//        for (int i=0; i<args.length; i++)
//            System.out.print(args[i] + " ");

        int a = Integer.parseInt(args[0]);
        int b = Integer.parseInt(args[1]);
        System.out.format("a=%d, b=%d\n", a, b);
        interschimb(a, b);
        System.out.format("a=%d, b=%d\n", a, b);

        Integer x = a;
        Integer y = b;

        interschimbInteger(x, y);
        System.out.format("x=%d, y=%d\n", x, y);

        int[] vector = {1, 5};
        System.out.format("vector[0]=%d, vector[1]=%d\n", vector[0], vector[1]);
        interschimbMasiv(vector);
        System.out.format("vector[0]=%d, vector[1]=%d\n", vector[0], vector[1]);

        var z = new MyInteger(100);
        var w = new MyInteger(300);
        System.out.format("z=%d, w=%d\n", z.getInteger(), w.getInteger());
        interschimbIntregulMeu(z, w);
        System.out.format("z=%d, w=%d\n", z.getInteger(), w.getInteger());

        // preluare atribute de la tastatura si tiparire alor la consola
        System.out.print("Introduceti numele si varsta studentului: ");
//        Scanner scaner = new Scanner(System.in);
        var scanner = new Scanner(System.in);
        scanner.useDelimiter("[\\r\\n\\t\\f\\v ,]+"); // /[\r\n\t\f\v ,]{1,}/g
        String nume = scanner.next();
        var varsta = scanner.nextInt();
//        int varsta = Integer.parseInt(scaner.next());
        System.out.format("Nume=%s, varsta=%d", nume, varsta);
    }
}
