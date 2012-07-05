#include <EIToolkit.h>
#include <cmath>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

typedef boost::chrono::high_resolution_clock Clock;

int main()
{
    std::string deviceName = "discrete sender";

    EI::Description desc(deviceName, "dummy");
    std::string name = "slow";
    desc.addDataSeries(name, EI::DataSeriesInfo(EI::Value::STRING, EI::DataSeriesInfo::NONE, ""));

    EI::Sender sender(desc, EI::StringMap());

    EI::DataMessage p(deviceName);

    Clock::time_point start;

    while(true)
    {
        p.setString(name, "pong");
        sender.sendMessage(p);
        boost::this_thread::sleep(boost::posix_time::milliseconds(5050));
    }
}
