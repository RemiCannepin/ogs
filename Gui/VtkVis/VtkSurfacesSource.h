/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.net/LICENSE.txt
 *
 * \file VtkSurfacesSource.h
 *
 * Created on 2010-02-03 by Lars Bilke
 */

#ifndef VTKSURFACESSOURCE_H
#define VTKSURFACESSOURCE_H

// ** INCLUDES **
#include "VtkAlgorithmProperties.h"
#include <vtkPolyDataAlgorithm.h>

#include "Surface.h"

/**
 * \brief VTK source object for the visualisation of surfaces.
 * Technically, surfaces are displayed as triangulated polydata objects.
 */
class VtkSurfacesSource : public vtkPolyDataAlgorithm, public VtkAlgorithmProperties
{
public:
	/// Create new objects with New() because of VTKs object reference counting.
	static VtkSurfacesSource* New();

	vtkTypeRevisionMacro(VtkSurfacesSource,vtkPolyDataAlgorithm);

	/// Sets the surfaces vector
	void setSurfaces(const std::vector<GeoLib::Surface*>* surfaces) { _surfaces = surfaces; }

	/// Prints its data on a stream.
	void PrintSelf(ostream& os, vtkIndent indent);

	/**
	 * \brief Generates random colors for each surface.
	 */
	//ogsUserPropertyMacro(ColorBySurface,bool);

	virtual void SetUserProperty(QString name, QVariant value);

protected:
	VtkSurfacesSource();
	~VtkSurfacesSource() {}

	/// Computes the polygonal data object.
	int RequestData(vtkInformation* request,
	                vtkInformationVector** inputVector,
	                vtkInformationVector* outputVector);

	int RequestInformation(vtkInformation* request,
	                       vtkInformationVector** inputVector,
	                       vtkInformationVector* outputVector);

	/// The surfaces to visualize
	const std::vector<GeoLib::Surface*>* _surfaces;

private:
};

#endif // VTKSURFACESSOURCE_H
