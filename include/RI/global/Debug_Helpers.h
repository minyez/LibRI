// ===================
//  Author: Min-Ye Zhang
//  date: 2025.10.08
// ===================

#pragma once

#include <string>
#include <fstream>

namespace RI
{

namespace Debug
{

extern std::string get_timestamp();

class FileLogger
{
private:
    std::string _prefix;
    std::ofstream _wf;

public:
    FileLogger(const char *prefix): _prefix(prefix) {};
    void open(int myid);
    void close();
    std::ofstream& wf() { return this->_wf; };
    ~FileLogger() { close(); };
};

/**
 * \brief Report virtual pages usage for memory check.
 */
extern void report_virtual_pages(std::ostream &os);

}

}

#include "Debug_Helpers.hpp"

