import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class Client {
    public static void main(String[] args) {
        try (
                var client = new Socket("localhost", 8983);
                var in = new DataInputStream(client.getInputStream());
                var out = new DataOutputStream(client.getOutputStream())
        ) {

            System.out.println("Conexiunea s-a realizat cu success");

            String nume = "Tiroliana";

            System.out.println("Numele aventurei trimis server-ului: " + nume);

            out.writeUTF(nume);

            System.out.println("Aventura cu numele: " + nume + " are " + in.readInt() + " locuri libere");

        } catch (IOException e) {
            System.out.println("Probleme la conexiunea client-ului");
        }
    }
}
