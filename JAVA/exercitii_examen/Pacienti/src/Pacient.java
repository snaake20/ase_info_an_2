public class Pacient {
    private long cnp;
    private String numePacient;
    private int varsta;
    private int codSectie;

    public Pacient() {
        cnp = 0;
        numePacient = "";
        varsta = 0;
        codSectie = 0;
    }

    public Pacient(long cnp, String numePacient, int varsta, int codSectie) {
        this.cnp = cnp;
        this.numePacient = numePacient;
        this.varsta = varsta;
        this.codSectie = codSectie;
    }

    public long getCnp() {
        return cnp;
    }

    public void setCnp(long cnp) {
        this.cnp = cnp;
    }

    public String getNumePacient() {
        return numePacient;
    }

    public void setNumePacient(String numePacient) {
        this.numePacient = numePacient;
    }

    public int getVarsta() {
        return varsta;
    }

    public void setVarsta(int varsta) {
        this.varsta = varsta;
    }

    public int getCodSectie() {
        return codSectie;
    }

    public void setCodSectie(int codSectie) {
        this.codSectie = codSectie;
    }

    @Override
    public String toString() {
        return "Pacient{" +
                "cnp=" + cnp +
                ", numePacient='" + numePacient + '\'' +
                ", varsta=" + varsta +
                ", codSectie=" + codSectie +
                '}';
    }
}
