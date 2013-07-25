#ifndef SHAPEPOPULATIONVIEWER_H
#define SHAPEPOPULATIONVIEWER_H

// local
#include "ui_ShapePopulationViewer.h"

// QT
#include <QDir>
#include <QVector>
#include <QMainWindow>
#include <QVTKWidget.h>
#include <QResizeEvent>
#include <QEvent>
#include <QSize>
#include <QString>

// VTK
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkScalarBarActor.h>
#include <vtkColorTransferFunction.h>
#include <vtkCamera.h>


/**
 * ShapePopulationViewer Gui class specification.  This class contains all model data and controller callbacks, if we are going to consider the code within the MVC paradigm.  See
 * ui_ShapePopulationViewer.h for information on the construction of the gui itself.  It is an autogenerated file from the ShapePopulationViewer.ui file, which could also be used as reference.
 *
 * Generally speaking there are two classes of functionality given by the code, viewing options and filesystem interaction.  The filesystem interaction is supported by callbacks which an both read and write meshes to .vtk
 * formatted files.  The viewing option functionality includes the propogation of renderer interaction between QVTKWidgets, the ability to rearrange the QVTKWidgets in a user specified number of columns, and the ability to
 * change the colormap used to view the meshes, ranging over any colormap present in the .vtk file originally.
 *
 * @brief The ShapePopulationViewer class
 * @author Michael Guarino
 */
class ShapePopulationViewer : public QMainWindow, public Ui::ShapePopulationViewer
{
  Q_OBJECT
public:
  // Constructor/Destructor
  ShapePopulationViewer();
  ~ShapePopulationViewer() {}
public slots:

  virtual void slotExit();

protected:

   /**
    * The user selected working directory
    * @brief directory
    */
   QDir directory;
   /**
    * vtkcamera shared by the renderWindows when the surfaces are synchronized
    * @brief camera
    */
   vtkCamera *headcam;
   /**
    * vector of QVTKWidget
    * @brief widgetList
    */
   QVector<QVTKWidget *> *widgetList;
   /**
    * Vector of vtkRenderWindows selected
    * @brief selectedWidgetList
    */
   QVector<vtkRenderWindow *> *windowList;
   /**
    * Vector of vtkPolyDataMapper's, maintained to make colormap updates easier and access the polydata (getInput)
    * @brief mapperList
    */
   QVector<vtkPolyDataMapper *> *mapperList;


   int loaded;

   //Display functionsn
   void updateWidgets();
   void ModifiedHandler();
   void SelectedWidget(vtkObject* selectedObject, unsigned long, void*);

   void updateCMaps(vtkMapper*  mapper, vtkColorTransferFunction* DistanceMapTFunc, double *rangeLUT);

   void resizeEvent(QResizeEvent* event);

   void printColNumber(int colNumber);
   int getNumberOfColumns();
   int getNumberOfRows(int colNumber);
   void placeWidgetInArea(int colNumber);
   void resizeWidgetInArea();

protected slots:
   void writeMeshes();
   void openVTKS();

   //View Options
   void on_radioButton_4_toggled();  //all
   void on_radioButton_5_toggled(); //square
   void on_colNumberEdit_editingFinished();
   void on_colNumberSlider_valueChanged();
   void on_colNumberSlider_sliderReleased();
   void on_pushButton_flip_clicked();

   //Synchro Options
   void on_radioButton_1_toggled();
   void on_radioButton_2_toggled();
   void on_checkBox_synchro_toggled(bool checked);

   //
   void on_colorMapBox_currentIndexChanged();

   //Axis change
   void on_toolButton_0_clicked();
   void on_toolButton_1_clicked();
   void on_toolButton_2_clicked();
   void on_toolButton_3_clicked();
   void on_toolButton_4_clicked();
   void on_toolButton_5_clicked();
   void on_toolButton_6_clicked();
   void viewChange(int x, int y, int z);

};

#endif
