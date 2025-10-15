// ===================
//  Author: Min-Ye Zhang
//  date: 2025.10.08
// ===================

#pragma once

#include <string>
#include <fstream>
#include "Tensor.h"

namespace RI
{

namespace Debug
{

std::string get_timestamp();

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
void report_virtual_pages(std::ostream &os);

template<typename TA, typename TAC, typename Tdata>
std::size_t count_map_total_size(const std::map<TA, std::map<TAC, Tensor<Tdata>>> &mm_tensor,
                                 std::ostream &os, bool print_ac_keys = false);

}

}

#include "Debug_Helpers.hpp"

