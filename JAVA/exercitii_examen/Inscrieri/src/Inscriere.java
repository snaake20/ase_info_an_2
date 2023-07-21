public class Inscriere {
    private long cnpCandidat;
    private String numeCandidat;
    private  double notaBacalaureat;
    private int codSpecializare;

    public Inscriere(long cnpCandidat, String numeCandidat, double notaBacalaureat, int codSpecializare) {
        this.cnpCandidat = cnpCandidat;
        this.numeCandidat = numeCandidat;
        this.notaBacalaureat = notaBacalaureat;
        this.codSpecializare = codSpecializare;
    }

    public long getCnpCandidat() {
        return cnpCandidat;
    }

    public void setCnpCandidat(long cnpCandidat) {
        this.cnpCandidat = cnpCandidat;
    }

    public String getNumeCandidat() {
        return numeCandidat;
    }

    public void setNumeCandidat(String numeCandidat) {
        this.numeCandidat = numeCandidat;
    }

    public double getNotaBacalaureat() {
        return notaBacalaureat;
    }

    public void setNotaBacalaureat(double notaBacalaureat) {
        this.notaBacalaureat = notaBacalaureat;
    }

    public int getCodSpecializare() {
        return codSpecializare;
    }

    public void setCodSpecializare(int codSpecializare) {
        this.codSpecializare = codSpecializare;
    }

    @Override
    public String toString() {
        return "Inscriere{" +
                "cnpCandidat=" + cnpCandidat +
                ", numeCandidat='" + numeCandidat + '\'' +
                ", notaBacalaureat=" + notaBacalaureat +
                ", codSpecializare=" + codSpecializare +
                '}';
    }
}
