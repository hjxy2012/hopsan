//!
//! @file   XMLUtilities.h
//! @author Peter Nordin <peter.nordin@liu.se>
//! @date   2010-11-xx
//!
//! @brief Contains XML DOM help functions that are more or less Hopsan specific
//!
//$Id$

#ifndef XMLUTILITIES_H
#define XMLUTILITIES_H

#include <QtXml>

QDomElement loadXMLDomDocument(QFile &rFile, QDomDocument &rDomDocument, QString rootTagName);

void appendRootXMLProcessingInstruction(QDomDocument &rDomDocument);

QDomElement appendHMFRootElement(QDomDocument &rDomDocument, QString hmfVersion, QString hopsanGuiVersion, QString hopsanCoreVersion);

//! @todo We could go back to using only appendDomNode and then overload manny different functions with same anme but different input arguments)
QDomElement appendDomElement(QDomElement &rDomElement, const QString element_name);
void appendDomTextNode(QDomElement &rDomElement, const QString element_name, const QString text);
void appendDomBooleanNode(QDomElement &rDomElement, const QString element_name, const bool value);

void appendDomValueNode(QDomElement &rDomElement, const QString element_name, const double val);
void appendDomValueNode2(QDomElement &rDomElement, const QString element_name, const double a, const double b);
void appendDomValueNode3(QDomElement &rDomElement, const QString element_name, const double a, const double b, const double c);
void appendDomValueNodeN(QDomElement &rDomElement, const QString element_name, const QVector<qreal> &rValues);

bool parseDomBooleanNode(QDomElement domElement);
qreal parseDomValueNode(QDomElement domElement);
void parseDomValueNode2(QDomElement domElement, double &rA, double &rB);
void parseDomValueNode3(QDomElement domElement, double &rA, double &rB, double &rC);

//Attribute help functions
void appendPoseTag(QDomElement &rDomElement, qreal x, qreal y, qreal th, bool flipped);
void appendPortPoseTag(QDomElement &rDomElement, QString name, qreal x, qreal y, qreal th);
void appendCoordinateTag(QDomElement &rDomElement, qreal x, qreal y);
void appendViewPortTag(QDomElement &rDomElement, qreal x, qreal y, qreal zoom);
void appendSimulationTimeTag(QDomElement &rDomElement, qreal start, qreal step, qreal stop);

void parsePoseTag(QDomElement domElement, qreal &rX, qreal &rY, qreal &rTheta, bool &rFlipped);
void parsePortPoseTag(QDomElement domElement, QString &rName, qreal &rX, qreal &rY, qreal &rTheta);
void parseCoordinateTag(QDomElement domElement, qreal &rX, qreal &rY);
void parseViewPortTag(QDomElement domElement, qreal &rX, qreal &rY, qreal &rZoom);
void parseSimulationTimeTag(QDomElement domElement, qreal &rStart, qreal &rStep, qreal &rStop);

//Color help functions
QString makeRgbString(QColor color);
void parseRgbString(QString rgb, double &red, double &green, double &blue);

//Save Load Definitions
//! @todo clean up this list and give some smarter names
#define HMF_ROOTTAG "hopsanmodelfile"
#define HMF_OBJECTS "objects"
#define HMF_OBJECTTAG "object"              //Non core Gui Object
#define HMF_COMPONENTTAG "component"
#define HMF_SYSTEMTAG "system"
#define HMF_SYSTEMPORTTAG "systemport"
#define HMF_CONNECTIONS "connections"
#define HMF_CONNECTORTAG "connect"
#define HMF_PARAMETERTAG "parameter"
#define HMF_PARAMETERS "parameters"
#define HMF_FAVORITEVARIABLETAG "favoritevariable"
#define HMF_STARTVALUES "startvalues"
#define HMF_STARTVALUE "startvalue"
#define HMF_GROUPTAG "group"
#define HMF_TEXTWIDGETTAG "textwidget"
#define HMF_BOXWIDGETTAG "boxwidget"
#define HMF_PORTSTAG "ports"
#define HMF_NAMESTAG "names"

#define HMF_NAMETAG "name"
#define HMF_TYPETAG "typename"
#define HMF_CQSTYPETAG "cqs_type"
#define HMF_PORTTAG "port"

#define HMF_HOPSANGUITAG "hopsangui"
#define HMF_COORDINATES "coordinates"
#define HMF_COORDINATETAG "coordinate"
#define HMF_GEOMETRIES "geometries"
#define HMF_GEOMETRYTAG "geometry"
#define HMF_XYTAG "xy"                      //Containes an xy coordinate pair
#define HMF_EXTERNALPATHTAG "external_path" //Contains the path to an external subsystem
#define HMF_VALUETAG "value"
#define HMF_SYSTEMPARAMETERTAG "globalkey"
#define HMF_TRUETAG "true"
#define HMF_FALSETAG "false"
#define HMF_PORTPOSETAG "portpose"
#define HMF_POSETAG "pose"
#define HMF_VIEWPORTTAG "viewport"
#define HMF_NAMETEXTTAG "nametext"
#define HMF_NAMETEXTPOSTAG "nametextpos"
#define HMF_VISIBLETAG "nametextvisible"

#define HMF_CONNECTORSTARTCOMPONENTTAG "startcomponent"
#define HMF_CONNECTORSTARTPORTTAG "startport"
#define HMF_CONNECTORENDCOMPONENTTAG "endcomponent"
#define HMF_CONNECTORENDPORTTAG "endport"
#define HMF_CONNECTORDASHEDTAG "dashed"

#define HMF_SYSTEMAPPEARANCETAG "systemappearance"
#define CAF_ROOTTAG "hopsanobjectappearance"
#define HMF_DISPLAYNAMETAG "displayname"
#define HMF_ISOICONTAG "isoicon"
#define HMF_USERICONTAG "usericon"
#define HMF_ICONROTATIONTAG "iconrotation"

#define HMF_VERSIONTAG "hmfversion"
#define HMF_HOPSANGUIVERSIONTAG "hopsanguiversion"
#define HMF_HOPSANCOREVERSIONTAG "hopsancoreversion"
#define HMF_SIMULATIONTIMETAG "simulationtime"
#define HMF_SCRIPTFILETAG "scriptfile"


#endif // XMLUTILITIES_H
