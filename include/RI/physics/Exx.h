// ===================
//  Author: Peize Lin
//  date: 2022.06.02
// ===================

#pragma once

#include "../ri/LRI.h"
#include "../global/Tensor.h"
#include "../global/Global_Func-2.h"

#include <mpi.h>
#include <array>
#include <map>

template<typename TA, typename Tcell, size_t Ndim, typename Tdata>
class Exx
{
public:
	using TAC = std::pair<TA,std::array<Tcell,Ndim>>;
	using Tdata_real = Global_Func::To_Real_t<Tdata>;
	using TatomR = std::array<double,Ndim>;		// tmp

	Exx(const MPI_Comm &mpi_comm):lri(mpi_comm){}

	void set_stru(
		const std::map<TA,TatomR> &atomsR,
		const std::array<TatomR,Ndim> &latvec,
		const std::array<Tcell,Ndim> &period);
	
	void set_Cs(
		const std::map<TA, std::map<TAC, Tensor<Tdata>>> &Cs,
		const Tdata_real &threshold_C);
	void set_Vs(
		const std::map<TA, std::map<TAC, Tensor<Tdata>>> &Vs,
		const Tdata_real &threshold_V);
	void set_Ds(
		const std::map<TA, std::map<TAC, Tensor<Tdata>>> &Ds,
		const Tdata_real &threshold_D);

	void cal();

	std::map<TA, std::map<TAC, Tensor<Tdata>>> Hs;

public:
	LRI<TA,Tcell,Ndim,Tdata> lri;

	struct Flag_Finish
	{
		bool stru=false;
		bool C=false;
		bool V=false;
		bool D=false;
	};
	Flag_Finish flag_finish;
};

#include "Exx.hpp"