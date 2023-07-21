/*
* Cerințe:
*
* 1) Un enum TipTranzactie cu valorile INTRARE și IESIRE și o metodă semn care să dea semnul tranzacției (-1 sau 1).
*
* 2) O clasă imutabilă Produs (cod - intreg, denumire - string).
* Constructori care să primească toate valorile, respectiv doar codul.
* Două produse sunt considerate egale dacă au același cod.
*
* 3) O clasă Tranzacție (tip - tipul tranzacției, data - data tranzacției, codProdus și cantitate - intreg).
*
* 4) În clasa ProgramStocuri:
* - să se definească un câmp static stocuri de tip dicționar care să asocieze fiecărui produs lista de tranzacții aferente.
* - să se definească o metodă statică adaugaProdus(int cod, String denumire) care să adauge un produs nou în lista de stocuri.
*   Produsul NU trebuie să existe în stocuri.
* - să se definească o metodă statică adaugaTranzactie(TipTranzactie tip,LocalDate data,int codProdus,int cantitate) care să adauge o tranzacție nouă.
*   Produsul trebuie să existe în stocuri.
* - să se definească o metodă statică afisareStocuri() care să afișeze lista de produse cu: cod, denumire, stocCurent, data ultimei tranzacții
*
*
* */


import stocuri.*;

import java.time.LocalDate;
import java.util.*;

public class ProgramStocuri {
    private static Map<Produs, List<Tranzactie>> stocuri= new HashMap<>();
    private static void adaugaProdus(int cod, String denumire)
    {
        Produs nou = new Produs(cod,denumire);
        if(!stocuri.containsKey(nou)) {
            stocuri.put(nou, new ArrayList<>());
        }
    }

    private static void adaugaTranzactie(TipTranzactie tip, LocalDate data,
                                         int codProdus,int cantitate)
    {
        Produs nou = new Produs(codProdus);
        if(stocuri.containsKey(nou))
        {
            stocuri.get(nou).add(new Tranzactie(tip,data,codProdus,cantitate));
        }
    }

    private static void afisareStocuri()
    {
        var setTranzactii = stocuri.entrySet();
        for(var entry : setTranzactii)
        {
            int stocCurent = 0;
            var tranzactii = entry.getValue();
            for(var tranzactie : tranzactii)
            {
                stocCurent += tranzactie.getTip().semn()*tranzactie.getCantitate();
            }
            String ultimaTranzactie = ", data ultimei tranzactii ";
            if(!tranzactii.isEmpty())
            {
                ultimaTranzactie += Collections.max(tranzactii,
                        new Comparator<Tranzactie>() {
                            @Override
                            public int compare(Tranzactie o1, Tranzactie o2) {
                                return o1.getData().compareTo(o2.getData());
                            }
                        }).getData().toString();
            }
            System.out.println(entry.getKey().getCod() +
                    ", " + entry.getKey().getDenumire() +
                    ", " + stocCurent +
                    ultimaTranzactie);
        }
    }
    public static void main(String[] args) {
        adaugaProdus(2,"Lapte");
        adaugaProdus(3,"Paine");
        adaugaProdus(10,"Apa");
        adaugaTranzactie(TipTranzactie.INTRARE,LocalDate.of(2022,12,23),
                2,10);
        adaugaTranzactie(TipTranzactie.INTRARE,LocalDate.of(2023,1,24),
                2,20);
        adaugaTranzactie(TipTranzactie.IESIRE,LocalDate.of(2023,2,23),
                2,5);
        afisareStocuri();
    }
  // TODO
}
