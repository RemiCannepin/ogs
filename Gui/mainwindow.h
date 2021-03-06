/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.net/LICENSE.txt
 *
 * \file mainwindow.h
 *
 * Created on 2009-11-04 by Lars Bilke
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FileFinder.h"
#include "ProjectData.h"
#include "ImportFileTypes.h"
#include "ui_mainwindow.h"

class GEOModels;
class MshModel;
class ElementTreeModel;
class StationTreeModel;
class ProcessModel;
class VtkVisPipeline;
class VisPrefsDialog;

class QSignalMapper;

#ifdef OGS_USE_VRPN
class TrackingSettingsWidget;
#endif // OGS_USE_VRPN

/**
 * Main program window for the graphical user interface of OpenGeoSys.
 */
class MainWindow : public QMainWindow, public Ui_MainWindowClass
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();

	void ShowWindow();
	void HideWindow();

protected:
	void closeEvent( QCloseEvent* event );

protected slots:
	void showGeoDockWidget( bool show );
	void showStationDockWidget( bool show );
	void showMshDockWidget( bool show );
	void showConditionDockWidget( bool show );
	void showVisDockWidget( bool show );

	/// Function calls for opening files.
	void open(int i = 0);
	/// Function calls for saving files.
	void save();
	/// Function calls for generating GMSH files from the GUI
	void callGMSH(std::vector<std::string> & selectedGeometries,
	              unsigned param1,
	              double   param2,
	              double   param3,
	              double   param4,
	              bool     delete_geo_file);
	/// Function calls for GMS export.
	void exportBoreholesToGMS(std::string listName, std::string fileName);
	/// Testing functionality for connection to FEM lib
	void FEMTestStart();
	void loadPetrelFiles();
	void loadFEMConditions(std::string geoName);
	void mapGeometry(const std::string &geo_name);
	void openRecentFile();
	void about();
	void showAddPipelineFilterItemDialog(QModelIndex parentIndex);
	void showConditionWriterDialog();
	/// Call dialog for creating or modifying FEM conditions.
	void showCondSetupDialog(const std::string &geometry_name, const GeoLib::GEOTYPE object_type, std::size_t id, bool on_points = false);
	/// Allows setting the name for a geometric object
	void showGeoNameDialog(const std::string &geometry_name, const GeoLib::GEOTYPE object_type, std::size_t id);
	/// Calls the diagram prefs dialog from the Tools menu.
	void showDiagramPrefsDialog();
	/// Calls the diagram prefs dialog from the station list (i.e. for a specific station).
	void showDiagramPrefsDialog(QModelIndex &index);
	//TODO6 void showFileConverterDialog();
	void showLineEditDialog(const std::string &geoName);
	void showGMSHPrefsDialog();
	void showMshQualitySelectionDialog(VtkMeshSource* mshSource);
	void showNewProcessDialog();
	void showPropertiesDialog(std::string const& name);
	void showVisalizationPrefsDialog();
	void showTrackingSettingsDialog();
	void updateDataViews();
	void addFEMConditions(const std::vector<FEMCondition*> conditions);
	void writeFEMConditionsToFile(const QString &geoName, const FEMCondition::CondType type, const QString &fileName);
	void writeGeometryToFile(QString listName, QString fileName);
	void writeStationListToFile(QString listName, QString fileName);

	void on_actionExportVTK_triggered(bool checked = false);
	void on_actionExportVRML2_triggered(bool checked = false);
	void on_actionExportObj_triggered(bool checked = false);
	void on_actionExportOpenSG_triggered(bool checked = false);

	void createPresentationMenu();
	void startPresentationMode();
	void quitPresentationMode();

private:
	QMenu* createImportFilesMenu();
	void loadFile(ImportFileType::type t, const QString &fileName);
	void loadFEMConditionsFromFile(const QString &fileName, std::string geoName = "");
	void readSettings();
	void writeSettings();
	QString getLastUsedDir();

	QString curFile;

	BaseLib::FileFinder _fileFinder;
	GEOModels* _geoModels;
	MshModel* _meshModels;
	ElementTreeModel* _elementModel;
	ProcessModel* _processModel;
	ProjectData _project;
	VtkVisPipeline* _vtkVisPipeline;
	QList<QRect> _screenGeometries;
	QWidget* _vtkWidget;
	QByteArray _windowState;
	QMenu* _import_files_menu;
	QSignalMapper* _signal_mapper;

#ifdef OGS_USE_VRPN
	TrackingSettingsWidget* _trackingSettingsWidget;
#endif     // OGS_USE_VRPN
	VisPrefsDialog* _visPrefsDialog;

signals:
	void fileUsed( QString filename );
	void fileOpenRequested( int );
};

class StartQt4
{
public:
	StartQt4()
	{
		int i = 0;
		QApplication* qapp = new QApplication(i, NULL);
		qapp->exec();
	}
};

#endif // MAINWINDOW_H
