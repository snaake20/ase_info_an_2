
import java.io.*;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

import static java.lang.Math.abs;

public class Trotineta implements Comparable {
    private String idTrotineta;
    private float distantaTotala;
    private float vitezaMedie;
    private float vitezaMaxima;

    public Trotineta() {
        idTrotineta = "";
        distantaTotala = 0;
        vitezaMedie = 0;
        vitezaMaxima = 0;
    }

    public Trotineta(String idTrotineta, float distantaTotala, float vitezaMedie, float vitezaMaxima) {
        this.idTrotineta = idTrotineta;
        this.distantaTotala = distantaTotala;
        this.vitezaMedie = vitezaMedie;
        this.vitezaMaxima = vitezaMaxima;
    }

    public float getVitezaMaxima() {
        return vitezaMaxima;
    }

    public void setVitezaMaxima(float vitezaMaxima) {
        this.vitezaMaxima = vitezaMaxima;
    }

    public float getVitezaMedie() {
        return vitezaMedie;
    }

    public void setVitezaMedie(float vitezaMedie) {
        this.vitezaMedie = vitezaMedie;
    }

    public float getDistantaTotala() {
        return distantaTotala;
    }

    public void setDistantaTotala(float distantaTotala) {
        this.distantaTotala = distantaTotala;
    }

    public String getIdTrotineta() {
        return idTrotineta;
    }

    public void setIdTrotineta(String idTrotineta) {
        this.idTrotineta = idTrotineta;
    }

    @Override
    public String toString() {
        return "Trotineta{" +
                "idTrotineta='" + idTrotineta + '\'' +
                ", distantaTotala=" + distantaTotala +
                ", vitezaMedie=" + vitezaMedie +
                ", vitezaMaxima=" + vitezaMaxima +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Trotineta trotineta)) return false;
        return abs(this.getDistantaTotala() - trotineta.getDistantaTotala()) < 10;
    }

    @Override
    public int compareTo(Object o) {
        Trotineta trotineta = (Trotineta) o;
        return this.equals(trotineta) ? 0 : (this.getDistantaTotala() - trotineta.getDistantaTotala() > 10 ? 1 : -1);
    }

    private static Map<String, Trotineta> parseFile(String fileName) {
        Map<String, Trotineta> map = new HashMap<>();
        try(var scanner = new Scanner(new BufferedReader(new FileReader(fileName)))) {
            while (scanner.hasNext()) {
                String line = scanner.nextLine();
                Scanner lineScanner = new Scanner(line);
                String id = lineScanner.next();
                float distantaTotala = lineScanner.nextFloat();
                float vitezaMedie = lineScanner.nextFloat();
                float vitezaMaxima = lineScanner.nextFloat();
                map.put(id, new Trotineta(id, distantaTotala, vitezaMedie, vitezaMaxima));
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        return map;
    }

    private static Map<String, Trotineta> parseFileLess(String fileName) {
        try(var file = (new BufferedReader(new FileReader(fileName)))) {
            return file.lines().map(l -> new Trotineta(l.split("\t")[0], Float.parseFloat(l.split("\t")[1]), Float.parseFloat(l.split("\t")[2]), Float.parseFloat(l.split("\t")[3]))).collect(Collectors.toMap(Trotineta::getIdTrotineta, Function.identity()));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static boolean saveToBinaryFile(String cale, List<Trotineta> trotinete) {
        if (trotinete == null || trotinete.isEmpty()) return false;
        try (var fisier = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(cale)))) {
            for (var trotineta:
                    trotinete) {
                fisier.writeUTF(trotineta.getIdTrotineta());
                fisier.writeFloat(trotineta.getDistantaTotala());
                fisier.writeFloat(trotineta.getVitezaMedie());
                fisier.writeFloat(trotineta.getVitezaMaxima());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    private static Map<String, Trotineta> afiseazaFisierBinar(String cale) {
        Map<String, Trotineta> res = new HashMap<>();
        try (var fisier = new DataInputStream(new BufferedInputStream(new FileInputStream(cale)))) {
            while (true) {
                var id = fisier.readUTF();
                res.put(id, new Trotineta(id, fisier.readFloat(), fisier.readFloat(), fisier.readFloat()));
            }
        } catch (EOFException e) {
            System.out.println("Fisierul a fost citit");
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
        return res;
    }

    public static void main(String[] args) {
        Map<String, Trotineta> trotinete = parseFileLess("./trotinete.txt");
        trotinete.forEach((key, value) -> {
            if (value.getVitezaMaxima() > 50) {
                System.out.println(value);
            }
        });
        Map<Float, List<Float>> aggregareTrotinete = trotinete.values().stream()
                .collect(Collectors.groupingBy(
                        Trotineta::getVitezaMedie,
                        Collectors.mapping(
                                Trotineta::getDistantaTotala,
                                Collectors.toList()
                        )
                ));
        for (var flash:
                aggregareTrotinete.entrySet()) {
            System.out.println("viteza medie: " + flash.getKey() + " -> " + flash.getValue().size() + " trotinete cu distanta totala: " + flash.getValue().stream().reduce(Float::sum).orElse(0.0f));
        }
        List<Trotineta> trotineteRapide = new ArrayList<>();
        for (var trotineta:
                trotinete.values()) {
            if (trotineta.getVitezaMedie() > 14 || trotineta.getVitezaMaxima() > 50) {
                trotineteRapide.add(trotineta);
            }
        }
        boolean didWrite = saveToBinaryFile("./trotineteRapide.dat", trotineteRapide);
        if (didWrite) {
            System.out.println("Salvare cu success");
        } else {
            System.out.println("Salvarea nu a avut success");
        }
        var trotineteFisier = afiseazaFisierBinar("./trotineteRapide.dat");
        for (var trota:
                trotineteFisier.entrySet()) {
            System.out.println(trota.getValue());
        }
    }
}
