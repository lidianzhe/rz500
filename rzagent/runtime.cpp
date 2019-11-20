#include "runtime.h"
#include "Poco/Logger.h"
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
using Poco::DirectoryIterator;
using Poco::Path;
using Poco::File;
using Poco::Logger;
using Poco::FileChannel;
using Poco::AutoPtr;
using Poco::PatternFormatter;
using Poco::FormattingChannel;

Runtime dzrun;
Runtime::Runtime()
{
    initLog();
}

Poco::Logger &Runtime::initLog(std::string name)
{
    if(Logger::has(name)!=nullptr)
        return Logger::get(name);
    std::cout << "initLog ("<<name<<") in Runtime" <<endl;
    AutoPtr<FileChannel> pChannel(new FileChannel);
    pChannel->setProperty("path", "/home/root/rzagent.log");
    pChannel->setProperty("rotation", "10M");
    pChannel->setProperty("archive", "timestamp");
    AutoPtr<PatternFormatter> pPF(new PatternFormatter);
    pPF->setProperty("pattern", "%L%Y-%m-%d %H:%M:%S %Z %s: [%p] %t"); // local time
    AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pChannel));
    Logger& m_logger = Logger::create(name,pFC);
    //m_logger.setChannel(pFC);
    //Logger::root().setChannel(pFC);
    //Logger::get("dzrun").setChannel(pFC);
    poco_information_f1(m_logger,"--create Logger %s in runtime's initLog().",name);
    return m_logger;
}
