package tcp_ip;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Objects;

import static java.lang.System.exit;


public class GenericTCPClient {
    public static void main(String[] args) {
        // "localhost" este numele asociat adresei de IP 127.0.0.1
        if (args.length != 2) {
            System.err.println("Utilizare: java GenericTCPClient <port> <ip address>");
            exit(-1);
        }

        int port = Integer.parseInt(args[0]);
        try {
            var ip = InetAddress.getByName(args[1]);
            System.out.println("Mă conectez la server-ul "+ip+":"+port);
            var client = new Socket(ip,port);
            OutputStream outToServer = client.getOutputStream();
//            var out = new DataOutputStream(outToServer);
            ObjectOutputStream out = new ObjectOutputStream(outToServer);
            InputStream inFromServer = client.getInputStream();
//            var in = new DataInputStream(inFromServer);
            ObjectInputStream in = new ObjectInputStream(inFromServer);

            System.out.println("Pentru ieşire, tastaţi EXIT");
            var reader = new BufferedReader(new InputStreamReader(System.in));
            while(true)
            {
                // 1. Pregătire cerere
                String mesaj = reader.readLine();
                if(mesaj.equalsIgnoreCase("exit")) {
                    in.close();
                    out.close();
                    client.close();
                    exit(0);
                }
                else // 2. Trimitere cerere către server
                {
//                    out.writeUTF(mesaj);
//                    System.out.println("scriere obiect");
                    out.writeObject(mesaj);
                }
                // 3. Primire răspuns de la server
//                var raspunsServer = in.readUTF();
                String raspunsServer = (String) in.readObject();
                // 4. Procesare răspuns de la server
                System.out.println(raspunsServer);
            }
        } catch (IOException e) {
            System.out.println("Conexiune la server eşuată.");
            //throw new RuntimeException(e);
//        } catch (ClassNotFoundException e) {
//            throw new RuntimeException(e);
        }
        catch(Exception e)
        {
            throw new RuntimeException(e);
        }

    }
}
