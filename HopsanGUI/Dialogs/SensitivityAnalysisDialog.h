/*-----------------------------------------------------------------------------
 This source file is a part of Hopsan

 Copyright (c) 2009 to present year, Hopsan Group

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 For license details and information about the Hopsan Group see the files
 GPLv3 and HOPSANGROUP in the Hopsan source code root directory

 For author and contributor information see the AUTHORS file
-----------------------------------------------------------------------------*/

//!
//! @file   SensitivityAnalysisDialog.h
//! @author Robert Braun <robert.braun@liu.se>
//! @date   2011-12-01
//!
//! @brief Contains a class for the sensitivity analysis dialog
//!
//$Id$

#ifndef SENSITIVITYANALYSISDIALOG_H
#define SENSITIVITYANALYSISDIALOG_H

#include "OpsEvaluator.h"
#include "OpsWorkerParameterSweep.h"

#include <QDialog>

// Qt forward declaration
class QTreeWidgetItem;
class QTreeWidget;
class QGridLayout;
class QSpinBox;
class QRadioButton;
class QProgressBar;
class QLabel;
class QLineEdit;
class QCheckBox;

// Hopsan forward declaration
class ModelWidget;
class SensitivityAnalysisSettings;
class SystemContainer;
class SensitivityAnalysisDialog;
class RemoteSimulationQueueHandler;

class SensitivityAnalysisEvaluator : public Ops::Evaluator
{
    friend class SensitivityAnalysisDialog;
public:
    SensitivityAnalysisEvaluator(SensitivityAnalysisDialog *pDialog, ModelWidget *pModel, QVector<QPair<double, double> > parLimits, QStringList &parComps, QStringList &par, QList<QStringList> &outputVars, int nThreads);
    bool init();
    void finalize();
    void evaluateAllPoints();
    void evaluateAllCandidates();
private:
    void plot();
    void setParameters(QVector<QVector<double> > *pPoints);
    SensitivityAnalysisDialog *mpDialog;
    QVector<QPair<double, double> > mLimits;
    ModelWidget *mpModel;
    QVector<ModelWidget *> mModelPtrs;
    QStringList mParComps, mPars;
    QList<QStringList> mOutputVars;
    RemoteSimulationQueueHandler *mpRemoteSimulationQueueHandler=0;

    int mNumParallelModels=1;
    bool mUseRemoteSimulators=false;
};


class SensitivityAnalysisDialog : public QDialog
{
    Q_OBJECT

public:
    SensitivityAnalysisDialog(QWidget *parent = 0);
    enum DistributionEnumT {UniformDistribution, NormalDistribution};

public slots:
    void open();
    void loadSettings();
    void saveSettings();
    void updateProgressBar(int i);

private slots:
    void updateChosenParameters(QTreeWidgetItem* item, int i);
    void updateChosenVariables(QTreeWidgetItem* item, int i);
    void run();
    void abort();

private:
    //Parameters
    QTreeWidget *mpParametersList;
    //QLabel *mpParametersLabel;
    //QLabel *mpParameterNameLabel;
    //QLabel *mpParameterAverageLabel;
    //QLabel *mpParameterSigmaLabel;
    QGridLayout *mpParametersLayout;
    //QGroupBox *mpParametersGroupBox;

    //Output
    QTreeWidget *mpOutputList;
    //QLabel *mpOutputLabel;
    //QLabel *mpOutputNameLabel;
    QGridLayout *mpOutputLayout;
    //QGroupBox *mpOutputGroupBox;

    //Member widgets
    QCheckBox *mpUseRemoteSimulatorsCheckBox;
    QSpinBox *mpNumRemoteParallelModelsSpinBox;
    QSpinBox *mpStepsSpinBox;
    QRadioButton *mpUniformDistributionRadioButton;
    QRadioButton *mpNormalDistributionRadioButton;
    QProgressBar *mpProgressBar;

    //Member variables
    ModelWidget *mpModel;
    SensitivityAnalysisSettings *mpSettings;
    QStringList mSelectedComponents;
    QStringList mSelectedParameters;
    QList<QLabel*> mpParameterLabels;
    QList<QLineEdit*> mpParameterAverageLineEdits;
    QList<QLineEdit*> mpParameterSigmaLineEdits;
    QList<QLineEdit*> mpParameterMinLineEdits;
    QList<QLineEdit*> mpParameterMaxLineEdits;

    QList<QStringList> mOutputVariables;
    QList<QLabel*> mpOutputLabels;

    bool mAborted;

    SensitivityAnalysisEvaluator *mpEvaluator;
    Ops::WorkerParameterSweep *mpWorker;
};

#endif // SENSITIVITYANALYSISDIALOG_H
