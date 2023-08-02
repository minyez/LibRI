// ===================
//  Author: Peize Lin
//  date: 2022.07.23
// ===================

#pragma once

#include "../global/Tensor.h"
#include "../ri/Label.h"

#include <mpi.h>
#include <vector>
#include <array>
#include <map>
#include <set>

namespace RI
{

template<typename TA, typename Tcell, std::size_t Ndim, typename Tdata>
//template<typename TA, typename Tcell, std::size_t Ndim>
class Parallel_LRI
{
public:
	using TC = std::array<Tcell,Ndim>;
	using TAC = std::pair<TA,TC>;
	using Tatom_pos = std::array<double,Ndim>;		// tmp

	//template<typename Tatom_pos>
	virtual void set_parallel(
		const MPI_Comm &mpi_comm,
		const std::map<TA,Tatom_pos> &atoms_pos,
		const std::array<Tatom_pos,Ndim> &latvec,
		const std::array<Tcell,Ndim> &period) =0;
	// atom_pos[iA][{cell}] = atoms_pos[iA] + \sum_x cell_x * latvec[cell_x]

	//template<typename Tdata>
	virtual std::map<TA,std::map<TAC,Tensor<Tdata>>> comm_tensors_map2(
		const Label::ab &label,
		const std::map<TA,std::map<TAC,Tensor<Tdata>>> &Ds) const =0;

	virtual const std::vector<TA >& get_list_Aa01() const =0;
	virtual const std::vector<TAC>& get_list_Aa2 () const =0;
	virtual const std::vector<TAC>& get_list_Ab01() const =0;
	virtual const std::vector<TAC>& get_list_Ab2 () const =0;
};

}