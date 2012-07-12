import de.uni_stuttgart.eitoolkit.*;

public class push {
    public static void main(String[] args) {
        Description desc = new Description("Java Dummy", "dummy");
        desc.addDataSeries("val1", new DataSeriesInfo(Value.Type.STRING, 0, ""));
        desc.addDataSeries("val2", new DataSeriesInfo(Value.Type.DOUBLE, DataSeriesInfo.Property.INTERPOLATABLE, ""));
        desc.addDataSeries("val3", new DataSeriesInfo(Value.Type.DOUBLE, DataSeriesInfo.Property.INTERPOLATABLE | DataSeriesInfo.Property.HAS_MINMAX, "", 0.0, 1.0));

        int cnt = 0;

        Sender sender = new Sender(desc, new StringMap());

        DataMessage msg = sender.createDataMessage();

        long start = System.currentTimeMillis();
        while(System.currentTimeMillis() < start + 5000) {
            msg.setString("val1", "hello");
            msg.setDouble("val2", 42.0);
            msg.setDouble("val3", 0.5);
            sender.sendMessage(msg);
            cnt++;
        }

        sender.delete();
        System.out.println(cnt);
    }
}
