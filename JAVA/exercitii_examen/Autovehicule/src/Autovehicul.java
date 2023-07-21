// În fișierul autovehicule.txt se găsesc informații privind autovehiculele unei firme de transport.
// Pe fiecare linie se află informații despre un autovehicul, astfel:
// număr înmatriculare (șir de caractere), data înmatriculării (șir de caractere în format dd.MM.yyyy)
// și număr de total de kilometri parcurși - kilometrajul masinii (valoare întreagă).
// Valorile sunt despărțite prin virgulă.

import java.time.LocalDate;

public class Autovehicul {
    private String numarInmatriculare;
    private LocalDate dataInmatricularii;
    private int kilometraj;

    public Autovehicul() {
        numarInmatriculare = "";
        dataInmatricularii = LocalDate.EPOCH;
        kilometraj = 0;
    }

    public Autovehicul(String numarInmatriculare, LocalDate dataInmatricularii, int kilometraj) {
        this.numarInmatriculare = numarInmatriculare;
        this.dataInmatricularii = dataInmatricularii;
        this.kilometraj = kilometraj;
    }

    public String getNumarInmatriculare() {
        return numarInmatriculare;
    }

    public void setNumarInmatriculare(String numarInmatriculare) {
        this.numarInmatriculare = numarInmatriculare;
    }

    public LocalDate getDataInmatricularii() {
        return dataInmatricularii;
    }

    public void setDataInmatricularii(LocalDate dataInmatricularii) {
        this.dataInmatricularii = dataInmatricularii;
    }

    public int getKilometraj() {
        return kilometraj;
    }

    public void setKilometraj(int kilometraj) {
        this.kilometraj = kilometraj;
    }

    @Override
    public String toString() {
        return "Autovehicul{" +
                "numarInmatriculare='" + numarInmatriculare + '\'' +
                ", dataInmatricularii=" + dataInmatricularii +
                ", kilometraj=" + kilometraj +
                '}';
    }
}
