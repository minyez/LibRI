// ===================
//  Author: Min-Ye Zhang
//  date: 2025.10.08
// ===================

#pragma once

#include "Debug_Helpers.h"

#include <chrono>
#include <sstream>

#if defined(__linux__)
#include <malloc.h>
#endif

namespace RI
{

namespace Debug
{

std::string get_timestamp()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    auto milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    std::stringstream ss;
    ss << "[" <<std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S")
       << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << "]";
    return ss.str();
}

void FileLogger::open(int myid)
{
    std::string fn = "debug_" + this->_prefix + "_myid_" + std::to_string(myid) + ".txt";
    this->_wf.open(fn.c_str());
}

void FileLogger::close()
{
    if (this->_wf.is_open())
    {
        this->_wf.close();
    }
}

void report_virtual_pages(std::ostream &os)
{
#ifndef __linux__
    os << "report_virtual_pages only available on Linux, skip" << std::endl;
#else
    struct mallinfo2 mi = mallinfo2();
    std::ifstream ifs("/proc/self/status");
    std::string line;
    std::string vmrss, vmdata;
    while (std::getline(ifs, line)) {
        if (line.rfind("VmRSS:", 0) == 0) vmrss = line;
        if (line.rfind("VmData:", 0) == 0) vmdata = line;
    }
    os << vmrss << std::endl << vmdata << std::endl
       << "Heap arena: " << mi.arena / (1024.0*1024)
       << " MB, Free: " << mi.fordblks / (1024.0*1024)
       << " MB, Mmap space: " << mi.hblkhd / (1024.0*1024)
       << " MB" << std::endl;
#endif
}

}

}


