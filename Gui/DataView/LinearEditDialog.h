/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.net/LICENSE.txt
 *
 * \file LinearEditDialog.h
 *
 * Created on 2012-04-17 by Karsten Rink
 */

#ifndef LINEAREDITDIALOG_H
#define LINEAREDITDIALOG_H

#include "ui_LinearEdit.h"
#include <QDialog>

#include "Polyline.h"

/**
 * \brief A dialog window for creating linear boundary conditions on polylines
 */
class LinearEditDialog : public QDialog, private Ui_LinearEdit
{
	Q_OBJECT

public:
	LinearEditDialog(const GeoLib::Polyline &line, const std::vector<std::size_t> &dis_nodes, const std::vector<double> &dis_values, QDialog* parent = 0);
	~LinearEditDialog(void);

private:
	void setupDialog(const std::vector<std::size_t> &dis_nodes, const std::vector<double> &dis_values);

	const GeoLib::Polyline _line;

private slots:
	void on_comboBox_currentIndexChanged(int index);

	/// Instructions if the OK-Button has been pressed.
	void accept();

	/// Instructions if the Cancel-Button has been pressed.
	void reject();

signals:
	void transmitDisValues(std::vector< std::pair<std::size_t,double> >);
};

#endif //LINEAREDITDIALOG_H
