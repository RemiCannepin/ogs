/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.net/LICENSE.txt
 *
 * \file VtkBGImageSource.h
 *
 * Created on 2010-04-30 by Karsten Rink
 */

#ifndef VTKBGIMAGESOURCE_H
#define VTKBGIMAGESOURCE_H

// ** INCLUDES **
#include <vtkTextureMapToPlane.h>

#include "VtkAlgorithmProperties.h"

class vtkImageAlgorithm;

/**
 * \brief Uses an image source to create a plane in the 3D with the given
 * image texture mapped on it.
 */
class VtkBGImageSource : public vtkTextureMapToPlane, public VtkAlgorithmProperties
{
public:
	/// Create new objects with New() because of VTKs object reference counting.
	static VtkBGImageSource* New();

	vtkTypeRevisionMacro(VtkBGImageSource, vtkTextureMapToPlane);

	/// Sets the raster/image to be used as a texture map
	void SetRaster(vtkImageAlgorithm *img, double x0, double y0, double scalingFactor);

	virtual void SetUserProperty(QString name, QVariant value);

protected:
	VtkBGImageSource();
	~VtkBGImageSource();

private:

	std::pair<double, double> _origin;
	double _cellsize;
};

#endif // VTKBGIMAGESOURCE_H
