package instrumente;

public class Actiune extends Instrument {
    /*

     * 5. O clasa Actiune, derivata din Instrument si care implementeaza
     interfata instrumente.Evaluabil.
      Are in plus un atribut privat double - procentDividend.
     * */

    private double procentDividend;

    public Actiune() {
        super();
        this.procentDividend = 0;
    }

    public void setProcentDividend(double procentDividend) {
        this.procentDividend = procentDividend;
    }

    @Override
    public String toString() {
        return "Actiune{" + super.toString() +
                "procentDividend=" + procentDividend +
                '}';
    }

    @Override
    public double valoare() {
       return super.valoare() * (1 + procentDividend/100);
    }

    // done!
}
