/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.net/LICENSE.txt
 *
 * \file VtkVisImageItem.h
 *
 * Created on 2011-09-29 by Karsten Rink
 */

#ifndef VTKVISIMAGEITEM_H
#define VTKVISIMAGEITEM_H

// ** INCLUDES **
#include "VtkVisPipelineItem.h"

class vtkAlgorithm;
class vtkImageChangeInformation;
class vtkPointSet;
class vtkProp3D;
class vtkRenderer;

class vtkOsgActor;

class VtkAlgorithmProperties;
class VtkCompositeFilter;

/**
 * \brief An item in the VtkVisPipeline containing an image to be visualized.
 *
 * Any vtkImageAlgorithm object is represented by a VtkVisImageItem to be assigned a mapper,
 * an actor and its visualization properties.
 * \sa VtkVisPipelineItem
 */
class VtkVisImageItem : public VtkVisPipelineItem
{
public:
	/// @brief Constructor for a source/filter object.
	VtkVisImageItem(vtkAlgorithm* algorithm,
	                TreeItem* parentItem,
	                const QList<QVariant> data = QList<QVariant>());

	/// @brief Constructor for composite filter
	VtkVisImageItem(VtkCompositeFilter* compositeFilter, TreeItem* parentItem,
	                const QList<QVariant> data = QList<QVariant>());

	~VtkVisImageItem();

	/// @brief Initializes vtkMapper and vtkActor necessary for visualization of
	/// the item and sets the item's properties.
	void Initialize(vtkRenderer* renderer);

	void setTranslation(double x, double y, double z) const;

	vtkAlgorithm* transformFilter() const;

protected:
	/// Selects the appropriate VTK-Writer object and writes the object to a file with the given name.
	virtual int callVTKWriter(vtkAlgorithm* algorithm, const std::string &filename) const;
	void setVtkProperties(VtkAlgorithmProperties* vtkProps);

private:
	vtkImageChangeInformation* _transformFilter;
};

#endif // VTKVISIMAGEITEM_H

