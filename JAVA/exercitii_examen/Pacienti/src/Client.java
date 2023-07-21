import java.io.*;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;

public class Client {
    public static void main(String[] args) {
        final int PORT_NUMBER = 8983;

        try(
                Socket client = new Socket("localhost", PORT_NUMBER);
                DataOutputStream out = new DataOutputStream(client.getOutputStream());
                DataInputStream in = new DataInputStream(client.getInputStream());
        ) {
            System.out.println("Am deschis conexiunea cu server-ul");
            int codSectie = 10;
            out.writeInt(codSectie);

            System.out.println("Am trimis catre server-ul codul de sectie: " + codSectie);

            System.out.print("Numarul de locuri libere este: ");
            System.out.println(in.readInt());

            System.out.println("Am inchis conexiunea cu server-ul");

        }catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}
