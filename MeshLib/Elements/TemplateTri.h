/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 *
 * \file TemplateTri.h
 *
 * Created on 2012-05-02 by Karsten Rink
 */

#ifndef TEMPLATETRI_H_
#define TEMPLATETRI_H_

#include "Edge.h"
#include "Node.h"
#include "Face.h"

#include "MathTools.h"


namespace MeshLib {

/**
 * This class represents a 2d triangle element. The following sketch shows the node and edge numbering.
 * @anchor TriNodeAndEdgeNumbering
 * @code
 *
 *          2
 *          o
 *         / \
 *        /   \
 *      2/     \1
 *      /       \
 *     /         \
 *    0-----------1
 *          0
 *
 * @endcode
 */
template <unsigned ORDER, unsigned NNODES>
class TemplateTri : public Face
{
public:
	/// Constructor with an array of mesh nodes.
	TemplateTri(Node* nodes[NNODES], unsigned value = 0);

	/// Copy constructor
	TemplateTri(const TemplateTri<ORDER, NNODES> &tri);

	/// Destructor
	virtual ~TemplateTri();

	/// Get the number of edges for this element.
	unsigned getNEdges() const { return 3; };

	/// Get the number of neighbors for this element.
	unsigned getNNeighbors() const { return 3; };

	/// Get the number of nodes for this element.
	virtual unsigned getNNodes(unsigned order = 1) const
	{
		return order == ORDER ? NNODES : 3;
	}

	/**
	 * Method returns the type of the element. In this case TRIANGLE will be returned.
	 * @return MshElemType::TRIANGLE
	 */
	virtual MshElemType::type getType() const { return MshElemType::TRIANGLE; }

	/// Returns true if these two indices form an edge and false otherwise
	bool isEdge(unsigned idx1, unsigned idx2) const;

	/**
	 * Method clone is inherited from class Element. It makes a deep copy of the TemplateTri instance.
	 * @return an exact copy of the object
	 */
	virtual Element* clone() const
	{
		return new TemplateTri<ORDER, NNODES>(*this);
	}


	/**
	 * This method should be called after at least two nodes of the triangle
	 * element are collapsed. As a consequence of the node collapsing an edge
	 * of the triangle will be collapsed. If one of the edges is collapsed we
	 * obtain an edge. In this case the method will create the appropriate
	 * object of class Edge.
	 * @return an Edge object or NULL
	 */
	virtual Element* reviseElement() const;

protected:
	/// Calculates the area of the triangle by returning half of the area of the corresponding parallelogram.
	double computeVolume()
	{
		return MathLib::calcTriangleArea(_nodes[0]->getCoords(), _nodes[1]->getCoords(), _nodes[2]->getCoords());
	}

protected:
	/// Return a specific edge node.
	inline Node* getEdgeNode(unsigned edge_id, unsigned node_id) const
	{
		return _nodes[_edge_nodes[edge_id][node_id]];
	}

	/// Returns the ID of a face given an array of nodes.
	unsigned identifyFace(Node* nodes[3]) const;

	static const unsigned _edge_nodes[3][2];
}; /* class */

template <unsigned ORDER, unsigned NNODES>
const unsigned TemplateTri<ORDER, NNODES>::_edge_nodes[3][2] = {
		{0, 1}, // Edge 0
		{1, 2}, // Edge 1
		{0, 2}  // Edge 2
	};

} /* namespace */

#include "TemplateTri.hpp"

#endif /* TEMPLATETRI_H_ */

