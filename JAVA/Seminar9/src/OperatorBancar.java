import java.util.Random;

/** Sa se implementeze clasa Cont (double sold, boolean inOperare) pentru a oferi operatiuni de:
 * - depunere(long suma, String mesaj)
 * - retragere(long suma, String mesaj)
 * - getSold()
 *
 * Se se defineasca clasa OperatorBancar, clasa derivata din clasa Thread care sa permita
 * operatiuni pe un obiect de timp cont. Clasa OperatorBancar are urmatoarele atribute:
 *     private Cont cont;
 *     private String nume;
 *     private int timpPregatire;
 *     private long suma;
 *
 * Sa se scrie un program care utilizeaza mai multi operatori bancari ce realizeza operatii
 * in regim concurential pe o resursa comuna reprezentata de un Cont bancar.
 * Programul primeste soldul contului si numarul de operatori ca parametri in linia de comanda.
 *
 */


public class OperatorBancar extends Thread {
    private Cont cont;
    private String nume;
    private int timpPregatire;
    private long suma;

    public OperatorBancar(Cont cont, String nume, int timpPregatire, long suma) {
        this.cont = cont;
        this.nume = nume;
        this.timpPregatire = timpPregatire;
        this.suma = suma;
    }



    @Override
    public void run() {
        while(cont.getSold() >= this.suma) {
            try {
                sleep(timpPregatire);
                cont.retrage(suma, nume);
            } catch (InterruptedException e ) {
//                throw new InterruptedException();
            }
        }
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Numar incorect de parametri");
            System.exit(-1);
        }
        int nrOperatori = Integer.parseInt(args[0]);
        long soldInitial = Long.parseLong(args[1]);
        System.out.println(nrOperatori + " " + soldInitial);
        var cont = new Cont(soldInitial);
        Thread[] operatori = new OperatorBancar[nrOperatori];

        for (int i = 0; i < nrOperatori; i++) {
            operatori[i] = new OperatorBancar(cont ,"Operator " + (i+1), (i+1) * 500, ((i+1)*10)+50);
            operatori[i].start();
        }
        for (var operator:
             operatori) {
            try {
                operator.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        System.out.println("Soldul final este: " + cont.getSold());
    }

}
