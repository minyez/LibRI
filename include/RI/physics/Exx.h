// ===================
//  Author: Peize Lin
//  date: 2022.06.02
// ===================

#pragma once

#include "Exx_Post_2D.h"
#include "../global/Global_Func-2.h"
#include "../global/Tensor.h"
#include "../ri/LRI.h"

#include <mpi.h>
#include <array>
#include <map>

namespace RI
{

template<typename TA, typename Tcell, std::size_t Ndim, typename Tdata>
class Exx
{
public:
	using TC = std::array<Tcell,Ndim>;
	using TAC = std::pair<TA,TC>;
	using Tdata_real = Global_Func::To_Real_t<Tdata>;
	constexpr static std::size_t Npos = Ndim;		// tmp
	using Tatom_pos = std::array<double,Npos>;		// tmp

	void set_parallel(
		const MPI_Comm &mpi_comm,
		const std::map<TA,Tatom_pos> &atoms_pos,
		const std::array<Tatom_pos,Ndim> &latvec,
		const std::array<Tcell,Ndim> &period);

	void set_Cs(
		const std::map<TA, std::map<TAC, Tensor<Tdata>>> &Cs,
		const Tdata_real &threshold_C,
		const std::string &save_name_suffix="");
	void set_Vs(
		const std::map<TA, std::map<TAC, Tensor<Tdata>>> &Vs,
		const Tdata_real &threshold_V,
		const std::string &save_name_suffix="");
	void set_Ds(
		const std::map<TA, std::map<TAC, Tensor<Tdata>>> &Ds,
		const Tdata_real &threshold_D,
		const std::string &save_name_suffix="");
	void set_dCs(
		const std::array<std::map<TA, std::map<TAC, Tensor<Tdata>>>,Npos> &dCs,
		const Tdata_real &threshold_dC,
		const std::string &save_name_suffix="");
	void set_dVs(
		const std::array<std::map<TA, std::map<TAC, Tensor<Tdata>>>,Npos> &dVs,
		const Tdata_real &threshold_dV,
		const std::string &save_name_suffix="");
	void set_csm_threshold(
		const Tdata_real &threshold) { this->lri.csm.set_threshold(threshold); }

	void cal_Hs(
		const std::array<std::string,3> &save_names_suffix={"","",""});		// "Cs","Vs","Ds"
	void cal_force(
		const std::array<std::string,5> &save_names_suffix={"","","","",""});	// "Cs","Vs","Ds","dCs","dVs"
	void cal_stress(
		const std::array<std::string,5> &save_names_suffix={"","","","",""});	// "Cs","Vs","Ds","dCs","dVs"

	std::map<TA, std::map<TAC, Tensor<Tdata>>> Hs;
	Tdata energy = 0;
	std::array<std::map<TA,Tdata>,Ndim> force;
	Tensor<Tdata> stress;

	Exx_Post_2D<TA,TC,Tdata> post_2D;

public:
	LRI<TA,Tcell,Ndim,Tdata> lri;

	struct Flag_Finish
	{
		bool stru=false;
		bool C=false;
		bool V=false;
		bool D=false;
		bool dC=false;
		bool dV=false;
	};
	Flag_Finish flag_finish;

	MPI_Comm mpi_comm;
	std::map<TA,Tatom_pos> atoms_pos;
	std::array<Tatom_pos,Ndim> latvec;
	std::array<Tcell,Ndim> period;	
};

}

#include "Exx.hpp"