/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.com)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.com/LICENSE.txt
 *
 *
 * \file Mesh.h
 *
 * Created on 2012-05-02 by Karsten Rink
 */

#ifndef MESH_H_
#define MESH_H_

#include <cstdlib>
#include <string>
#include <vector>

// MeshLib
#include "Node.h"

namespace MeshLib
{
	class Element;

/**
 * A basic mesh.
 */
class Mesh
{

public:
	/**
	 * This constructor for an instance of the class mesh takes the name of the mesh,
	 * a vector of objects of class Node and a vector of pointers to objects of class elements.
	 * @param name the name of the mesh (in the case you put your mesh to ProjectData the
	 * 	name should be unique, otherwise the name will be set to a unique name within the method
	 * 	ProjectData::addMesh())
	 * @param nodes the vector of instances of class Node (not pointers to instances of class Node)
	 * @param elements the vector elements where the nodes of the elements refer to the vector nodes
	 */
	Mesh(const std::string &name, const std::vector<Node> &nodes, const std::vector<Element*> &elements);

	/// Constructor using a mesh name and an array of nodes and elements
	Mesh(const std::string &name, const std::vector<Node*> &nodes, const std::vector<Element*> &elements);

	/// Copy constructor
	Mesh(const Mesh &mesh);

	/// Destructor
	virtual ~Mesh();

	/// Add a node to the mesh.
	void addNode(Node* node);

	/// Add an element to the mesh.
	void addElement(Element* elem);

	/// Get the minimum edge length over all elements of the mesh.
	double getMinEdgeLength() { return _edge_length[0]; };

	/// Get the maximum edge length over all elements of the mesh.
	double getMaxEdgeLength() { return _edge_length[1]; };

	/// Get the node with the given index.
	const Node* getNode(unsigned idx) const { return &_nodes[idx]; };

	/// Get the element with the given index.
	const Element* getElement(unsigned idx) const { return _elements[idx]; };

	/// Get the minimum edge length for the mesh
	double getMinEdgeLength() const { return _edge_length[0]; };

	/// Get the maximum edge length for the mesh
	double getMaxEdgeLength() const { return _edge_length[1]; };

	/// Get the number of elements
	size_t getNElements() const { return _elements.size(); };

	/// Get the number of nodes
	size_t getNNodes() const { return _nodes.size(); };

	/// Get name of the mesh.
	const std::string getName() const { return _name; };

	/// Get the nodes-vector for the mesh.
	std::vector<Node> const& getNodes() const { return _nodes; };

	/// Get the element-vector for the mesh.
	std::vector<Element*> const& getElements() const { return _elements; };

	/// Resets the IDs of all mesh-nodes to their position in the node vector
	void resetNodeIDs();

	/**
	 * Set the minimum and maximum length over the edges of the mesh.
	 * This should have been previously calcumlated using the Element::computeSqrEdgeLengthRange(min, max)
	 * function or by some other means.
	 */
	void setEdgeLengthRange(const double &min_length, const double &max_length);

	/// Changes the name of the mesh.
	void setName(const std::string &name) { this->_name = name; };

protected:
	/// Checks the coordinates of all mesh nodes and removes identical nodes. Elements are adapted accordingly.
	void makeNodesUnique();

	/// Fills in the neighbor-information for nodes (i.e. which element each node belongs to).
	void setElementInformationForNodes();

	/// Fills in the neighbor-information for elements.
	void setNeighborInformationForElements();

	double _edge_length[2];
	std::string _name;
	std::vector<Node> _nodes;
	std::vector<Element*> _elements;

}; /* class */

} /* namespace */

#endif /* MESH_H_ */

