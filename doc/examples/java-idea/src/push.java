import de.uni_stuttgart.eitoolkit.*;

public class push {
    public static void main(String[] args) {
        Description desc = new Description("Java Dummy", "dummy");
        desc.addDataSeries("val", new DataSeriesInfo(Value.Type.DOUBLE, 0, ""));

        int cnt = 0;

        Sender sender = new Sender(desc, new StringMap());

        DataMessage msg = sender.createDataMessage();

        long start = System.currentTimeMillis();
        while(System.currentTimeMillis() < start + 5000) {
            msg.setDouble("val", 42.0);
            sender.sendMessage(msg);
            cnt++;
        }

        sender.delete();
        System.out.println(cnt);
    }
}
