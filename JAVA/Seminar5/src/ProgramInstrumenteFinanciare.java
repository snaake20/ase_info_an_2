import instrumente.Actiune;
import instrumente.Instrument;
import instrumente.PortofoliuGenerics;
import instrumente.TipOperatiune;

import java.io.*;
import java.time.LocalDate;
import java.util.*;

import javax.management.RuntimeErrorException;

public class ProgramInstrumenteFinanciare {

    // seminar 5 ---------------------------------------------------------------

    private static void salvarePortofoliu(String caleFisier
    , PortofoliuGenerics<Instrument> portofoliu) throws IOException {
        if(new File(caleFisier).getParentFile()!=null)
        {
            new File(caleFisier).getParentFile().mkdirs();
        }
        try (var fisier = new FileWriter(caleFisier)) { // sau try(var fisier = new PrintWriter(new BufferedWriter(new FileWriter(caleFisier))))
            for(var entry : portofoliu.getPortofoliu().entrySet())
            {
                fisier.write(entry.getValue().toString());
            }
        }
    }

    // todo: de implementat csv scriere si citire -> urmatorul seminar
    // private static PortofoliuGenerics incarcarePortofoliu(String caleFisier)

    // seminar 5 ---------------------------------------------------------------

    public static void main(String[] args) {
        /*
         * Sa se creeze un program pentru popularea colectiei de
         * intrumente financiare cu obiecte de tip Intrument si cu obiecte de tip
         * Actiune.
         * Sa de afiseze continutul portofoliului, valoarea acestuia si
         * data primei operatiuni financiare efectuate pentru fiecare intrument
         * financiar continut in portofoliu.
         */

        PortofoliuGenerics<Instrument> portofoliu = new PortofoliuGenerics<>();

        Instrument i1 = new Instrument();
        i1.setSymbol("TLV");
        i1.adaugaOperatiune(new Instrument.Operatiune(TipOperatiune.CUMPARARE, LocalDate.of(2000, 10, 21), 20, 30));
        portofoliu.adaugaInstrument(i1.getSymbol(), i1);

        Instrument i2 = new Instrument();

        Instrument.Operatiune o1 = new Instrument.Operatiune(TipOperatiune.CUMPARARE, LocalDate.of(2000, 10, 22), 20,
                30);
        Instrument.Operatiune o2 = new Instrument.Operatiune(TipOperatiune.CUMPARARE, LocalDate.of(2000, 10, 23), 20,
                30);
        Instrument.Operatiune o3 = new Instrument.Operatiune(TipOperatiune.CUMPARARE, LocalDate.of(2000, 10, 24), 20,
                30);

        List<Instrument.Operatiune> o = new ArrayList<>();

        Collections.addAll(o, o1, o2, o3);

        i2.setOperatiuni(o);

        i2.setSymbol("RND");

        portofoliu.adaugaInstrument(i2.getSymbol(), i2);

        Actiune a1 = new Actiune();
        a1.setSymbol("BCR");

        List<Instrument.Operatiune> operatiuni2 = new ArrayList<>();

        Collections.addAll(operatiuni2, o2, o3);

        a1.setOperatiuni(operatiuni2);
        a1.setProcentDividend(3.15);

        portofoliu.adaugaInstrument(a1.getSymbol(), a1);

        double val = 0;

        for (var instr : portofoliu.getPortofoliu().entrySet()) {
            val += instr.getValue().valoare();
            System.out.println(instr.getKey() + ", data primei tranzactiei: ");
            try {
                LocalDate primaData = Collections.min(instr.getValue().getOperatiuni(),
                        (o11, o21) -> o11.getData().compareTo(o21.getData())).getData();
                System.out.println(primaData.toString());
            } catch (Exception ignored) {
                System.out.println("Instrumentul nu are tranzactii!");
            }
        }
        System.out.println("Valoarea portofoliu: " + val);

        // seminar 4 ends here

        try {
            salvarePortofoliu("./JAVA/Seminar5/Portofolii/portofoliu.txt", portofoliu);
        } catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeErrorException(null, "Eroare la salvarea portofoliului!");
        }
    }
}
