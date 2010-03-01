//!
//! @file   Port.h
//! @author Björn Eriksson <bjorn.eriksson@liu.se>
//! @date   2010-01-16
//!
//! @brief Contains Port base class as well as Sub classes
//!
//$Id$

#ifndef PORT_H_INCLUDED
#define PORT_H_INCLUDED

#include "Node.h"
#include "Component.h"
#include "win32dll.h"
#include <string>

using namespace std;

typedef string PortTypeT;

class DLLIMPORTEXPORT Port
{
    friend class Component;
    friend class ComponentSystem;
    friend Port* CreatePort(const string &rPortType);

public:
    virtual double readNode(const size_t idx);
    virtual void writeNode(const size_t idx, const double value);
    void saveLogData(string filename);

    vector<double> *getTimeVectorPtr();
    vector<vector<double> > *getDataVectorPtr();

    bool isConnected();

    const string &getNodeType();
    const string &getPortType();
    const string &getPortName();

    Node* getNodePublic();

protected:
    //Constructors - Destructors
    Port();
    Port(string portname, string node_type);
    virtual ~Port();

    PortTypeT mPortType;

    void setNode(Node* pNode);
    Node &getNode();
    Node *getNodePtr();

private:
    string mPortName;
    NodeTypeT mNodeType;
    Node* mpNode;
    Component* mpComponent;
    bool mIsConnected;

    void clearNode();
};


class SystemPort :public Port
{
    friend class Component;
    friend class ComponentSystem;
    friend Port* CreatePort(const string &rPortType);

protected:
    //Constructors
    SystemPort();
};


class PowerPort :public Port
{
    friend class Component;
    friend class ComponentSystem;
    friend Port* CreatePort(const string &rPortType);

protected:
    //Constructors
    PowerPort();
    PowerPort(string portname, string node_type);
};


class ReadPort :public Port
{
    friend class Component;
    friend class ComponentSystem;
    friend Port* CreatePort(const string &rPortType);

public:
    void writeNode(const size_t idx, const double value);

protected:
    //Constructors
    ReadPort();
    ReadPort(string portname, string node_type);
};


class WritePort :public Port
{
    friend class Component;
    friend class ComponentSystem;
    friend Port* CreatePort(const string &rPortType);

public:
    double readNode(const size_t idx);

protected:
    //Constructors
    WritePort();
    WritePort(string portname, string node_type);
};

Port* CreatePort(const string &rPortType);

#endif // PORT_H_INCLUDED
