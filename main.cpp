#include "classes.h"

void CloneEncryptAndPrint(Object &object1){
    Object* object2;
    object2=object1.Clone();
    int equal,identical;
    equal=object2->Equal(object1);
    identical=object2->Identical(object1);
    if (equal==1)
        cout << "Object 1 is equal to object 2!"<<endl;
    else
        cout << "Object 1 is not equal to object 2!"<<endl;
    if (identical==1)
        cout << "Object 1 identical to object 2!"<<endl;
    else
        cout << "Object 1 not identical to object 2!"<<endl;
    String* string1;
    string1=object1.ToString();
    String* string2;
    string2=object2->ToString();
    int length,i;
    length=string2->Length();
    for (int j=0; j<6; j++) {
        i = rand() % length;
        string2->UpdateAt(i, 'q');
    }
    string1->PrintString();
    string2->PrintString();
    string1->Concat(string2);
    length=string1->Length();
    cout<<"String length is: "<<length<<endl;
    char character1;
    character1=string1->At(length/2);
    if(length%2==0)
        cout<<"The middle character is: " <<character1<< endl;
    else{
        char character2;
        character2=string1->At((length/2)+1);
        cout<<"The middle characters are: " <<character1<<" and "<<character2<< endl;
    }
    string1->Clear();
    length=string1->Length();
    cout<<"String length after clear is: "<<length<<endl;
    delete string1;
    delete string2;
    delete object2;
}

int main(){
    Plane* plane;
    SecurityEmployee* security_employee;
    CleaningEmployee* cleaning_employee;
    MaintenanceEmployee* maintenance_employee;
    plane=new Plane("AIRPLANE",50);
    security_employee=new SecurityEmployee("SECYRITY_NAME");
    cleaning_employee=new CleaningEmployee("CLEANING_NAME");
    maintenance_employee=new MaintenanceEmployee("MAINTEN_NAME");
    cout<<endl<<endl<<endl;
    plane->Process(security_employee);
    plane->Process(cleaning_employee);
    plane->Process(maintenance_employee);
    int ready;
    ready=plane->ReadyCheck();
    if (ready==1)
        cout<<"Plane ready to take off!"<<endl<<endl<<endl;
    CloneEncryptAndPrint(*plane);
    cout<<endl<<endl<<endl;
    delete plane;
    delete security_employee;
    delete cleaning_employee;
    delete maintenance_employee;
return 0;
}

