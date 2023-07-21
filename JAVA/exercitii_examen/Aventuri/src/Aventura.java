public class Aventura {
    private int codAventura;
    private String denumire;
    private double tarif;
    private int locuriDisponibile;

    public Aventura() {
        codAventura = 0;
        denumire = "";
        tarif = 0;
        locuriDisponibile = 0;
    }

    public Aventura(int codAventura, String denumire, double tarif, int locuriDisponibile) {
        this.codAventura = codAventura;
        this.denumire = denumire;
        this.tarif = tarif;
        this.locuriDisponibile = locuriDisponibile;
    }

    public int getCodAventura() {
        return codAventura;
    }

    public void setCodAventura(int codAventura) {
        this.codAventura = codAventura;
    }

    public String getDenumire() {
        return denumire;
    }

    public void setDenumire(String denumire) {
        this.denumire = denumire;
    }

    public double getTarif() {
        return tarif;
    }

    public void setTarif(double tarif) {
        this.tarif = tarif;
    }

    public int getLocuriDisponibile() {
        return locuriDisponibile;
    }

    public void setLocuriDisponibile(int locuriDisponibile) {
        this.locuriDisponibile = locuriDisponibile;
    }

    @Override
    public String toString() {
        return "Aventura{" +
                "codAventura=" + codAventura +
                ", denumire='" + denumire + '\'' +
                ", tarif=" + tarif +
                ", locuriDisponibile=" + locuriDisponibile +
                '}';
    }
}
