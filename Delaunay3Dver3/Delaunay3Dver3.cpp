//*********************************************************
//Title		:Delaunay3Dver3
//Author	:Tanabe Yuta
//Date		:2019/01/26
//Copyright	:(C)2019 TanabeYuta
//*********************************************************

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>


#include "Delaunay.h"
#include "Parameter.h"


//**********節点の取り込み**********
bool importnode(std::vector<Node*> &_node, std::string _fname, int _type) {
	std::ifstream fin(_fname);
	if (!fin) {
		std::cout << "Node File Open Error : " << _fname << "\n";
		return false;
	}

	std::string tmp;
	while (getline(fin, tmp)) {
		std::istringstream ssi(tmp);
		std::string tmpx[3];
		ssi >> tmpx[0] >> tmpx[1] >> tmpx[2];
		_node.push_back(new Node(stod(tmpx[0]), stod(tmpx[1]), stod(tmpx[2]), 0));
	}
	fin.close();
	return true;
}


//**********
int main() {
	clock_t ts = clock();

	std::vector<Node*> nlist;
	std::vector<Element*> elist;

	std::cout << "**********Delaunay trianguration**********\n";
	if (!importnode(nlist, MODELNAME + (std::string)"/node.dat", 0)) {
		return -1;
	}

	if (!importnode(nlist, MODELNAME + (std::string)"/copynode.dat", 0)) {
		//return -1;
	}

	Delaunay3D::MakeSupertetrahedran(nlist, elist);
	Delaunay3D::MakeRoughMesh(nlist, elist);
	
	clock_t te = clock();
	std::cout << "\ntime cost:\t" << (double)(te - ts) / CLOCKS_PER_SEC << "sec.\n";
	std::cout << "node:     \t" << nlist.size() << "\n";
	std::cout << "element:  \t" << elist.size() << "\n";

	return 0;
}