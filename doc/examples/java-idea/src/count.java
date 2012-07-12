import de.uni_stuttgart.eitoolkit.DataListener;
import de.uni_stuttgart.eitoolkit.DataMessage;
import de.uni_stuttgart.eitoolkit.Receiver;
import de.uni_stuttgart.eitoolkit.StringMap;

import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;

public class count {
    public static void main(String[] args) {
        final AtomicInteger cnt = new AtomicInteger();

        DataListener listener = new DataListener(){
            @Override
            public void onMessage(DataMessage msg) {
                String str = msg.getSender();
                String val1 = msg.getString("val1");
                double val2 = msg.getDouble("val2");
                double val3 = msg.getDouble("val3");
                cnt.incrementAndGet();
            }
        };
        Receiver receiver = new Receiver(new StringMap());
        receiver.addDataListener(listener);

        Scanner sc = new Scanner(System.in);
        sc.nextLine();
        receiver.delete();
        System.out.println(cnt.get());
    }
}
