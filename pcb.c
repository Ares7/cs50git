#include <iostream.h>
#include <sstream.h>
#include <vector.h>
#include <list.h>
#include <string.h>
#include "proc.h"
#include "rq.h"

using namespace std;


// creates a vector of Queues
void load_queue(vector<rq> &queue, unsigned int num_of_queues)
{
    for(int pos=0; pos<num_of_queues; pos++)
    {
        queue.push_back(rq());
    }
}

//returns the biggest queue position in the vector
unsigned int get_biggest_queue_pos(vector<rq> queues)
{
    unsigned int queue_pos = 0; // Pos of smaller queue. Default 0.
    unsigned int queue_size = queues.at(queue_pos).size(); // Its size
    for(unsigned int pos = 0; pos < queues.size(); pos++)
    {
        if(queues.at(pos).size() > queue_size)
        {
            queue_pos = pos;
            queue_size = queues.at(pos).size();
        }
    }
    return queue_pos; // Return smaller queue position in vector.
}



// Returns the smaller queue position in the vector.
unsigned int get_smaller_queue_pos(vector<rq> queues)
{
    unsigned int queue_pos = 0; // Pos of smaller queue. Default 0.
    unsigned int queue_size = queues.at(queue_pos).size(); // Its size
    for(unsigned int pos = 0; pos < queues.size(); pos++)
    {
        if(queues.at(pos).size() < queue_size)
        {
            queue_pos = pos;
            queue_size = queues.at(pos).size();
        }
    }
    return queue_pos; // Return smaller queue position in vector.
}

//Searches for a PID in entire system and erases it.
bool get_pid_process(vector<rq> &queue, int id)
{
    vector <proc> temp;
    proc process(0,0,0);
    int check;
    int number=id;
    int size=queue.size();

    /*checks rest of queues, including ready queues and device queues*/
    for(int i=0; i<size; i++)
    {
        temp=queue[i].get_queue();
        int size1=temp.size();
        for(int j=0; j<size1; j++)
        {
            process=temp.at(j);
            check=process.get_pid();
            if(check==number)
            {
                cout<<"Process found in a queue and being erased..."<<endl;
                queue[i].remove_process(j);
                float cputime=process.get_burst();
                float burstime=process.get_average();
                cout<<"Process information:"<<endl;
                cout<<"PID: "<<number<<endl<<"Acc CPU time: "<<cputime<<endl<<"Average burst time: "<<burstime<<endl;
                cout<<"Process killed"<<endl<<endl;
                return true;
            }
        }
    }

    /*Checks all CPUs in ready queues*/
    for(int k=0; k<size; k++)
    {
        temp=queue[k].get_cpu();
        process=temp.front();
        check=process.get_pid();
        if(check==number)
        {
            cout<<"Process found in a CPU and being erased..."<<endl;
            float cputime=process.get_burst();
            float burstime=process.get_average();
            queue[k].clear_cpu();
            cout<<"Process information:"<<endl;
            cout<<"PID: "<<number<<endl<<"Acc CPU time: "<<cputime<<endl<<"Average burst time: "<<burstime<<endl;
            cout<<"Process killed"<<endl<<endl;
            return true;//ends if PID is found in CPU and returns true
        }
    }
    return false;
}

int main()
{
    cout << "Sys gen starting..."<<endl;
    cout<<"Please enter the amount of CPUs (between 1 and 9)"<<endl;
    int cpu;
    cin>>cpu;
    while(cpu<1 || cpu>9)
    {
        cout<<"Invalid value, please re-enter amount:"<<endl;
        cin>>cpu;
    }

    cout<<"Enter amount of PRINTERs:"<<endl;
    int pr;
    cin>>pr;
    cout<<"Enter amount of  DISKs:"<<endl;
    int di;
    cin>>di;
    cout<<"Enter amount of CD/RWs:"<<endl;
    int cd;
    cin>>cd;
    int devices=(cpu*2)+pr+di+cd;//amount of devices(queues and CPU's)
    int PID=0;
    int PCB=0;
    vector<rq> RQ;  //vector of ready queues
    vector<rq> PQ; //vector of printer queues
    vector<rq> DQ; //vector of disk queues
    vector<rq> CQ; //vector of CD/RW queues

    load_queue(RQ, cpu);
    load_queue(PQ, pr); //load printer queues to PQ vector
    load_queue(DQ, di); // ...
    load_queue(CQ, cd); // ...


    cout << "Running section..." <<endl<< endl;
    cout<<"Start inputting commands; To terminate program press E or e at any time:"<<endl;
    while(true)
    {
        string device;//for name of device
        string enter;//for input
        cin>>enter;
        int correspond=0;
        int smaller;
        char num11=enter[0];//1st position character
        char input=enter[1];//2nd position  char
        char num=enter[2];//3rd position    char
        int num1=num11 -'0';//1st position integer
        int n=num -'0';//3rd position       int
        int inp=input - '0';//2nd position  int
        int empty;

        /*creates a new process and puts it into emptiest Ready Queue*/
        if(num11=='A')
        {
            smaller=get_smaller_queue_pos(RQ);  //determines which ready queue has less processes 
            RQ[smaller].create_process(smaller, PID, PCB);
            PID++;
            PCB++;
            if(RQ[smaller].get_cpu().size() == 0)
            {
                RQ[smaller].cpu();
            }
        }

        /*terminates a process from a particular CPU*/
        else if(input=='t') 
        {
            if(num1>0 && num1<=cpu)
            {
                RQ[num1-1].terminate();
                PCB--;
                RQ[num1-1].cpu();
            }
            else 
            {
                cout<<"Invalid entry"<<endl;
            }
        }

        /*Prints out a snapshot of a particular device Q or the ready queues*/
        else if(num11 == 'S')
        {
            cout << "Select a queue: "<<endl;
            char sele;
            cin >> sele;
            switch(sele)
            {
                case 'p':
                    if(pr==0)
                    {
                        cout<<"There are no printer queues created."<<endl;
                    }
                    else
                    {
                        device="Printer";
                        cout<<"A snapshot of your "<<device<<" queues:"<<endl<<"PCB\tPID\tLENGTH\tLOCATION\tFILE NAME\tUsed CPU time(ms)\tAverage Burst time(ms)"<<endl;
                        for(int i = 0; i < PQ.size(); i++)
                        {
                            cout<<device<<" "<<i+1<<":"<<endl;
                            PQ.at(i).snapshot(device);
                        }
                    }
                    break;
                case 'r':
                    cout<<endl<<"___A Snapshot of your Ready Queue(s)___"<<endl;
                    for(int i = 0; i < RQ.size(); i++)
                    {
                        cout<<"Ready queue "<<i+1<<":"<<endl;
                        RQ[i].snapshot();
                    }
                        break;
                case 'd':
                    if(di==0)
                    {
                        cout<<"There are no disk queues created."<<endl;
                    }
                    else
                    {
                        device="Disk";
                        cout<<"A snapshot of your "<<device<<" queues:"<<endl<<"PCB\tPID\tLENGTH\tLOCATION\tFILE NAME\tUsed CPU time(ms)\tAverage Burst time(ms)"<<endl;
                        for(int i = 0; i < PQ.size(); i++)
                        {
                            cout<<device<<" "<<i+1<<":"<<endl;
                            DQ.at(i).snapshot(device);
                        }                       
                    }
                    break;
                case 'c':
                    if(cd==0)
                    {
                        cout<<"There are no cd/rw queues created."<<endl;
                    }
                    else
                    {
                        device="Cd/rw";
                        cout<<"A snapshot of your "<<device<<" queues:"<<endl<<"PCB\tPID\tLENGTH\tLOCATION\tFILE NAME\tUsed CPU time(ms)\tAverage Burst time(ms)"<<endl;
                        for(int i = 0; i < PQ.size(); i++)
                        {
                            cout<<device<<" "<<i+1<<":"<<endl;
                            CQ.at(i).snapshot(device);
                        }
                    }
                    break;
                default:
                    cout << "No such queue; wrong option." << endl;
                    break;
            }
        }
        /*moves a process from a particular CPU into a particular printer queue*/
        else if(input=='p')
        {
            if(n>pr)
            {
                cout<<"You are exceding the amount of queues available for this device."<<endl;
            }
            else  
            {

                /*start of push */
                vector <proc> temp1;
                int big;
                temp1=RQ[num1-1].get_cpu();             
                if (temp1.empty())
                {
                    big=get_biggest_queue_pos(RQ);
                    temp1=RQ[big].get_front();
                    temp1.at(0).change_q(num1-1);
                    RQ[num1-1].enter_to_rq(temp1.front());
                    RQ[num1-1].cpu();
                }
                /*end of push */

                int ind=1;// to determines it's a printer when asking for parameters
                vector <proc> temp;
                temp=RQ[num1-1].get_cpu();
                int nn=temp.at(0).get_first();//to determine if process already has parameters (if nn=1)
                if(nn==0)
                {
                    RQ[num1-1].get_info(ind);//input process parameters
                    RQ[num1-1].bur_info();
                    temp=RQ[num1-1].get_cpu();
                }
                else
                {
                    RQ[num1-1].bur_info();
                    temp=RQ[num1-1].get_cpu();
                }
                RQ[num1-1].clear_cpu();
                proc te(0,0,0);
                te=temp.front();
                PQ[n-1].enter_to_rq(te);
            }
        }
        /*moves a process from a particular CPU into a particular disk queue*/
        else if(input=='d')
        {
            if(n>di)
            {
                cout<<"You are exceding the amount of queues available for this device."<<endl;
            }
            else 
            {   
                /*start of push */
                vector <proc> temp1;
                int big;
                temp1=RQ[num1-1].get_cpu();             
                if (temp1.empty())
                {
                    big=get_biggest_queue_pos(RQ);
                    temp1=RQ[big].get_front();
                    temp1.at(0).change_q(num1-1);
                    RQ[num1-1].enter_to_rq(temp1.front());
                    RQ[num1-1].cpu();
                }
                /*end of push */

                int ind=0;// to determine it's a printer when asking for parameters
                vector <proc> temp;
                temp=RQ[num1-1].get_cpu();
                int nn=temp.at(0).get_first();//to determine if process already has parameters (if nn=1)
                if(nn==0)
                {
                    RQ[num1-1].get_info(ind);//input process parameters
                    RQ[num1-1].bur_info();
                    temp=RQ[num1-1].get_cpu();
                }
                else
                {
                    RQ[num1-1].bur_info();
                    temp=RQ[num1-1].get_cpu();
                }               
                RQ[num1-1].clear_cpu();
                proc te(0,0,0);
                te=temp.front();
                DQ[n-1].enter_to_rq(te);
            }
        }

        /*moves a process from a particular CPU into a particular cd/rw queue*/
        else if(input=='c')
        { 
            if(n>pr)
            {
                cout<<"You are exceding the amount of queues available for this device."<<endl;
            }
            else  
            {
                /*start of push */
                vector <proc> temp1;
                int big;
                temp1=RQ[num1-1].get_cpu();             
                if (temp1.empty())
                {
                    big=get_biggest_queue_pos(RQ);
                    temp1=RQ[big].get_front();
                    temp1.at(0).change_q(num1-1);
                    RQ[num1-1].enter_to_rq(temp1.front());
                    RQ[num1-1].cpu();
                }
                /*end of push */


                int ind=0;// to determine it's a printer when asking for parameters
                vector <proc> temp;
                temp=RQ[num1-1].get_cpu();
                int nn=temp.at(0).get_first();//to determine if process already has parameters (if nn=1)
                if(nn==0)
                {
                    RQ[num1-1].get_info(ind);//input process parameters
                    RQ[num1-1].bur_info();
                    temp=RQ[num1-1].get_cpu();
                }
                else
                {
                    RQ[num1-1].bur_info();
                    temp=RQ[num1-1].get_cpu();
                }
                RQ[num1-1].clear_cpu();
                proc te(0,0,0);
                te=temp.front();
                CQ[n-1].enter_to_rq(te);
            }
        }
        /*moves a process from a particular printer queue to it's ready queue*/
        else if(num11=='P')
        {
            if(enter=="P")
            {
                cout<<"missing values"<<endl;
            }
            else if(inp>pr)
            {
                cout<<"Invalid input."<<endl;
            }
            else if(PQ[inp-1].tamano()==0)
            {
                cout<<"There are no more processes in the Queue"<<endl;
            }
            else
            {
                vector<proc> temp;
                temp=PQ[inp-1].get_device();
                proc te(0,0,0);
                te=temp.front();
                correspond=te.get_q();
                RQ[correspond].enter_to_rq(te);
            }
        }
        /*moves a process from a particular disk queue to it's ready queue*/
        else if(num11=='D')
        {
            if(enter=="D")
            {
                cout<<"missing values"<<endl;
            }
            else if(inp>di)
            {
                cout<<"Invalid input."<<endl;
            }
            else if(DQ[inp-1].tamano()==0)
            {
                cout<<"There are no more processes in the Queue"<<endl;
            }
            else
            {
                vector<proc> temp;
                temp=DQ[inp-1].get_device();
                correspond=DQ[inp-1].queue();
                proc te(0,0,0);
                te=temp.front();
                correspond=te.get_q();
                RQ[correspond].enter_to_rq(te);
            }
        }
        /*moves a process from a particular cr/rw queue to it's ready queue*/
        else if(num11=='C')
        {
            if(enter=="C")
            {
                cout<<"missing values"<<endl;
            }
            else if(inp>cd)
            {
                cout<<"Invalid input."<<endl;
            }
            else if(CQ[inp-1].tamano()==0)
            {
                cout<<"There are no more processes in the Queue"<<endl;
            }
            else
            {
                vector<proc> temp;
                temp=CQ[inp-1].get_device();
                correspond=PQ[inp-1].queue();
                proc te(0,0,0);
                te=temp.front();
                correspond=te.get_q();
                RQ[correspond].enter_to_rq(te);
            }
        }
        /*terminates program*/
        else if(num11=='E' || num11=='e')
        {
            return 0;
        }

        /*Moves process from CPU to it's ready queue*/
        else if(input=='T')
        {
            if(enter=="T")
            {
                    cout<<"missing values"<<endl;
            }
            else if (num1>cpu)
            {
                cout<<"Invalid entry, no such CPU."<<endl;
            }
            else if (num1==0)
            {
                cout<<"Invalid entry, no such CPU."<<endl;
            }
            else 
            {
                vector<proc> temp;
                temp=RQ[num1-1].get_cpu();
                RQ[num1-1].cpu_clear();
                proc te(0,0,0);
                te=temp.at(0);
                RQ[num1-1].enter_to_rq(te);
                RQ[num1-1].clear_cpu();
            }
        }
        /*Kills a process determined by it's PID*/
        else if(num11=='K')
        {
        if(enter=="K")
        {
            cout<<"missing values"<<endl;
        }
        else
        {   
            /*Borrowed code to convert a string into an int*/       
            /*converts the rest of numbers into a separate string*/
            int n=enter.length();
            char number[n-1];
            for (int j=0; j<n; j++)
            {
                number[j]=enter[j+1];
            }
            string final=number;
            /*end of conversion, final= string containing PID*/

            /*convert the string final into an int*/
            int id;
            stringstream test(final);
            test>>id;
            /*end of conversion, id= int containing PID*/
            /*End of Borrowed code to convert a string into an int*/

            if (id > PID)   
            {
                cout<<"Invalid PID, no such process"<<endl;
            }
            else
            {
                /*Check if PID is in a Q or CPU and delete process*/
                bool buscar;
                buscar=get_pid_process(RQ, id);
                if(buscar==false)
                {
                    buscar=get_pid_process(PQ, id);
                }
                if(buscar==false)
                {
                    buscar=get_pid_process(DQ, id);
                }
                if(buscar==false)
                {
                    buscar=get_pid_process(CQ, id);
                }
                if(buscar==false)
                {
                    cout<<"Process not found."<<endl;
                }
            }
        }
        }

        /*If invalid input*/
        else
        {
            cout<<"Invalid input, re-enter command."<<endl<<endl;
        }
    }
    return 0;
}