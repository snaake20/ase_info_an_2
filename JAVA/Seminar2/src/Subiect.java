public class Subiect {
    private int numar;
    private String enunt;

    public Subiect() {

    }
    public Subiect(int numar, String enunt) {
        this.numar = numar;
        this.enunt = enunt;
    }

    public int getNumar() {
        return numar;
    }

    public void setNumar(int numar) {
        this.numar = numar;
    }

    public String getEnunt() {
        return enunt;
    }


    public void setEnunt(String enunt) {
        this.enunt = enunt;
    }

    @Override
    public String toString() {
        return "Subiect{" +
                "numar=" + numar +
                ", enunt='" + enunt + '\'' +
                '}';
    }
}
