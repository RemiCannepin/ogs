/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.net/LICENSE.txt
 *
 * \file VtkPickCallback.h
 *
 * Created on 2010-06-21 by Lars Bilke
 *
 */

#ifndef VTKPICKCALLBACK_H
#define VTKPICKCALLBACK_H

// ** INCLUDES **
#include <QObject>
#include <vtkCommand.h>

class vtkProp3D;

/**
 * VtkPickCallback is a vtkCommand that implements functionality when
 * picking a vtk object through a vtkCellPicker.
 */
class VtkPickCallback : public QObject, public vtkCommand
{
	Q_OBJECT

public:
	static VtkPickCallback* New();

	void Execute(vtkObject* caller, unsigned long eventId, void* callData);

protected:
	VtkPickCallback();

signals:
	/// Is emitted when an vtkActor was picked.
	void actorPicked (vtkProp3D* actor);
};

#endif // VTKPICKCALLBACK_H
