public class SectieSmechera extends Sectie {
    private int numarLocuriOcupate;

    public SectieSmechera() {
        super();
        numarLocuriOcupate = 0;
    }

    public SectieSmechera(int codSectie, String denumire, int numarLocuri, int numarLocuriOcupate) {
        super(codSectie, denumire, numarLocuri);
        this.numarLocuriOcupate = numarLocuriOcupate;
    }

    public int getNumarLocuriOcupate() {
        return numarLocuriOcupate;
    }

    public void setNumarLocuriOcupate(int numarLocuriOcupate) {
        this.numarLocuriOcupate = numarLocuriOcupate;
    }
}
