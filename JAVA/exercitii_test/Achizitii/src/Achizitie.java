import java.io.*;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Achizitie implements Comparable {

    static class Data {
        private int an;
        private int luna;
        private int zi;

        public Data() {
            an = 0;
            luna = 0;
            zi = 0;
        }

        public Data(int an, int luna, int zi) {
            this.an = an;
            this.luna = luna;
            this.zi = zi;
        }

        public int getAn() {
            return an;
        }

        public void setAn(int an) {
            this.an = an;
        }

        public int getLuna() {
            return luna;
        }

        public void setLuna(int luna) {
            this.luna = luna;
        }

        public int getZi() {
            return zi;
        }

        public void setZi(int zi) {
            this.zi = zi;
        }

        @Override
        public String toString() {
            return "Data{" +
                    "an=" + an +
                    ", luna=" + luna +
                    ", zi=" + zi +
                    '}';
        }
    }
    private String cod;
    private Data dataAchizitie;
    private int cantitate;
    private float pretUnitar;


    public Achizitie() {
        cod = "";
        dataAchizitie = new Data();
        cantitate = 0;
        pretUnitar = 0;
    }

    public Achizitie(String cod, Data dataAchizitie, int cantitate, float pretUnitar) {
        this.cod = cod;
        this.dataAchizitie = dataAchizitie;
        this.cantitate = cantitate;
        this.pretUnitar = pretUnitar;
    }

    public String getCod() {
        return cod;
    }

    public void setCod(String cod) {
        this.cod = cod;
    }

    public Data getDataAchizitie() {
        return dataAchizitie;
    }

    public void setDataAchizitie(Data dataAchizitie) {
        this.dataAchizitie = dataAchizitie;
    }
    public int getCantitate() {
        return cantitate;
    }

    public void setCantitate(int cantitate) {
        this.cantitate = cantitate;
    }

    public float getPretUnitar() {
        return pretUnitar;
    }

    public void setPretUnitar(float pretUnitar) {
        this.pretUnitar = pretUnitar;
    }

    @Override
    public String toString() {
        return "Achizitie{" +
                "cod='" + cod + '\'' +
                ", dataAchizitie=" + dataAchizitie.toString() +
                ", pretUnitar=" + pretUnitar +
                '}';
    }

    public float valoare() {
        return pretUnitar * cantitate;
    }

    @Override
    public int compareTo(Object o) {
        var achizitie = (Achizitie) o;
        return this.valoare() == achizitie.valoare() ? 0 : (this.valoare() > achizitie.valoare() ? 1 : -1);
    }

    public static List<Achizitie> parseFile(String cale) {
        List<Achizitie> res = new ArrayList<>();
        try (var file = new BufferedReader(new FileReader(cale))) {

            res = file.lines().filter(l -> !Objects.equals(l, "")).map(l -> {
                return new Achizitie(l.split(",")[0], new Data(Integer.parseInt(l.split(",")[1]), Integer.parseInt(l.split(",")[2]), Integer.parseInt(l.split(",")[3])), Integer.parseInt(l.split(",")[4]), Float.parseFloat(l.split(",")[5]));
            }).toList();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return res;
    }

    public static boolean writeBinary(String cale, List<Achizitie> achizitii) {
        if (achizitii == null || achizitii.isEmpty()) return false;
        try (var file = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(cale)))) {
            for (var ach:
                 achizitii) {
                file.writeUTF(ach.getCod());
                file.writeInt(ach.getDataAchizitie().getAn());
                file.writeInt(ach.getDataAchizitie().getLuna());
                file.writeInt(ach.getDataAchizitie().getZi());
                file.writeInt(ach.getCantitate());
                file.writeFloat(ach.getPretUnitar());
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return true;
    }

    public static List<Achizitie> readBinary(String cale) {
        List<Achizitie> res = new ArrayList<>();
        try(var file = new DataInputStream(new BufferedInputStream(new FileInputStream(cale)))) {
            while (true) {
                res.add(new Achizitie(file.readUTF(), new Data(file.readInt(), file.readInt(), file.readInt()), file.readInt(), file.readFloat()));
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (EOFException e ) {
            System.out.println("Fisier citit");
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return res;
    }

    public static void main(String[] args) {
        var listaAchizitii = parseFile("./achizitii.txt");
        for (var achizitie:
             listaAchizitii) {
            if (achizitie.getDataAchizitie().getZi() < 15 && achizitie.getCantitate() > 100) {
                System.out.println(achizitie);
            }
        }
        Map<String, List<Float>> achizitiiAgregate = listaAchizitii.stream().collect(Collectors.groupingBy(Achizitie::getCod, Collectors.mapping(Achizitie::valoare, Collectors.toList())));
        for (var ach:
             achizitiiAgregate.entrySet()) {
            System.out.println("Produs " + ach.getKey() + " -> " + ach.getValue().size() + " achizitii, valoare totala " + ach.getValue().stream().reduce(Float::sum).orElse(0.0f) + " Lei");
        }
        List<Achizitie> frecvente = new ArrayList<>();
        achizitiiAgregate.forEach((key, value) -> {
            if (value.size() > 3)
                frecvente.addAll(listaAchizitii.stream().filter(achizitie -> Objects.equals(achizitie.getCod(), key)).toList());
        });
        var didWrite = writeBinary("./produseFrecvente.dat", frecvente);
        if (didWrite) {
            System.out.println("Salvare cu success");
        } else {
            System.out.println("Nu a fost salvat");
        }
        var produseFrecvente = readBinary("./produseFrecvente.dat");
        for (var pr:
                produseFrecvente) {
            System.out.println(pr);
        }
    }
}
