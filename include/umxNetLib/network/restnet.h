#ifndef RESTNET_H
#define RESTNET_H

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>
using Poco::Util::OptionSet;

#include "network.h"
#if 1 //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h vvv
#include "umxNetLib/umxNetGlobal.h"
#else
#include "iNetworkManager.h"
#endif //EF-45(unklee88)-57 : netglobal.h includes iNetworkmanager.h ^^^

#include "restnetrun.h"
#include "rawnet.h"

#if 1 //EF-45(unklee88)-62 : made Namespace UMXNetwork vvv
using namespace UMXNetwork;
#endif //EF-45(unklee88)-62 : made Namespace UMXNetwork ^^^

class RestNet : public Poco::Util::ServerApplication, public Network
{
public:
    RestNet();
    ~RestNet();

    void setINetworkManager(INetworkManager *iNetworkManager);
    INetworkManager* getINetworkManager();

protected:
    void initialize(Application& self);
    void uninitialize();
    void defineOptions(OptionSet& options);
    void handleHelp(const std::string& name, const std::string& value);
    int main(const std::vector<std::string>& args);

public:

private:
    bool _helpRequested;

    INetworkManager *_iNetworkManager;

    RestNetRun* _restNetRun;
    RawNet* _rawNet;
    Poco::Thread _restNetThread;
    Poco::Thread _rawNetThread;
};

#endif // RESTNET_H

