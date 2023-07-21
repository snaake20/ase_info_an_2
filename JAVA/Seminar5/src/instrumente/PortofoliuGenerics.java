package instrumente;

import java.util.HashMap;
import java.util.Map;

public class PortofoliuGenerics<T> {

    /*
     * 6. O clasa  PortofoliuGenerics<T> ce implementeaza o colectie generica
     * de intrumente financiare. Are un atribut privat portofoliu ce
     * stocheaza colectia de obiecte <T> si constructori cu si fara parametri.
     *
     * Contine urmatoarele metode publice:
     *  getProtofoliu(),
     *  setPortofoliu(),
     *  adaugaIntrument(),
     *  getIntrument().
     * */

    private Map<String, T> portofoliu;

    public PortofoliuGenerics() {
        this.portofoliu = new HashMap<>();
    }

    public PortofoliuGenerics(Map<String, T> portofoliu) {
        this.portofoliu = portofoliu;
    }

    public Map<String, T> getPortofoliu() {
        return portofoliu;
    }

    public void setPortofoliu(Map<String, T> portofoliu) {
        this.portofoliu = portofoliu;
    }

    public void adaugaInstrument(String key, T instrument) {
        this.portofoliu.put(key, instrument);
    }

    public T getInstrument(String key){
        return this.portofoliu.get(key);
    }

    // done!
}
