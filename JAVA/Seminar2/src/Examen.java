import java.util.Arrays;

public class Examen implements Cloneable {
    private String disciplina;
    private Tip tip;
    private Subiect[] subiecte;

    public Examen() {
        this.disciplina = null;
        this.tip = Tip.NECUNOSCUT;
        this.subiecte = null;
    }

    public String getDisciplina() {
        return disciplina;
    }

    public void setDisciplina(String disciplina) {
        this.disciplina = disciplina;
    }

    public Tip getTip() {
        return tip;
    }

    public void setTip(Tip tip) {
        this.tip = tip;
    }

    public Subiect[] getSubiecte() {
        return subiecte;
    }

    public void setSubiecte(Subiect[] subiecte) {
        this.subiecte = subiecte;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    @Override
    public String toString() {
        return "Examen{" +
                "disciplina='" + disciplina + '\'' +
                ", tip=" + tip +
                ", subiecte=" + Arrays.toString(subiecte) +
                '}';
    }
    // USING INTELLIJ SI BIFEZI TOT
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Examen examen)) return false;

        if (!getDisciplina().equals(examen.getDisciplina())) return false;
        if (getTip() != examen.getTip()) return false;
        // Probably incorrect - comparing Object[] arrays with Arrays.equals
        return Arrays.equals(getSubiecte(), examen.getSubiecte());
    }

    @Override
    public int hashCode() {
        int result = getDisciplina().hashCode();
        result = 31 * result + getTip().hashCode();
        result = 31 * result + Arrays.hashCode(getSubiecte());
        return result;
    }
}
