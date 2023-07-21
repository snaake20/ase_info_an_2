package tcp_ip;

import java.io.*;
import java.net.Socket;


public class ServerThread extends Thread {
    private Socket client = null;
    private static int nrClient = 0;

    // TODO

    public ServerThread(Socket client) {
        super("Client_"+(++nrClient));
        this.client = client;
    }

    @Override
    public void run()
    {
        try {
            System.out.println("Conexiune acceptată de la client "
                    + client.getRemoteSocketAddress()+"; "+this.getName());
            InputStream inFromClient = client.getInputStream();
//            var in = new DataInputStream(inFromClient);
            var in = new ObjectInputStream(inFromClient);
            OutputStream outToClient = client.getOutputStream();
//            var out = new DataOutputStream(outToClient);
            var out = new ObjectOutputStream(outToClient);
            while(true) {
                // 1. Primesc cerere de la client
//                var mesaj = in.readUTF();
                String mesaj = (String) in.readObject();

                // 2. Prelucrez cerere de la client
                sleep(500); // Simulare timp prelucrare
                System.out.println(mesaj + " ("+this.getName()+")");

                // 3. Construiesc răspuns
                var raspuns = "Echo Server: "+mesaj;

                // 4. Trimit răspuns
//                out.writeUTF(raspuns);
                out.writeObject(raspuns);
            }
        }
        catch(EOFException eof)
        {
            System.out.println("S-a închis conexiunea cu "+this.getName());
        }
        catch(IOException | ClassNotFoundException e) {

        } catch (InterruptedException e) {
            throw new RuntimeException(e);
//        } catch (ClassNotFoundException e) {
//            throw new RuntimeException(e);
        }

    }

}

