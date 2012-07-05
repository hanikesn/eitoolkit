#include <EIToolkit.h>
#include <cmath>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

typedef boost::chrono::high_resolution_clock Clock;

int main()
{
    std::string name = "sinus sender";

    EI::Description desc(name, "dummy");
    std::string val = "regular";
    desc.addDataSeries(val, EI::DataSeriesInfo(EI::Value::DOUBLE, EI::DataSeriesInfo::INTERPOLATABLE | EI::DataSeriesInfo::HAS_MINMAX, "", -1.0, 1.0));

    EI::Sender sender(desc, EI::StringMap());

    EI::DataMessage p(name);

    Clock::time_point start;

    while(true)
    {
        p.setDouble(val, sin(boost::chrono::duration<double>(start - Clock::now()).count()));
        sender.sendMessage(p);
        boost::this_thread::sleep(boost::posix_time::milliseconds(250));
    }
}
