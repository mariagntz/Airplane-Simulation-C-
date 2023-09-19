
#include "classes.h"

class String;
int Object:: counter=0;
Object::Object(int object_id) {
    id=object_id;
    cout<<"Object just created!"<<endl;
}
Object::Object(){
    id=counter;
    counter++;
    cout<<"Object just created!"<<endl;
}

Object::~Object(void) {
    cout<<"Object to be destroyed!"<<endl;
}


String *Object::ToString() {
    string object_description;
    stringstream ss;
    ss << id;
    object_description = ss.str();
    String* object_str;
    object_str=new String(object_description);
    return object_str;
}

int Object::ObjectGetId() {
    return id;
}

int Object::Equal(Object& Object2) {
    if (this->id==Object2.id)
        return 1;
    else
        return 0;
}

int Object::Identical(Object &Object2) {
    if (this==&Object2)
        return 1;
    else
        return 0;
}


String::String(string desc, int object_id) :Object(object_id){
    tostring=desc;
    cout<<"String just created!"<<endl;
}

String::String(string desc):Object() {
    tostring=desc;
    cout<<"String just created!"<<endl;
}

String::~String() {
    cout<<"String to be destroyed!"<<endl;
}

int String::Length() {
    return tostring.length();
}

string String::GetToString() {
    return tostring;
}

void String::Clear() {
    tostring.clear();
}

char String::At(int i) {
    return tostring.at(i);
}

void String::UpdateAt(int i, char newchar) {
    tostring[i]=newchar;
}

void String::Concat(String *add_string) {
    this->tostring+="\n";
    this->tostring=this->tostring+add_string->tostring;
}

void String::PrintString() {
    cout<<tostring<<endl;
}

String *String::Clone() {
    int clone_id=this->ObjectGetId();
    string clone_tostring=tostring;
    String* clone_string;
    clone_string= new String(clone_tostring,clone_id);
    return clone_string;
}

int String::Equal(String &string2) {
    if ((this->ObjectGetId()==string2.ObjectGetId()) && (this->tostring==string2.tostring))
        return 1;
    else
        return 0;
}

class Employee;
class PassengerCompartment;
class EquipmentCompartment;
class CargoBay;

Plane::Plane(string p_title, int p_capacity) :Object(){
    plane_title=p_title;
    plane_capacity=p_capacity;

    equipment_compartment= new EquipmentCompartment*[3];
    for(int i=0; i<3; i++)
        equipment_compartment[i] = new EquipmentCompartment();

    cargo_bay= new CargoBay();

    int passengers_number;
    srand (time(NULL));
    passengers_number=rand()%200+50;
    passenger_compartment_number=passengers_number/plane_capacity;
    if((passengers_number%plane_capacity)>0)
        passenger_compartment_number++;
    passenger_compartment=new PassengerCompartment*[passenger_compartment_number];
    for (int j=0; j<passenger_compartment_number; j++)
        passenger_compartment[j]= new PassengerCompartment(1);

    cout<<"Plane just created!"<<endl;
}

Plane::~Plane() {
    for(int i =0; i<3; i++)
        delete equipment_compartment[i];
    delete[] equipment_compartment;
    delete cargo_bay;
    for(int j=0; j<passenger_compartment_number; j++)
        delete passenger_compartment[j];
    delete[] passenger_compartment;
    cout<<"Plane to be destroyed!"<<endl;
}

Plane::Plane(int plane_id, string p_title, int p_capacity, int pass_comp_num) :Object(plane_id){
    plane_title=p_title;
    plane_capacity=p_capacity;
    passenger_compartment_number=pass_comp_num;
    equipment_compartment= new EquipmentCompartment*[3];
    passenger_compartment=new PassengerCompartment*[passenger_compartment_number];
    cout<<"Plane just created!"<<endl;
}

Plane *Plane::Clone() {
    int clone_id=this->ObjectGetId();
    string clone_title=plane_title;
    int clone_capacity=plane_capacity;
    int clone_pass_comp_num=passenger_compartment_number;
    Plane* clone_plane;
    clone_plane=new Plane(clone_id,clone_title,clone_capacity,clone_pass_comp_num);
    clone_plane->cargo_bay=this->cargo_bay->Clone();
    for(int i=0; i<3; i++)
        clone_plane->equipment_compartment[i]=this->equipment_compartment[i]->Clone();
    for(int j=0; j<passenger_compartment_number; j++)
        clone_plane->passenger_compartment[j]=this->passenger_compartment[j]->Clone();
    return clone_plane;
}

int Plane::ReadyCheck() {
    if (cargo_bay->ReadyCheck() == 0)
        return 0;
    for (int i = 0; i < passenger_compartment_number; i++) {
        if (passenger_compartment[i]->ReadyCheck() == 0)
            return 0;
    }
    for (int j = 0; j < 3; j++) {
        if (equipment_compartment[j]->ReadyCheck() == 0)
            return 0;
    }
    return 1;
}

String *Plane::ToString() {
    string plane_description;
    stringstream ss;
    ss << this->ObjectGetId();
    plane_description = ss.str();
    plane_description = "Plane id: "+plane_description+" title: "+plane_title+" has : ";
    String* plane_str;
    plane_str = new String(plane_description);
    String** pass_comp_str;
    String* cargo_str;
    String** equipment_str;
    cargo_str=cargo_bay->ToString();
    pass_comp_str= new String*[passenger_compartment_number];
    equipment_str=new String*[3];
    for (int i=0; i<3; i++){
        equipment_str[i]=equipment_compartment[i]->ToString();
    }
    equipment_str[0]->Concat(equipment_str[1]);
    equipment_str[0]->Concat(equipment_str[2]);
    for(int j=0; j<passenger_compartment_number; j++){
        pass_comp_str[j]=passenger_compartment[j]->ToString();
    }
    for(int x=1; x<passenger_compartment_number; x++){
        pass_comp_str[0]->Concat(pass_comp_str[x]);
    }
    plane_str->Concat(cargo_str);
    plane_str->Concat(pass_comp_str[0]);
    plane_str->Concat(equipment_str[0]);
    
    for(int i =0; i<3; i++)
       delete equipment_str[i];
    delete[] equipment_str;
    delete cargo_str;
    for(int j=0; j<passenger_compartment_number; j++)
       delete pass_comp_str[j];
    delete[] pass_comp_str;

    return plane_str;
}

string Plane::PlaneGetTitle() {
    return plane_title;
}

int Plane::PlaneGetCapacity() {
    return plane_capacity;
}

int Plane::PlaneGetPassCompNum() {
    return passenger_compartment_number;
}

PassengerCompartment *Plane::PlaneGetPassComp(int i) {
    return passenger_compartment[i];
}

EquipmentCompartment *Plane::PlaneGetEquipComp(int i) {
    return equipment_compartment[i];
}

CargoBay *Plane::PlaneGetCargoBay() {
    return cargo_bay;
}
int Plane::Equal(Plane& plane2){
    if (this->ObjectGetId()!= plane2.ObjectGetId())
        return 0;
    if (this->plane_title != plane2.plane_title)
        return 0;
    if (this->plane_capacity != plane2.plane_capacity)
        return 0;
    if (this->passenger_compartment_number != plane2.passenger_compartment_number)
        return 0;
    if(this->cargo_bay->Equal(*plane2.cargo_bay)==0)
        return 0;
    for (int i = 0; i <3; ++i) {
        if (this->equipment_compartment[i]->Equal(*plane2.equipment_compartment[i]) ==0)
            return 0;
    }
    for (int j = 0; j <passenger_compartment_number ; ++j) {
        if (this->passenger_compartment[j]->Equal(*plane2.passenger_compartment[j])==0)
            return 0;
    }
    return 1;
}

int Plane::Identical(Plane &plane2){
    if(this!=&plane2)
        return 0;
    if (this->cargo_bay->Identical(*plane2.cargo_bay)==0)
        return 0;
    for (int i = 0; i <3; ++i) {
        if (this->equipment_compartment[i]->Identical(*plane2.equipment_compartment[i]) ==0)
            return 0;
    }
    for (int j = 0; j <passenger_compartment_number ; ++j) {
        if (this->passenger_compartment[j]->Identical(*plane2.passenger_compartment[j])==0)
            return 0;
    }
    return 1;
    }

void Plane::Process(Employee *e) {
    cargo_bay->Process(e);
    for(int i=0; i<3; i++)
        equipment_compartment[i]->Process(e);
    for(int j=0; j<passenger_compartment_number; j++)
        passenger_compartment[j]->Process(e);
}


PlaneComponent::PlaneComponent(int plane_comp_id) :Object(plane_comp_id){
    cout<<"Plane Component just created!"<<endl;
}

PlaneComponent::~PlaneComponent() {
    cout<<"Plane Component to be destroyed!"<<endl;
}

PlaneComponent::PlaneComponent() :Object(){
    cout<<"Plane Component just created!"<<endl;
}

void PlaneComponent:: SetCleaningWorkDone(){}

void PlaneComponent:: SetSecurityWorkDone(){}

void PlaneComponent:: SetMaintenanceWorkDone(){}


PassengerCompartment::PassengerCompartment(int inter) :PlaneComponent(){
    security_work_done=0;
    cleaning_work_done=0;
    internal=inter;
    if (internal==1)
        internal_passenger_compartment=new PassengerCompartment(0);
    else internal_passenger_compartment=NULL;
    cout<<"Passenger Compartment just created!"<<endl;
}

PassengerCompartment::~PassengerCompartment() {
    if (internal==1)
        delete  internal_passenger_compartment;
    cout<<"Passenger Compartment to be destroyed!"<<endl;
}

PassengerCompartment::PassengerCompartment(int passenger_comp_id, int inter, int security_work, int cleaning_work) :PlaneComponent(passenger_comp_id){
    internal=inter;
    security_work_done=security_work;
    cleaning_work_done=cleaning_work;
    cout<<"Passenger Compartment just created!"<<endl;
}

void PassengerCompartment::Process(Employee *e) {
    if (internal==1)
        e->WorkOn(internal_passenger_compartment);
    e->WorkOn(this);
}

PassengerCompartment *PassengerCompartment::Clone() {
    int clone_id = this->ObjectGetId();
    int clone_internal = internal;
    int clone_security = security_work_done;
    int clone_cleaning = cleaning_work_done;
    PassengerCompartment *clone_passenger_compartment;
    clone_passenger_compartment = new PassengerCompartment(clone_id,clone_internal,clone_security,clone_cleaning);
    if (clone_internal==1)
        clone_passenger_compartment->internal_passenger_compartment=this->internal_passenger_compartment->Clone();
    else
        clone_passenger_compartment->internal_passenger_compartment=NULL;
    return clone_passenger_compartment;
}

String *PassengerCompartment::ToString() {
    string passenger_comp_description;
    stringstream ss;
    ss << this->ObjectGetId();
    passenger_comp_description="Passenger Compartment with id : "+ss.str();
    String* passenger_comp_str;
    if (internal==1) {
        passenger_comp_description+=" with internal Passenger Compartment: ";
        passenger_comp_str= new String(passenger_comp_description);
        String* internal_str;
        internal_str=this->internal_passenger_compartment->ToString();
        passenger_comp_str->Concat(internal_str);
	delete internal_str;
        return passenger_comp_str;

    }
    else {
        passenger_comp_description += " without internal passenger compartment ";
        passenger_comp_str = new String(passenger_comp_description);
        return passenger_comp_str;
    }
}

void PassengerCompartment::SetCleaningWorkDone() {
    cleaning_work_done=1;
}

void PassengerCompartment::SetSecurityWorkDone() {
    security_work_done=1;
}

int PassengerCompartment::ReadyCheck() {
    if (security_work_done==0)
        return 0;
    if (cleaning_work_done==0)
        return 0;
    if(internal_passenger_compartment->security_work_done==0)
        return 0;
    if(internal_passenger_compartment->cleaning_work_done==0)
         return 0;
    return 1;
}

PassengerCompartment *PassengerCompartment::PassCompGetInternalPassComp() {
    if(internal==1)
        return internal_passenger_compartment;
    else {
        cout << "No internal Passenger Compartment" << endl;
        return NULL;
    }
}

int PassengerCompartment::PassCompGetCleaningWork() {
    return cleaning_work_done;
}

int PassengerCompartment::PassCompGetSecurityWork() {
    return security_work_done;
}

int PassengerCompartment::Equal (PassengerCompartment &passcomp2) {
    if (this->ObjectGetId()!=passcomp2.ObjectGetId())
        return 0;
    if (this->security_work_done!=passcomp2.security_work_done)
        return 0;
    if (this->cleaning_work_done!=passcomp2.cleaning_work_done)
        return 0;
    if (this->internal!=passcomp2.internal)
        return 0;
    else if (this->internal == 1){
        if (this->Equal(*passcomp2.internal_passenger_compartment)==1)
            return 1;
        else return 0;
    }
    else return 1;
}

int PassengerCompartment::Identical(PassengerCompartment &passcomp2) {
    if (this != &passcomp2)
        return 0;
    if (this->internal == 1) {
        if (this->Identical(*passcomp2.internal_passenger_compartment)==1)
            return 1;
        else return 0;
    }
    else return 1;
}


PrivateCompartment::PrivateCompartment(int private_comp_id) :PlaneComponent(private_comp_id){
    cout<<"Private Compartment just created!"<<endl;
}

PrivateCompartment::PrivateCompartment() :PlaneComponent(){
    cout<<"Private Compartment just created!"<<endl;
}

PrivateCompartment::~PrivateCompartment() {
    cout<<"Private Compartment to be destroyed!"<<endl;
}

EquipmentCompartment::EquipmentCompartment() :PrivateCompartment(){
    security_work_done=0;
    maintenance_work_done=0;
    cout<<"Equipment Compartment just created!"<<endl;
}

EquipmentCompartment::EquipmentCompartment(int equipment_comp_id, int security_work, int maintenance_work) :PrivateCompartment(equipment_comp_id){
    security_work_done=security_work;
    maintenance_work_done=maintenance_work;
    cout<<"Equipment Compartment just created!"<<endl;
}

EquipmentCompartment::~EquipmentCompartment() {
    cout<<"Equipment Compartment to be destroyed!"<<endl;
}

void EquipmentCompartment::Process(Employee *e) {
    e->WorkOn(this);
}

EquipmentCompartment *EquipmentCompartment::Clone() {
    int clone_id=this->ObjectGetId();
    int clone_security=security_work_done;
    int clone_maintenance=maintenance_work_done;
    EquipmentCompartment* clone_equipment_compartment;
    clone_equipment_compartment=new EquipmentCompartment(clone_id,clone_security,clone_maintenance);
    return clone_equipment_compartment;
}

String *EquipmentCompartment::ToString() {
    string equipment_description;
    stringstream ss;
    ss << this->ObjectGetId();
    equipment_description = ss.str();
    equipment_description = "Equipment compartment with id: "+ equipment_description + " ";
    String* equipment_str;
    equipment_str = new String(equipment_description);
    return equipment_str;
}

void EquipmentCompartment::SetSecurityWorkDone() {
    security_work_done=1;
}

void EquipmentCompartment::SetMaintenanceWorkDone() {
    maintenance_work_done=1;
}

int EquipmentCompartment::ReadyCheck() {
    if (security_work_done==0)
        return 0;
    if (maintenance_work_done == 0)
        return 0;
    return 1;
}

int EquipmentCompartment::EquipmentGetMaintenanceWork() {
    return maintenance_work_done;
}

int EquipmentCompartment::EquipmentGetSecurityWork() {
    return security_work_done;
}

int EquipmentCompartment::Equal(EquipmentCompartment &equipment2) {
    if (this->ObjectGetId() != equipment2.ObjectGetId())
        return 0;
    if (this->security_work_done != equipment2.security_work_done)
        return 0;
    if (this->maintenance_work_done != equipment2.maintenance_work_done)
        return 0;
    return 1;
}

CargoBay::CargoBay() :PrivateCompartment(){
    equipment_compartment=new EquipmentCompartment();
    security_work_done=0;
    maintenance_work_done=0;
    cleaning_work_done=0;
    cout<<"Cargo Bay just created!"<<endl;
}

CargoBay::CargoBay(int cargo_bay_id, int security_work, int maintenance_work, int cleaning_work) :PrivateCompartment(cargo_bay_id){
    security_work_done=security_work;
    maintenance_work_done=maintenance_work;
    cleaning_work_done=cleaning_work;
    cout<<"Cargo Bay just created!"<<endl;
}

CargoBay::~CargoBay() {
    delete equipment_compartment;
    cout<<"Cargo Bay to be destroyed!"<<endl;
}

void CargoBay::Process(Employee *e) {
    e->WorkOn(equipment_compartment);
    e->WorkOn(this);
}

CargoBay *CargoBay::Clone() {
    int clone_id=this->ObjectGetId();
    int clone_security=security_work_done;
    int clone_maintenance=maintenance_work_done;
    int clone_cleaning=cleaning_work_done;
    CargoBay* clone_cargo_bay;
    clone_cargo_bay=new CargoBay(clone_id,clone_security,clone_maintenance,clone_cleaning);
    clone_cargo_bay->equipment_compartment=this->equipment_compartment->Clone();
    return clone_cargo_bay;
}

String *CargoBay::ToString() {
    string cargo_description;
    stringstream ss;
    ss << this->ObjectGetId();
    cargo_description = ss.str();
    cargo_description = "Cargo Bay with id: "+ cargo_description + " with : ";
    String* cargo_str;
    cargo_str = new String(cargo_description);
    String* equipment_str;
    equipment_str=this->equipment_compartment->ToString();
    cargo_str->Concat(equipment_str);
    delete equipment_str;
    return cargo_str;
}

void CargoBay::SetCleaningWorkDone() {
    cleaning_work_done=1;
}

void CargoBay::SetSecurityWorkDone() {
    security_work_done=1;
}

void CargoBay::SetMaintenanceWorkDone() {
    maintenance_work_done=1;
}

int CargoBay::ReadyCheck() {
    if (security_work_done==0)
        return 0;
    if (cleaning_work_done==0)
        return 0;
    if(maintenance_work_done==0)
        return 0;
    if(equipment_compartment->ReadyCheck()==0)
        return 0;
    return 1;

}

EquipmentCompartment *CargoBay::CargoBayGetEquipmentComp() {
    return equipment_compartment;
}

int CargoBay::CargoGetCleaningWork() {
    return cleaning_work_done;
}

int CargoBay::CargoGetMaintenanceWork() {
    return maintenance_work_done;
}

int CargoBay::CargoGetSecurityWork() {
    return security_work_done;
}

int CargoBay::Equal(CargoBay &cargo2) {
    if (this->ObjectGetId()!=cargo2.ObjectGetId())
        return 0;
    if (this->security_work_done!=cargo2.security_work_done)
        return 0;
    if (this->maintenance_work_done!=cargo2.maintenance_work_done)
        return 0;
    if (this->cleaning_work_done!=cargo2.cleaning_work_done)
        return 0;
    if (this->equipment_compartment->Equal(*cargo2.equipment_compartment) == 0)
        return 0;
    return 1;
}

int CargoBay::Identical(CargoBay &cargo2) {
    if (this!=&cargo2)
        return 0;
    if (this->equipment_compartment->Identical(*cargo2.equipment_compartment)==0)
        return 0;
    return 1;
}


Employee::Employee(int employee_id, string employee_name) :Object(employee_id){
    name=employee_name;
    cout<<"Employee just created!"<<endl;
}

Employee::Employee(string employee_name) :Object(){
    name=employee_name;
    cout<<"Employee just created!"<<endl;
}


string Employee::GetEmployeeName() {
    return name;
}


Employee::~Employee() {
    cout<<"Employee to be destroyed!"<<endl;
}

int Employee::Equal(Employee &employee2) {
    if(this->ObjectGetId()!=employee2.ObjectGetId())
        return 0;
    if (this->name!=employee2.name)
        return 0;
    return 1;
}


SecurityEmployee::SecurityEmployee(int security_id, string security_name) :Employee(security_id,security_name){
    cout<<"Security Employee just created!"<<endl;
}

SecurityEmployee::SecurityEmployee(string security_name) :Employee(security_name){
    cout<<"Security Employee just created!"<<endl;
}

SecurityEmployee::~SecurityEmployee() {
    cout<<"Security Employee to be destroyed!"<<endl;
}

void SecurityEmployee::Report(PlaneComponent *plane_component) {
    plane_component->SetSecurityWorkDone();
    cout<<"Security Employee worked on plane component with id: "<<plane_component->ObjectGetId();
    cout<<" OK!"<<endl;
}

void SecurityEmployee::WorkOn(PassengerCompartment *passenger_compartment) {
    this->Report(passenger_compartment);
}

void SecurityEmployee::WorkOn(EquipmentCompartment *equipment_compartment) {
    this->Report(equipment_compartment);
}

void SecurityEmployee::WorkOn(CargoBay *cargo_bay) {
    this->Report(cargo_bay);
}

SecurityEmployee *SecurityEmployee::Clone() {
    int clone_id=this->ObjectGetId();
    string clone_name=this->GetEmployeeName();
    SecurityEmployee* clone_security_employee;
    clone_security_employee= new SecurityEmployee(clone_id,clone_name);
    return clone_security_employee;
}

String *SecurityEmployee::ToString() {
    string security_description;
    stringstream ss;
    ss << this->ObjectGetId();
    security_description = "Security Employee with name: "+this->GetEmployeeName()+ " and id: "+ss.str();
    String* security_str;
    security_str = new String(security_description);
    return security_str;
}

MaintenanceEmployee::MaintenanceEmployee(int maintenance_id, string maintenance_name) :Employee(maintenance_id,maintenance_name){
    cout<<"Maintenance Employee just created!"<<endl;
}

MaintenanceEmployee::MaintenanceEmployee(string maintenance_name) :Employee(maintenance_name){
    cout<<"Maintenance Employee just created!"<<endl;
}

MaintenanceEmployee::~MaintenanceEmployee() {
    cout<<"Maintenance Employee to be destroyed!"<<endl;
}

void MaintenanceEmployee::Report(PlaneComponent *plane_component) {
    plane_component->SetMaintenanceWorkDone();
    cout<<"Maintenance Employee worked on plane component with id: "<<plane_component->ObjectGetId();
    cout<<" OK!"<<endl;
}

void MaintenanceEmployee::WorkOn(PassengerCompartment *passenger_compartment) {}

void MaintenanceEmployee::WorkOn(EquipmentCompartment *equipment_compartment) {
    this->Report(equipment_compartment);
}

void MaintenanceEmployee::WorkOn(CargoBay *cargo_bay) {
    this->Report(cargo_bay);
}

MaintenanceEmployee *MaintenanceEmployee::Clone() {
    int clone_id=this->ObjectGetId();
    string clone_name=this->GetEmployeeName();
    MaintenanceEmployee* clone_maintenance_employee;
    clone_maintenance_employee= new MaintenanceEmployee(clone_id,clone_name);
    return clone_maintenance_employee;
}

String *MaintenanceEmployee::ToString() {
    string maintenance_description;
    stringstream ss;
    ss << this->ObjectGetId();
    maintenance_description = "Maintenance Employee with name: "+this->GetEmployeeName()+ " and id: "+ss.str();
    String* maintenance_str;
    maintenance_str = new String(maintenance_description);
    return maintenance_str;
}

CleaningEmployee::CleaningEmployee(int cleaning_id, string cleaning_name) :Employee(cleaning_id,cleaning_name){
    cout<<"Cleaning Employee just created!"<<endl;
}

CleaningEmployee::CleaningEmployee(string cleaning_employee) :Employee(cleaning_employee){
    cout<<"Cleaning Employee just created!"<<endl;
}

CleaningEmployee::~CleaningEmployee() {
    cout<<"Cleaning Employee to be destroyed!"<<endl;
}

void CleaningEmployee::Report(PlaneComponent *plane_component) {
    plane_component->SetCleaningWorkDone();
    cout<<"Cleaning Employee worked on plane component with id: "<<plane_component->ObjectGetId();
    cout<<" OK!"<<endl;
}

void CleaningEmployee::WorkOn(PassengerCompartment *passenger_compartment) {
    this->Report(passenger_compartment);
}

void CleaningEmployee::WorkOn(EquipmentCompartment *) {}

void CleaningEmployee::WorkOn(CargoBay *cargo_bay) {
    this->Report(cargo_bay);
}

CleaningEmployee *CleaningEmployee::Clone() {
    int clone_id=this->ObjectGetId();
    string clone_name=this->GetEmployeeName();
    CleaningEmployee* clone_cleaning_employee;
    clone_cleaning_employee= new CleaningEmployee(clone_id,clone_name);
    return clone_cleaning_employee;
}

String *CleaningEmployee::ToString() {
    string cleaning_description;
    stringstream ss;
    ss << this->ObjectGetId();
    cleaning_description = "Cleaning Employee with name: "+this->GetEmployeeName()+ " and id: "+ss.str();
    String* cleaning_str;
    cleaning_str = new String(cleaning_description);
    return cleaning_str;
}
