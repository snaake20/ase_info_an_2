// În tabela REVIZII din baza de date sqlite examen.db se află informații privind reviziile făcute la autovehicule.
// Câmpurile tabelei sunt următoarele:
// numar_inmatriculare - text - cheie primară
// data_revizie - text - în format dd.MM.yyyy
// tip_revizie - text - cu valori ITP pentr inspecțiile tehnice obligatorii sau TPU pentru reviziile tehnice voluntare
// km - integer - reprezinta valoarea kilometrajului la momentul reviziei (int)
// cost_revizie - double

import java.time.LocalDate;

public class Revizie extends DetaliiRevizie {
    private String numarInmatriculare;

    public Revizie() {
        super();
        numarInmatriculare = "";
    }

    public Revizie(String numarInmatriculare, LocalDate dataRevizie, TipRevizie tipRevizie, int km, double costRevizie) {
        super(dataRevizie,tipRevizie,km,costRevizie);
        this.numarInmatriculare = numarInmatriculare;

    }

    public String getNumarInmatriculare() {
        return numarInmatriculare;
    }

    public void setNumarInmatriculare(String numarInmatriculare) {
        this.numarInmatriculare = numarInmatriculare;
    }

    @Override
    public String toString() {
        return "Revizie{" +
                "numarInmatriculare='" + numarInmatriculare + '\'' +
                ", dataRevizie=" + getDataRevizie() +
                ", tipRevizie=" + getTipRevizie().getTip() +
                ", km=" + getKm() +
                ", costRevizie=" + getCostRevizie() +
                '}';
    }
}
