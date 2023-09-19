#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <cstdlib>
using namespace std;


class String;

class Object{
    int id;
    static int counter;
public:
    Object(int object_id);
    Object();
    virtual ~Object(void);
    virtual int Equal(Object &Object2);
    virtual int Identical(Object &Object2);
    virtual Object* Clone()=0;
    virtual String* ToString();
    int ObjectGetId();
};


class String : public Object{
    string tostring;
public:
    String(string desc,int string_id);
    String(string desc);
    ~String();
    int Length();
    string GetToString();
    void Clear();
    char At(int i);
    void UpdateAt(int i, char newchar);
    void Concat(String* add_string);
    void PrintString();
    String* Clone();
    int Equal(String& string2);
};

class Employee;
class PassengerCompartment;
class EquipmentCompartment;
class CargoBay;

class Plane:public Object {
    string plane_title;
    int plane_capacity;
    int passenger_compartment_number;
    PassengerCompartment **passenger_compartment;
    EquipmentCompartment **equipment_compartment;
    CargoBay *cargo_bay;
public:
    Plane(string p_title, int p_capacity);
    Plane(int plane_id, string p_title, int p_capacity, int pass_comp_num);
    ~Plane();
    String *ToString();
    Plane *Clone();
    int ReadyCheck();
    string PlaneGetTitle();
    int PlaneGetCapacity();
    int PlaneGetPassCompNum();
    PassengerCompartment *PlaneGetPassComp(int i);
    EquipmentCompartment *PlaneGetEquipComp(int i);
    CargoBay *PlaneGetCargoBay();
    int Equal(Plane& plane2);
    int Identical(Plane &plane2);
    void Process(Employee* e);
};


class PlaneComponent:public Object{
public:
    PlaneComponent(int plane_comp_id);
    PlaneComponent();
    virtual ~PlaneComponent();
    virtual int ReadyCheck()=0;
    virtual void Process(Employee*)=0;
    virtual void SetCleaningWorkDone();
    virtual void SetSecurityWorkDone();
    virtual void SetMaintenanceWorkDone();
};


class PassengerCompartment: public PlaneComponent{
    PassengerCompartment* internal_passenger_compartment;
    int internal;
    int security_work_done;
    int cleaning_work_done;
public:
    PassengerCompartment(int inter);
    PassengerCompartment(int passenger_comp_id,int inter,int security_work,int cleaning_work);
    ~PassengerCompartment();
    void Process(Employee* e);
    PassengerCompartment* Clone();
    String* ToString();
    void SetCleaningWorkDone();
    void SetSecurityWorkDone();
    int ReadyCheck();
    PassengerCompartment* PassCompGetInternalPassComp();
    int PassCompGetCleaningWork();
    int PassCompGetSecurityWork();
    int Equal(PassengerCompartment &passcomp2);
    int Identical(PassengerCompartment& passcomp2);
};

class PrivateCompartment: public PlaneComponent{
public:
    PrivateCompartment(int private_comp_id);
    PrivateCompartment();
    ~PrivateCompartment();
};

class EquipmentCompartment:public PrivateCompartment{
    int security_work_done;
    int maintenance_work_done;
public:
    EquipmentCompartment();
    EquipmentCompartment(int equipment_comp_id,int security_work,int maintenance_work);
    ~EquipmentCompartment();
    void Process(Employee* e);
    EquipmentCompartment* Clone();
    String* ToString();
    void SetSecurityWorkDone();
    void SetMaintenanceWorkDone();
    int ReadyCheck();
    int EquipmentGetMaintenanceWork();
    int EquipmentGetSecurityWork();
    int Equal(EquipmentCompartment& equipment2);
};

class CargoBay:public PrivateCompartment{
    EquipmentCompartment* equipment_compartment;
    int security_work_done;
    int maintenance_work_done;
    int cleaning_work_done;
public:
    CargoBay();
    CargoBay(int cargo_bay_id,int security_work,int maintenance_work,int cleaning_work);
    ~CargoBay();
    void Process(Employee *e);
    CargoBay* Clone();
    String* ToString();
    void SetCleaningWorkDone();
    void SetSecurityWorkDone();
    void SetMaintenanceWorkDone();
    int ReadyCheck();
    int CargoGetCleaningWork();
    int CargoGetMaintenanceWork();
    int CargoGetSecurityWork();
    EquipmentCompartment* CargoBayGetEquipmentComp();
    int Equal(CargoBay& cargo2);
    int Identical(CargoBay &cargo2);
};

class Employee:public Object {
    string name;
public:
    Employee(int employee_id, string employee_name);
    Employee(string employee_name);
    virtual ~Employee();
    virtual void WorkOn(PassengerCompartment *) = 0;
    virtual void WorkOn(EquipmentCompartment *) = 0;
    virtual void WorkOn(CargoBay *) = 0;
    virtual void Report(PlaneComponent *) = 0;
    string GetEmployeeName();
    int Equal(Employee &employee2);
};


class SecurityEmployee:public Employee{
public:
    SecurityEmployee(int security_id,string security_name);
    SecurityEmployee(string security_name);
    ~SecurityEmployee();
    void Report(PlaneComponent* plane_component);
    void WorkOn(PassengerCompartment* passenger_compartment);
    void WorkOn(EquipmentCompartment* equipment_compartment);
    void WorkOn(CargoBay* cargo_bay);
    SecurityEmployee* Clone();
    String* ToString();
};

class MaintenanceEmployee:public Employee{
public:
    MaintenanceEmployee(int maintenance_id,string maintenance_name);
    MaintenanceEmployee(string maintenance_name);
    ~MaintenanceEmployee();
    void Report(PlaneComponent* plane_component);
    void WorkOn(PassengerCompartment* passenger_compartment);
    void WorkOn(EquipmentCompartment* equipment_compartment);
    void WorkOn(CargoBay* cargo_bay);
    MaintenanceEmployee* Clone();
    String* ToString();
};

class CleaningEmployee:public Employee{
public:
    CleaningEmployee(int cleaning_id,string cleaning_name);
    CleaningEmployee(string cleaning_employee);
    ~CleaningEmployee();
    void Report(PlaneComponent* plane_component);
    void WorkOn(PassengerCompartment* passenger_compartment);
    void WorkOn(EquipmentCompartment*);
    void WorkOn(CargoBay* cargo_bay);
    CleaningEmployee* Clone();
    String* ToString();

};


