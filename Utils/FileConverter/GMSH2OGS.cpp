/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.net/LICENSE.txt
 *
 * \file GMSH2OGS.cpp
 *
 *  Created on 2011-12-13 by Thomas Fischer
 */

// STL
#include <string>

// FileIO
#include "MeshIO/GMSHInterface.h"
#include "MeshIO/OGSMeshIO.h"

// MSH
#include "msh_lib.h" // for FEMRead
#include "msh_mesh.h"

Problem* aproblem = NULL;

int main (int argc, char* argv[])
{
	if (argc < 5)
	{
		std::cout << "Usage: " << argv[0] <<
		" --mesh-in meshfile --mesh-out meshfile" <<  std::endl;
		return -1;
	}

	// *** read mesh
	std::string tmp (argv[1]);
	if (tmp.find ("--mesh-in") == std::string::npos)
	{
		std::cout << "could not find option --mesh-in" << std::endl;
		return -1;
	}

	tmp = argv[2];
	std::string file_base_name (tmp);
	if (tmp.find (".msh") != std::string::npos)
		file_base_name = tmp.substr (0, tmp.size() - 4);

	std::vector<MeshLib::CFEMesh*> mesh_vec;
	FEMRead(file_base_name, mesh_vec);
	if (mesh_vec.empty())
	{
		std::cerr << "could not read mesh from file " << tmp << std::endl;
		return -1;
	}
	MeshLib::CFEMesh* mesh (mesh_vec[mesh_vec.size() - 1]);

	// *** create new mesh
	tmp = argv[3];
	if (tmp.find ("--mesh-out") == std::string::npos)
	{
		std::cout << "could not find option --mesh-out" << std::endl;
		return -1;
	}

	if (mesh->GetNodesNumber(false) == 0) {
		mesh->setNumberOfNodesFromNodesVectorSize();
	}

	tmp = argv[4];
	std::cout << "writing mesh to file " << tmp << " ... " << std::flush;
	FileIO::OGSMeshIO mesh_io;
	mesh_io.setMesh(mesh);
	mesh_io.writeToFile (tmp);
	std::cout << "ok" << std::endl;

	delete mesh;

}
