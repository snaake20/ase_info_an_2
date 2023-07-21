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


public class Cont {
    private long sold;
    boolean inOperare;

    public Cont() {
        this.sold = 0;
        this.inOperare = false;
    }

    public Cont(long sold) {
        this.sold = sold;
        this.inOperare = false;
    }

    public synchronized void depunere(long suma, String mesaj) throws InterruptedException {
        while (inOperare) {
            System.out.println(mesaj + " contul este in operare asteptam");
            try {
                wait();
            } catch (InterruptedException e) {
                throw new InterruptedException();
            }
        }
        inOperare = true;
        this.sold += suma;
        inOperare = false;
        notifyAll();
    }

    public synchronized long retrage(long suma, String mesaj) throws InterruptedException {

        while (inOperare) {
            System.out.println(mesaj + " contul este in operare asteptam");
            try {
                wait();
            } catch (InterruptedException e) {
                throw new InterruptedException();
            }
        }
        inOperare = true;
        if (sold < suma) {
            System.out.println(mesaj +  " Fonduri insuficiente! Soldul este: " + sold);
            inOperare = false;
            return -1;
        }
        this.sold -= suma;
        inOperare = false;
        System.out.println(mesaj + " a retras cu success suma: " + suma + " sold ramas: " + sold);
        return this.sold;
    }

    public long getSold() {
        return this.sold;
    }

}
