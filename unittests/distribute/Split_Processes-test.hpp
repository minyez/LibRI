// ===================
//  Author: Peize Lin
//  date: 2022.07.11
// ===================

#pragma once

#include "distribute/Split_Processes.h"

#include <fstream>

namespace Split_Processes_Test
{
	void test_split_all()
	{
		MPI_Init(NULL,NULL);

		const std::vector<int> Ns = {4,5,6};
		//const std::vector<int> Ns = {4,5,30};
		const std::vector<std::tuple<MPI_Comm,int,int>> comm_color_sizes = Split_Processes::split_all(MPI_COMM_WORLD, Ns);

		std::ofstream ofs("out."+std::to_string(MPI_Wrapper::mpi_get_rank(MPI_COMM_WORLD)), std::ofstream::app);
		for(const auto &comm_color_size : comm_color_sizes)
			ofs<<MPI_Wrapper::mpi_get_rank(std::get<0>(comm_color_size))<<"\t"
			<<MPI_Wrapper::mpi_get_size(std::get<0>(comm_color_size))<<"\t|\t"
			<<std::get<1>(comm_color_size)<<"\t"
			<<std::get<2>(comm_color_size)<<std::endl;

		MPI_Finalize();	
	}
	/*
	mpirun -n 7
		rank 0
			0	7	|	0	1
			0	4	|	0	2
			0	2	|	0	2
			0	1	|	0	2
		rank 1
			1	7	|	0	1
			1	4	|	0	2
			1	2	|	0	2
			0	1	|	1	2
		rank 2
			2	7	|	0	1
			2	4	|	0	2
			0	2	|	1	2
			0	1	|	0	2
		rank 3
			3	7	|	0	1
			3	4	|	0	2
			1	2	|	1	2
			0	1	|	1	2
		rank 4
			4	7	|	0	1
			0	3	|	1	2
			0	2	|	0	2
			0	1	|	0	2
		rank 5
			5	7	|	0	1
			1	3	|	1	2
			1	2	|	0	2
			0	1	|	1	2
		rank 6
			6	7	|	0	1
			2	3	|	1	2
			0	1	|	1	2
			0	1	|	0	1
	*/
}