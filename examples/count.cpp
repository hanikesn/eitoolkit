#include <EIToolkit.h>

#include <iostream>
#include <algorithm>

volatile int count = 0;

class ExampleListener : public EI::DataListener
{
public:
    void onMessage(EI::DataMessage const& p) {
       std::string test =  p.getString("msg");
       count++;
    }
};

int main()
{
    std::cout << "count" << std::endl;

    EI::StringMap options;

    EI::Receiver receiver(options);

    ExampleListener listener;
    receiver.addDataListener(listener);

    std::cin.get();

    std::cerr << count << "\n";
}
