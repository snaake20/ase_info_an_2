import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class Client {
    private static final int PORT = 8983;

    public static void main(String[] args) {
        try(
                Socket client = new Socket("localhost", PORT);
                DataInputStream in = new DataInputStream(client.getInputStream());
                DataOutputStream out = new DataOutputStream(client.getOutputStream());
                DataInputStream t = new DataInputStream(System.in);
        ) {
            System.out.println("Am deschis conexiunea");

            String msg = "B100LCT";

            out.writeUTF(msg);

            System.out.println("Am trimis " + msg);

            System.out.println("Am primit " + in.readInt());

            System.out.println("Conexiunea s-a inchis");

        } catch(IOException e) {
            System.out.println("sth went wrong while sending/receiving data");
        }
    }


}
