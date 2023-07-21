public class Rezervare {
    private String idRezervare;
    private int codAventura;
    private int nrLocuriRezervate;

    public Rezervare() {
        idRezervare = "";
        codAventura = 0;
        nrLocuriRezervate = 0;
    }

    public Rezervare(String idRezervare, int codAventura, int nrLocuriRezervate) {
        this.idRezervare = idRezervare;
        this.codAventura = codAventura;
        this.nrLocuriRezervate = nrLocuriRezervate;
    }

    public String getIdRezervare() {
        return idRezervare;
    }

    public void setIdRezervare(String idRezervare) {
        this.idRezervare = idRezervare;
    }

    public int getCodAventura() {
        return codAventura;
    }

    public void setCodAventura(int codAventura) {
        this.codAventura = codAventura;
    }

    public int getNrLocuriRezervate() {
        return nrLocuriRezervate;
    }

    public void setNrLocuriRezervate(int nrLocuriRezervate) {
        this.nrLocuriRezervate = nrLocuriRezervate;
    }

    @Override
    public String toString() {
        return "Rezervare{" +
                "idRezervare='" + idRezervare + '\'' +
                ", codAventura=" + codAventura +
                ", nrLocuriRezervate=" + nrLocuriRezervate +
                '}';
    }
}
