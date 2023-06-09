#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("p2p_network_sim");

int main(int argc, char* argv[])
{
    // Declare command line parameters
    uint32_t simNodes;
    double simTime;

    CommandLine cmd;
    
    cmd.AddValue("simNodes", "Number of nodes in the network", simNodes);
    cmd.AddValue("simTime", "Simulation time in seconds", simTime);

    cmd.Parse(argc, argv);

    // Create nodes and install Internet stack
    NodeContainer nodes;
    nodes.Create(simNodes);

    PointToPointHelper p2p;
    InternetStackHelper stack;
    stack.Install(nodes);

    // Set up point-to-point links
    p2p.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("10ms"));

    NetDeviceContainer devices;
    devices = p2p.Install(nodes);

    // Assign IP addresses
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces;
    interfaces = address.Assign(devices);

    // Run simulation
    Simulator::Stop(Seconds(simTime));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}



