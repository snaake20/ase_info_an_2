import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class DetaliiRevizie {
    private LocalDate dataRevizie;
    private TipRevizie tipRevizie;
    private int km;
    private double costRevizie;

    public DetaliiRevizie() {
        dataRevizie = LocalDate.EPOCH;
        tipRevizie = null;
        km = 0;
        costRevizie = 0.0;
    }

    public DetaliiRevizie(LocalDate dataRevizie, TipRevizie tipRevizie, int km, double costRevizie) {
        this.dataRevizie = dataRevizie;
        this.tipRevizie = tipRevizie;
        this.km = km;
        this.costRevizie = costRevizie;
    }

    public LocalDate getDataRevizie() {
        return dataRevizie;
    }

    public void setDataRevizie(LocalDate dataRevizie) {
        this.dataRevizie = dataRevizie;
    }

    public TipRevizie getTipRevizie() {
        return tipRevizie;
    }

    public void setTipRevizie(TipRevizie tipRevizie) {
        this.tipRevizie = tipRevizie;
    }

    public int getKm() {
        return km;
    }

    public void setKm(int km) {
        this.km = km;
    }

    public double getCostRevizie() {
        return costRevizie;
    }

    public void setCostRevizie(double costRevizie) {
        this.costRevizie = costRevizie;
    }

    public String returnDetalii() {
        return String.format("%s,%s,%d,%.1f\n", dataRevizie.format(DateTimeFormatter.ofPattern("dd.MM.yyyy")), getTipRevizie(), getKm(), getCostRevizie());
    }
}
