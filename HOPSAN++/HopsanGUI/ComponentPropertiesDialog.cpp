//!
//! @file   ComponentPropertiesDialog.cpp
//! @author Björn Eriksson <bjorn.eriksson@liu.se>
//! @date   2010-03-01
//!
//! @brief Contains a dialog class for changing component properties
//!
//$Id$

#include <QtGui>
#include <cassert>
#include <iostream>

#include "ComponentPropertiesDialog.h"
#include "MainWindow.h"
#include "GUIPort.h"
#include "MessageWidget.h"
#include "GUIObjects/GUIComponent.h"
#include "GUIObjects/GUIContainerObject.h"
#include "GUIObjects/GUISystem.h"
#include "UndoStack.h"
#include "ProjectTabWidget.h"
#include "SystemParametersWidget.h"

#include <QToolButton>


//! @class ComponentPropertiesDialog
//! @brief The ComponentPropertiesDialog class is a Widget used to interact with component parameters.
//!
//! It reads and writes parameters to the core components.
//!


//! @brief Constructor for the parameter dialog for components
//! @param pGUIComponent Pointer to the component
//! @param parent Pointer to the parent widget
ComponentPropertiesDialog::ComponentPropertiesDialog(GUIComponent *pGUIComponent, QWidget *parent)
    : QDialog(parent)
{
    mpGUIComponent = pGUIComponent;
    createEditStuff();
}


//! @brief Creates the contents in the parameter dialog
void ComponentPropertiesDialog::createEditStuff()
{
    mpNameEdit = new QLineEdit(mpGUIComponent->getName());

    QFont fontH1;
    fontH1.setBold(true);

    QFont fontH2;
    fontH2.setBold(true);
    fontH2.setItalic(true);

    QLabel *pParameterLabel = new QLabel("Parameters");
    pParameterLabel->setFont(fontH1);

    QGridLayout *parameterLayout = new QGridLayout;

    QVector<QString> parnames = mpGUIComponent->getParameterNames();
    QVector<QString>::iterator pit;
    size_t n = 0;
    for ( pit=parnames.begin(); pit!=parnames.end(); ++pit )
    {
        QString valueTxt;
        if(mpGUIComponent->isParameterMappedToSystemParameter(*pit))
        {
            if(mpGUIComponent->mpParentContainerObject->getCoreSystemAccessPtr()->hasSystemParameter(mpGUIComponent->getSystemParameterKey(*pit)))
            {
                valueTxt = mpGUIComponent->getSystemParameterKey(*pit);
            }
            else
            {
                mpGUIComponent->forgetSystemParameterMapping(*pit);
                valueTxt.setNum(mpGUIComponent->getParameterValue(*pit), 'g', 6 );
                gpMainWindow->mpMessageWidget->printGUIWarningMessage(tr("Warning: Global parameter no longer exists, replacing with last used value."));
            }
        }
        else
        {
            valueTxt.setNum(mpGUIComponent->getParameterValue(*pit), 'g', 6 );
        }
        mvParameterLayout.push_back(new ParameterLayout(*pit,
                                                        mpGUIComponent->getParameterDescription(*pit),
                                                        valueTxt,
                                                        mpGUIComponent->getParameterUnit(*pit),
                                                        mpGUIComponent));

        parameterLayout->addLayout(mvParameterLayout.back(), n, 0);
        ++n;
    }


    QGridLayout *startValueLayout = new QGridLayout;
    size_t sr=0;
    QLabel *pStartValueLabel = new QLabel("Start Values");
    pStartValueLabel->setFont(fontH1);

    QList<GUIPort*> ports = mpGUIComponent->getPortListPtrs();
    QList<GUIPort*>::iterator portIt;
    double j=0;
    QVector<QVector<QString> > startDataNamesStr, startDataUnitsStr;
    QVector<QVector<double> > startDataValuesDbl;
    startDataNamesStr.resize(ports.size());
    startDataValuesDbl.resize(ports.size());
    startDataUnitsStr.resize(ports.size());
    mvStartValueLayout.resize(ports.size());
    for ( portIt=ports.begin(); portIt!=ports.end(); ++portIt )
    {
        (*portIt)->getStartValueDataNamesValuesAndUnits(startDataNamesStr[j], startDataValuesDbl[j], startDataUnitsStr[j]);
        if(!(startDataNamesStr[j].isEmpty()))
        {
            QString portName("Port, ");
            portName.append((*portIt)->getName());
            QLabel *portLabelName = new QLabel(portName);
            portLabelName->setFont(fontH2);
            startValueLayout->addWidget(portLabelName, sr, 0);
            ++sr;

            mvStartValueLayout[j].resize(startDataNamesStr[j].size());
            for(size_t i=0; i < startDataNamesStr[j].size(); ++i)
            {
                mvStartValueLayout[j][i]= new ParameterLayout("",
                                                              startDataNamesStr[j][i],
                                                              startDataValuesDbl[j][i],
                                                              startDataUnitsStr[j][i],
                                                              mpGUIComponent);
                startValueLayout->addLayout(mvStartValueLayout[j][i], sr, 0);

                ++sr;
            }
            ++j;
        }
    }


    //qDebug() << "after parnames";

    okButton = new QPushButton(tr("&Ok"));
    okButton->setDefault(true);
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->setDefault(false);

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(okButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::ActionRole);

    connect(okButton, SIGNAL(pressed()), SLOT(okPressed()));
    connect(cancelButton, SIGNAL(pressed()), SLOT(close()));

    QHBoxLayout *pNameLayout = new QHBoxLayout;
    QLabel *pNameLabel = new QLabel("Name: ");
    pNameLayout->addWidget(pNameLabel);
    pNameLayout->addWidget(mpNameEdit);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    int lr = 0; //Layout row
    mainLayout->addLayout(pNameLayout, lr, 0);
    mainLayout->addWidget(buttonBox, lr, 1);
    ++lr;

    if(!(mvParameterLayout.empty()))
    {
        mainLayout->addWidget(pParameterLabel, lr, 0);
        ++lr;
        mainLayout->addLayout(parameterLayout, lr, 0);
        ++lr;
    }
    if(!(mvStartValueLayout[0].isEmpty()))
    {
        mainLayout->addWidget(pStartValueLabel,lr, 0);
        ++lr;
        mainLayout->addLayout(startValueLayout, lr, 0);
    }
    setLayout(mainLayout);

    setWindowTitle(tr("Parameters"));
}


//! @brief Reads the values from the dialog and writes them into the core component
void ComponentPropertiesDialog::okPressed()
{
    mpGUIComponent->mpParentContainerObject->renameGUIModelObject(mpGUIComponent->getName(), mpNameEdit->text());
    //qDebug() << mpNameEdit->text();

    setParameters();
    setStartValues();
}


//! Sets the parameters in the core component. Read the values from the dialog and write them into the core component.
void ComponentPropertiesDialog::setParameters()
{
    bool addedUndoPost = false;
    for (size_t i=0 ; i < mvParameterLayout.size(); ++i )
    {
        QString requestedParameter = mvParameterLayout[i]->getDataValueTxt();
        bool ok;
        double newValue = requestedParameter.toDouble(&ok);

        if(!ok)     //Global parameter
        {
            if(mpGUIComponent->mpParentContainerObject->getCoreSystemAccessPtr()->hasSystemParameter(requestedParameter))
            {
                mpGUIComponent->mapParameterToSystemParameter(mvParameterLayout[i]->getDataName(), requestedParameter);
            }
            else    //User has written something illegal
            {
                //! @todo Make something better, like showing a warning box, if parameter is not ok. Maybe check all parameters before setting any of them.
                MessageWidget *messageWidget = gpMainWindow->mpMessageWidget;//qobject_cast<MainWindow *>(this->parent()->parent()->parent()->parent()->parent()->parent())->mpMessageWidget;
                messageWidget->printGUIMessage(QString("ComponentPropertiesDialog::setParameters(): You must give a correct value for '").append(mvParameterLayout[i]->getDataName()).append(QString("', putz. Try again!")));
                qDebug() << "Inte okej!";
                return;
            }
        }
        else
        {
            if(mpGUIComponent->getParameterValue(mvParameterLayout[i]->getDataName()) != newValue)     //Normal parameter (a double value)
            {
                if(!addedUndoPost)
                {
                    this->mpGUIComponent->mpParentContainerObject->mUndoStack->newPost("changedparameters");
                    addedUndoPost = true;
                }
                this->mpGUIComponent->mpParentContainerObject->mUndoStack->registerChangedParameter(mpGUIComponent->getName(), mvParameterLayout[i]->getDataName(), mpGUIComponent->getParameterValue(mvParameterLayout[i]->getDataName()), newValue);
            }
            mpGUIComponent->setParameterValue(mvParameterLayout[i]->getDataName(), newValue);
        }
    }

    std::cout << "Parameters updated." << std::endl;
    this->close();
}


void ComponentPropertiesDialog::setStartValues()
{
    QList<GUIPort*> ports = mpGUIComponent->getPortListPtrs();
    QList<GUIPort*>::iterator portIt;
    QVector<QString> startDataNamesStr, startDataUnitsStr;
    QVector<double> startDataValuesDbl;
    size_t j=0;
    for ( portIt=ports.begin(); portIt!=ports.end(); ++portIt )
    {
        startDataNamesStr.resize(mvStartValueLayout[j].size());
        startDataValuesDbl.resize(mvStartValueLayout[j].size());
        startDataUnitsStr.resize(mvStartValueLayout[j].size());
        for(size_t i=0; i < mvStartValueLayout[j].size(); ++i)
        {
            startDataNamesStr[i] = mvStartValueLayout[j][i]->getDescriptionName();
            startDataValuesDbl[i] = mvStartValueLayout[j][i]->getDataValue();
        }
        (*portIt)->setStartValueDataByNames(startDataNamesStr, startDataValuesDbl);
        ++j;
    }
    std::cout << "Start values updated." << std::endl;
    this->close();
}
