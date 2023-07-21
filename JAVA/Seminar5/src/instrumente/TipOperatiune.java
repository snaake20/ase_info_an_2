package instrumente;

public enum TipOperatiune {
   /*
     * 4. Un enum TipOperatiune cu valorile CUMPARARE, VANZARE și o metodă pozitie() care să dea directia operatiunii
     * financiare (-1 VANZARE, 1 CUMPARARE).
    */

    CUMPARARE(1),
    VANZARE(-1);

    private final int directie;

    TipOperatiune(int directie) {
        this.directie = directie;
    }

    public int pozitie()
    {
        return this.directie;
    }

    // done!
}
