package stocuri;

public class Produs implements Comparable<Produs> {

    private static final String DENUMIRE_IMPLICITA = "-";

    private final int cod;
    private final String denumire;

    public Produs(int cod, String denumire) {
        this.cod = cod;
        this.denumire = denumire;
    }

    public Produs(int cod) {
        this.cod = cod;
        this.denumire = DENUMIRE_IMPLICITA;
    }

    public int getCod() {
        return cod;
    }

    public String getDenumire() {
        return denumire;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Produs)) return false;

        Produs produs = (Produs) o;

        return getCod() == produs.getCod();
    }

    @Override
    public int hashCode() {
        return getCod();
    }


    @Override
    public String toString() {
        return "Produs{" +
                "cod=" + cod +
                ", denumire='" + denumire + '\'' +
                '}';
    }

    @Override
    public int compareTo(Produs o) {
        return Integer.compare(this.cod,o.getCod());
    }

    // TODO
}
