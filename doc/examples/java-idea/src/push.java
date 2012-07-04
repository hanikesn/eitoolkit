import de.uni_stuttgart.eitoolkit.DataMessage;
import de.uni_stuttgart.eitoolkit.Description;
import de.uni_stuttgart.eitoolkit.Sender;
import de.uni_stuttgart.eitoolkit.StringMap;

public class push {
    public static void main(String[] args) {
        Sender sender = new Sender(new Description("Kinect"), new StringMap());

        DataMessage msg = new DataMessage("Kinect 123");

        int cnt = 0;

        long start = System.currentTimeMillis();
        while(System.currentTimeMillis() < start + 5000) {
            msg.setString("x", "asd");
            msg.setDouble("y", 325.0);
            sender.sendMessage(msg);
            cnt++;
        }
        System.out.println(cnt);
    }
}
