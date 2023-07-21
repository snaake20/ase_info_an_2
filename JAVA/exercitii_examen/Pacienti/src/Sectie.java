public class Sectie {

    private int codSectie;

    private String denumire;

    private int numarLocuri;


    public Sectie() {
        codSectie = 0;
        denumire = "";
        numarLocuri = 0;
    }

    public Sectie(int codSectie, String denumire, int numarLocuri) {
        this.codSectie = codSectie;
        this.denumire = denumire;
        this.numarLocuri = numarLocuri;
    }

    public int getCodSectie() {
        return codSectie;
    }

    public void setCodSectie(int codSectie) {
        this.codSectie = codSectie;
    }

    public String getDenumire() {
        return denumire;
    }

    public void setDenumire(String denumire) {
        this.denumire = denumire;
    }

    public int getNumarLocuri() {
        return numarLocuri;
    }

    public void setNumarLocuri(int numarLocuri) {
        this.numarLocuri = numarLocuri;
    }

    @Override
    public String toString() {
        return "Sectie{" +
                "codSectie=" + codSectie +
                ", denumire='" + denumire + '\'' +
                ", numarLocuri=" + numarLocuri +
                '}';
    }
}
