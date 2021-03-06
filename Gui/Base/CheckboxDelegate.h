/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.net/LICENSE.txt
 *
 * \file CheckboxDelegate.h
 *
 * Created on 2010-08-19 by Lars Bilke
 */

#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QItemDelegate>

class QWidget;
class QRect;

/**
 * \brief CheckboxDelegate modifies a model view to display boolean values as checkboxes.
 *
 * Important: the column on which this delegate is set (QAbstractItemView::setItemDelegateForColumn())
 * must not have the flags Qt::ItemIsEditable or Qt::ItemIsUserCheckable set in the model.
 **/
class CheckboxDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	/// \brief Constructor
	CheckboxDelegate (QObject* parent = 0);

	/// \brief Paints a checkbox. This overrides the default painting of a combo box.
	void paint(QPainter* painter, const QStyleOptionViewItem& option,
	           const QModelIndex& index) const;

	/// \brief Handles the click events and sets the model data.
	bool editorEvent(QEvent* event, QAbstractItemModel* model,
	                 const QStyleOptionViewItem &option, const QModelIndex &index);

	QSize sizeHint (const QStyleOptionViewItem & option, const QModelIndex & index) const;

private:
	QRect checkboxRect(const QStyleOptionViewItem& viewItemStyleOptions) const;
};

#endif // CHECKBOXDELEGATE_H
