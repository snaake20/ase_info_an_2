package instrumente;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
public class Instrument implements Evaluabil {

    /*
     * 1. O clasa instrumente.Instrument, care sa implementeze interfata Evaluabil si care contine
     * urmatoarele atribute private:
     * symbol - String, o colectie de obiecte de tip Operatiune financiara
     * si o clasă internă statică Operatiune si !publica!.
     *
     * Clasa instrumente.Instrument va avea cel putin:
     *  - constructor cu parametri si fara parametri
     *  - metode de citire pentru toate atributele
     *  - posibilitatea de a adăuga operatiuni la un intrumentul financiar.
     */

    private String symbol;
    private List<Operatiune> operatiuni;

    public static class Operatiune {
        /*
        * Atribute: tip - TipOperatiune (vezi fisier), data - LocalDate, preț - număr cu zecimale, cantitate - întreg
        */
        private TipOperatiune tip;
        private LocalDate data;
        private double pret;
        private int cantitate;

        public Operatiune(TipOperatiune tip, LocalDate data, double pret, int cantitate) {
            this.tip = tip;
            this.data = data;
            this.pret = pret;
            this.cantitate = cantitate;
        }

        public TipOperatiune getTip() {
            return tip;
        }

        public void setTip(TipOperatiune tip) {
            this.tip = tip;
        }

        public LocalDate getData() {
            return data;
        }

        public void setData(LocalDate data) {
            this.data = data;
        }

        public double getPret() {
            return pret;
        }

        public void setPret(double pret) {
            this.pret = pret;
        }

        public int getCantitate() {
            return cantitate;
        }

        public void setCantitate(int cantitate) {
            this.cantitate = cantitate;
        }

        
        // seminar 5 --------------------------------------------------

        @Override
        public String toString() {
            return "Operatiune{" +
                    "tip=" + tip +
                    ", data=" + data +
                    ", pret=" + pret +
                    ", cantitate=" + cantitate +
                    '}';
        }

    }

    public Instrument(String symbol, List<Operatiune> operatiuni) {
        this.symbol = symbol;
        this.operatiuni = operatiuni;
    }
    public Instrument() {
        this.symbol = "";
        this.operatiuni = new ArrayList<>();
    }


    public String getSymbol() {
        return symbol;
    }

    public void setSymbol(String symbol) {
        this.symbol = symbol;
    }

    public List<Operatiune> getOperatiuni() {
        return operatiuni;
    }

    public void setOperatiuni(List<Operatiune> operatiuni) {
        this.operatiuni = operatiuni;
    }

    public void adaugaOperatiune(Operatiune o) {
        this.operatiuni.add(o);
    }

    // overrides
    @Override
    public double valoare() {
        return operatiuni.stream().mapToDouble(o -> o.pret * o.cantitate * o.tip.pozitie()).sum();
    }

    @Override
    public String toString() {
        return "Instrument{" +
                "simbol='" + symbol + '\'' +
                ", operatiuni=" + operatiuni +
                '}';

    }

    // done!
}
