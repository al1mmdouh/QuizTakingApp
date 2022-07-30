#include <iostream>
#include <ctime>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>

using namespace std;
void random (int Arr[])
{
// The Function generates array with size of 4 with randomly unique numbers to random the answers in the quiz
    srand(time(0)) ;
    int x=0,flag=0;
    int arr[4];
    arr[0]=rand()%4 ;
    int counter1= 1 ;
    while(counter1!=4)
    {
        x=rand()%4 ;
        for(int i=0; i<4; i++)
        {
            if(x==arr[i])
            {
                flag=0;
                break;
            }
            else
            {
                flag=1;
            }
        }
        if (flag==1)
        {
            arr[counter1]=x;
            counter1++;
        }
    }
    for(int i =0 ; i<4 ; i++)
    {
        Arr[i]=arr[i];
    }
}
void PrintIntro()
{
    cout << "******************************************************************" << endl;
    cout << "              Welcome to the Quiz game program V2.0!              " << endl;
    cout << "******************************************************************" << endl;
}
class User
{
protected:
    string Password;
    string FirstName;
    string LastName;
    string UserName;
public :
    string getUsername()
    {
        return UserName;
    }
    string getPassword()
    {
        return Password;
    }
    string getFirstname()
    {
        return FirstName;
    }
    string getLastname()
    {
        return LastName;
    }
    void setFirstname(string s)
    {
        FirstName = s;
    }
    void setLastname(string s)
    {
        LastName = s;
    }
    void setUsername(string s)
    {
        UserName = s;
    }
    void setPassword(string s)
    {
        Password = s;
    }
};
class Admin :public User
{
private:
    string role = "admin";
public :
    Admin() {};
    Admin(string Un,string P,string Fn,string Ln)
    {
        UserName = Un;
        Password = P;
        FirstName = Fn;
        LastName = Ln;
    }
    string getRole()
    {
        return role;
    }
    bool operator==(vector<Admin> &A)
    {
        int ch=0;
        for(int i=0; i<A.size(); i++)
        {
            if(A[i].UserName==UserName)
            {
                return true;
                ch=1;
            }
        }
        if(ch==1)
            return false;

    }

};
class Player :public User
{
private:
    string role = "player";
    vector<int> MCQ_Score;
    vector<int> TF_Score;
    vector<int> Complete_Score;
    vector<int> Score;
    int num_of_quizzes=0;
public :
    struct last
    {
        string QTitle[3];
        string Answer[3];
        string right_Answer[3];
        int score[3];
        int total_score;
    };
    last quiz;
    vector <last> details;
    double sum_mcq=0.0,sum_tf=0.0,sum_com=0.0,sum_sc=0.0;
    int high=0,low=1000;
    Player() {};
    Player(string Un,string P,string Fn,string Ln)
    {
        UserName = Un;
        Password = P;
        FirstName = Fn;
        LastName = Ln;
    }
    string getRole()
    {
        return role;
    }
    bool operator==(vector<Player> &P)
    {
        int ch=0;
        for(int i=0; i<P.size(); i++)
        {
            if(P[i].UserName==UserName)
            {
                return true;
                ch=1;
            }
        }
        if(ch==1)
            return false;

    }
    void setMCQ_Score(int i)
    {
        MCQ_Score.push_back(i);
    }
    void setTF_Score(int i)
    {
        TF_Score.push_back(i);
    }
    void setComplete_Score(int i)
    {
        Complete_Score.push_back(i);
    }
    void setScore (int i)
    {
        Score.push_back(i);
    }
    int getSizeofSocres()
    {
        return Score.size();
    }
    int getScore(int i)
    {
        return Score[i];
    }
    void setNum()
    {
        num_of_quizzes++;
    }
    int getNum()
    {
        return num_of_quizzes;
    }
    double getAverage_mcq()
    {
        for(int i=0; i<MCQ_Score.size(); i++)
            sum_mcq=sum_mcq+MCQ_Score[i];
        double a;
        a=sum_mcq/num_of_quizzes;
        return a;
    }
    double getAverage_TF()
    {
        for(int i=0; i<TF_Score.size(); i++)
            sum_tf=sum_tf+TF_Score[i];
        double a;
        a=sum_tf/num_of_quizzes;
        return a;
    }
    double getAverage_sc()
    {
        for(int i=0; i<Score.size(); i++)
            sum_sc=sum_sc+Score[i];
        double a;
        a=sum_sc/num_of_quizzes;
        return a;
    }
    double getAverage_com()
    {
        for(int i=0; i<Complete_Score.size(); i++)
            sum_com=sum_com+Complete_Score[i];
        double a;
        a=sum_com/num_of_quizzes;
        return a;
    }
    int getHigh()
    {
        for(int i=0; i<Score.size(); i++)
            if(Score[i]>high)
                high=Score[i];
        return high;
    }
    int getLow()
    {
        for(int i=0; i<Score.size(); i++)
            if(Score[i]<low)
                low=Score[i];
        return low;
    }
};
int Login (vector <Admin> a,vector <Player> p,string s1,string s2,int &usernum)
{
    //to login to the Program
    int flag=0;
    for (int i =0 ; i<a.size(); i++)
    {
        if (s1==a[i].getUsername())
        {
            if(s2==a[i].getPassword())
            {
                flag=1;
                usernum=i;
            }
        }
    }
    if (flag==1)
        return flag;
    else
    {
        for (int i =0 ; i<p.size(); i++)
        {
            if (s1==p[i].getUsername())
            {
                if(s2==p[i].getPassword())
                {
                    usernum=i;
                    return flag=2;
                }
            }
        }
    }
    if (flag!=1||flag!=2)
        return flag=0;
}
class Question
{
    //That Class is for the MCQ Questions and rest of types will inherit the important attributes from it. That way will reduce number of classes and make the code easier.
protected:
    string QuestionTitle;
    string CorrectChoice;
    int ID;
private :
    string Choice2;
    string Choice3;
    string Choice4;
public:
    Question() {};
    Question(string QuestionTitle, string CorrectChoice, string Choice2, string Choice3, string Choice4,int ID)
    {
        this->QuestionTitle = QuestionTitle;
        this->CorrectChoice = CorrectChoice;
        this->Choice2 = Choice2;
        this->Choice3 = Choice3;
        this->Choice4 = Choice4;
        this->ID = ID;
    }
    int getID()
    {
        return ID;
    }
    string getQuestiontitle()
    {
        return QuestionTitle;
    }
    string getCorrectchoice()
    {
        return CorrectChoice;
    }
    string getChoice2()
    {
        return Choice2;
    }
    string getChoice3()
    {
        return Choice3;
    }
    string getChoice4()
    {
        return Choice4;
    }
    void setID(int s)
    {
        ID = s;
    }
    void setQuestiontitle(string s)
    {
        QuestionTitle = s;
    }
    void setCorrectchoice(string s)
    {
        CorrectChoice = s;
    }
    void setChoice2(string s)
    {
        Choice2 = s;
    }
    void setChoice3(string s)
    {
        Choice3 = s;
    }
    void setChoice4(string s)
    {
        Choice4 = s;
    }
    bool operator==(vector<Question> &Q)
    {
        int ch=0;
        for(int i=0; i<Q.size(); i++)
        {
            if(Q[i].QuestionTitle==QuestionTitle)
            {
                return true;
                break;
            }
        }
        if(ch==1)
            return false;

    }
    void readQuestionFromFile(string file_name,ifstream &file)
    {
        getline(file,QuestionTitle);
        getline (file,CorrectChoice);
        getline (file,Choice2);
        getline (file,Choice3);
        getline (file,Choice4);
    }

};

class TFQuestion:public Question
{
private :
    char CorrectChoice;
public:
    TFQuestion() {};
    TFQuestion(string QuestionTitle, char CorrectChoice,int ID)
    {
        this->QuestionTitle = QuestionTitle;
        this->CorrectChoice = CorrectChoice;
        this->ID = ID;
    }
    void setCorrectChoice (char s)
    {
        CorrectChoice =s;
    }
    char getCorrectchoice()
    {
        return CorrectChoice;
    }
    bool operator==(vector<TFQuestion> &Q)
    {
        int ch=0;
        for(int i=0; i<Q.size(); i++)
        {
            if(Q[i].QuestionTitle==QuestionTitle)
            {
                return true;
                break;
            }
        }
        if(ch==1)
            return false;

    }
    void readQuestionFromFile(string file_name,ifstream &file,int &i)
    {

        string cha;
        getline(file,QuestionTitle);
        getline (file,cha);
        if(cha[0]!='T'&&cha[0]!='F')
        {
            i=1;
        }
        CorrectChoice=cha[0];

    }
};
class Compelete_Question : public Question
{
public:
    Compelete_Question() {};
    Compelete_Question (string QuestionTitle, string CorrectChoice,int ID)
    {
        this->QuestionTitle = QuestionTitle;
        this->CorrectChoice = CorrectChoice;
        this->ID = ID;
    }
    bool operator==(vector<Compelete_Question> &Q)
    {
        int ch=0;
        for(int i=0; i<Q.size(); i++)
        {
            if(Q[i].QuestionTitle==QuestionTitle)
            {
                return true;
                break;
            }
        }
        if(ch==1)
            return false;

    }
    void readQuestionFromFile(string file_name,ifstream &file,int &i)
    {
        string checkingg;
        getline(file,QuestionTitle);
        getline(file,checkingg);
        if(checkingg=="\0")
        {
            i=1;
        }
        CorrectChoice=checkingg;
    }
};
int delete_question (vector <Question> &mcq,vector <TFQuestion> &tfq,vector<Compelete_Question>&cmq,int &id)
{
    bool chekk;
    //the function is going to look for the id in the three vectors of question types and if it finds the id  it deletes the question with it
    for(int z=0; z<mcq.size(); z++)
        if(mcq[z].getID()==id)
        {
            mcq.erase(mcq.begin()+(z));
            chekk=true;
            return 2;
        }
    if (chekk==false)
    {
        for(int z=0; z<tfq.size(); z++)
            if(tfq[z].getID()==id)
            {
                tfq.erase(tfq.begin()+(z));
                chekk=true;
                return 2;
            }
    }
    if (chekk==false)
    {
        for(int z=0; z<cmq.size(); z++)
            if(cmq[z].getID()==id)
            {
                cmq.erase(cmq.begin()+(z));
                chekk=true;
                return 2;
            }
    }
    if(chekk==false)
        return 1;

}
int Admin_Menu (vector <Admin> &a,vector <Player> &p,vector <Question> &mcq,vector <TFQuestion> &tfq,vector<Compelete_Question>&cmq,int &i,vector<string> &filenames)
{
    // That's Every thing the Admin is allowed to do
    int choice,del_id,QID;
    static int x=6;
    string newFName, newLName,newRole,newUName,newPass,file_name;
    string QType,QTitle,QCorrect,QChoice2,QChoice3,QChoice4;
    char choice_ch,QCorrect_h;
adminMenu:
    cout<<"welcome "<<a[i].getFirstname()<<" "<<a[i].getLastname()<<",  please choose from the following options:"<<endl;
    cout<<"[1] Switch accounts \n[2] Update your name\n[3] View all users\n[4] Add new user\n[5] View all questions"
        <<"\n[6] Add new question\n[7] Load questions from file \n[8] Exit the program"<<endl;
    cout<<"My Choice : ";
    if (cin.fail()){ //to prevent the cin errors
        cin.clear();
        cin.ignore(100,'\n');}
    cin>>choice;
    switch (choice)
    {
    case 1 :
        return 1;
        break;
    case 2 :
    {
        cout<< "Enter Your New First Name : ";
        cin >>newFName;
        cout<< "Enter Your New Last Name : ";
        cin >>newLName;
        a[i].setFirstname(newFName);
        a[i].setLastname(newLName);
        goto adminMenu;
    }
    case 3 :
    {
        cout << "Existing users in the system: "<<endl;
        cout<<"First name\t Last name\t Username\t Role"<<endl;
        for(int z=0; z<a.size(); z++)
        {
            cout<<a[z].getFirstname()<<"\t\t "<<a[z].getLastname()<<"\t\t "<<a[z].getUsername()<<"\t\t "<<a[z].getRole()<<endl;
        }
        for(int z=0; z<p.size(); z++)
        {
            cout<<p[z].getFirstname()<<"\t\t "<<p[z].getLastname()<<"\t\t "<<p[z].getUsername()<<"\t\t "<<p[z].getRole()<<endl;
        }
char_choice1:
        cout<<"Press [n] if you want to add a new user or [b] to go back to the main menu."<<endl;
        cin>>choice_ch;
        if(choice_ch=='n')
            goto adduser;
        else if (choice_ch=='b')
            goto adminMenu;
        else
        {
            cout<<"Wrong Choice,Try Again"<<endl;
            goto char_choice1;
        }
    }
    break;
    case 4 :
    {
adduser:
        cout<<"Enter the Role of The New User : ";
        cin>>newRole;
        if (newRole=="Admin")
        {
            Admin newAdmin;
            cout<<"Enter The First Name of The User : ";
            cin>>newFName ;
            newAdmin.setFirstname(newFName);
            cout<<"Enter The Last Name of The User : ";
            cin>>newLName;
            newAdmin.setLastname(newLName);
            cout<<"Enter The User name of The User : ";
            cin>>newUName;
            newAdmin.setUsername(newUName);
            cout<<"Enter The Password of The User : ";
            cin>>newPass;
            newAdmin.setPassword(newPass);
            if(newAdmin==a)
            {
                cout<<"Repeated Username"<<endl;
                goto adduser;
            }
            a.push_back(newAdmin);
        }
        else if (newRole=="Player")
        {
            Player newPlayer;
            cout<<"Enter The First Name of The User : ";
            cin>>newFName ;
            newPlayer.setFirstname(newFName);
            cout<<"Enter The Last Name of The User : ";
            cin>>newLName;
            newPlayer.setLastname(newLName);
            cout<<"Enter The User name of The User : ";
            cin>>newUName;
            newPlayer.setUsername(newUName);
            cout<<"Enter The Password of The User : ";
            cin>>newPass;
            newPlayer.setPassword(newPass);
            if(newPlayer==p)
            {
                cout<<"Repeated Username"<<endl;
                goto adduser;
            }
            p.push_back(newPlayer);
        }
        else {cout<<"Wrong Type"<<endl;
              goto adduser;}
        goto adminMenu;
    }
    break;
    case 5 :
    {
        int num_of_questions = mcq.size()+tfq.size()+cmq.size();
        cout<<"Number of questions available: "<<num_of_questions<<"\n"<<"---------------------------------------------------"<<endl;
        cout<<"MC Questions list (Total: "<<mcq.size()<<" Questions)\n---------------------------------------------------"<<endl;
        for (int z=0; z<mcq.size(); z++)
        {
            cout<<"["<<z+1<<"] "<<"(ID: "<<mcq[z].getID()<<") "<<mcq[z].getQuestiontitle()<<endl<<"     ";
            cout<<"["<<char(97)<<"] *"<<mcq[z].getCorrectchoice()<<"\t\t";
            cout<<"["<<char(98)<<"] "<<mcq[z].getChoice2()<<"\t\t";
            cout<<"["<<char(99)<<"] "<<mcq[z].getChoice3()<<"\t\t";
            cout<<"["<<char(100)<<"] "<<mcq[z].getChoice4()<<"\t\t"<<endl;
        }
        cout<<"----------------------------------------------------\nTF Questions list (Total: "<<tfq.size()<<" Questions)\n";
        cout<<"---------------------------------------------------\n";
        for (int z=0; z<tfq.size(); z++)
        {
            cout<<"["<<z+1<<"] "<<"(ID: "<<tfq[z].getID()<<") "<<tfq[z].getQuestiontitle();
            cout<<" (Answer: "<<tfq[z].getCorrectchoice()<<" )\n";
        }
        cout<<"----------------------------------------------------\nCompelete Questions list (Total: "<<cmq.size()<<" Questions)\n";
        cout<<"---------------------------------------------------\n";
        for (int z=0; z<cmq.size(); z++)
        {
            cout<<"["<<z+1<<"] "<<"(ID: "<<cmq[z].getID()<<") "<<cmq[z].getQuestiontitle();
            cout<<" (Answer: "<<cmq[z].getCorrectchoice()<<" )\n";
        }
        cout<<endl<<"-------------------------------------------------------------------------------------\n";
char_choice2:
        cout<<"Press [d] and the question ID if you want to delete a question (Example: d 2)\n"
            <<"Press [b] if you want to go back to the main menu\n"<<endl;
        cin>>choice_ch;
        if(choice_ch=='b')
            goto adminMenu;
        else if (choice_ch=='d')
        {
id_choice:
            cin>>del_id;
            int v=delete_question(mcq,tfq,cmq,del_id);
            if(v==1)
            {
                cout<<"Wrong ID, Try Again"<<endl;
                goto id_choice;
            }
            if (v==2)
                goto adminMenu;
        }
        else
        {
            cout<<"Wrong Answer"<<endl;
            goto char_choice2;
        }

    }
    break;
    case 6 :
    {
Type :
        cout<<"Enter Your Question Type (MCQ/TF/Complete) : ";
        cin>>QType;
        if (QType == "MCQ")
        {
            x++;
EnterQuestion1:
            Question Question1;
            cout<<"Enter The Question Title : ";
            cin.ignore();
            getline(cin,QTitle);
            Question1.setQuestiontitle(QTitle);
            cout<<"Enter The Correct Answer : ";
            getline(cin,QCorrect);
            Question1.setCorrectchoice(QCorrect);
choice2:
            cout<<"Enter Choice 2 : ";
            getline(cin,QChoice2);
            if(QChoice2==Question1.getCorrectchoice())
            {
                cout<<"Reapeated Answer"<<endl;
                goto choice2;
            }
            Question1.setChoice2(QChoice2);
choice3:
            cout<<"Enter Choice 3 : ";
            getline(cin,QChoice3);
            if(QChoice3==Question1.getCorrectchoice()||QChoice3==Question1.getChoice2())
            {
                cout<<"Reapeated Answer"<<endl;
                goto choice3;
            }
            Question1.setChoice3(QChoice3);
choice4:
            cout<<"Enter Choice 4 : ";
            getline(cin,QChoice4);
            if(QChoice4==Question1.getCorrectchoice()||QChoice4==Question1.getChoice2()||QChoice4==Question1.getChoice3())
            {
                cout<<"Reapeated Answer"<<endl;
                goto choice4;
            }
            Question1.setChoice4(QChoice4);
            QID=x;
            Question1.setID(QID);
            if(Question1== mcq)
            {
                cout<<"Repeated Question"<<endl;
                goto EnterQuestion1;
            }
            mcq.push_back(Question1);
        }
        else if (QType=="TF")
        {
            x++;
            TFQuestion Question1;
EnterQuestion2 :
            cout<<"Enter The Question Title : ";
            cin.ignore();
            getline(cin,QTitle);
            Question1.setQuestiontitle(QTitle);
            cout<<"Enter The Correct Answer : ";
            cin>>QCorrect_h;
            if(QCorrect_h!='T'&&QCorrect_h!='F')
            {
                cout<<"Wrong Entry"<<endl;
                goto EnterQuestion2;
            }
            Question1.setCorrectChoice(QCorrect_h);
            QID=x;
            Question1.setID(QID);
            if(Question1== tfq)
            {
                cout<<"Repeated Question"<<endl;
                goto EnterQuestion2;
            }
            tfq.push_back(Question1);
        }
        else if (QType =="Complete")
        {
            x++;
            Compelete_Question Question1;
EnterQuestion3 :
            cout<<"Enter The Question Title : ";
            cin.ignore();
            getline(cin,QTitle);
            Question1.setQuestiontitle(QTitle);
            cout<<"Enter The Correct Answer : ";
            getline(cin,QCorrect);
            Question1.setCorrectchoice(QCorrect);
            QID=x;
            Question1.setID(QID);
            if(Question1== cmq)
            {
                cout<<"Repeated Question"<<endl;
                goto EnterQuestion3;
            }
            cmq.push_back(Question1);
        }
        else
        {
            cout<<"Wrong Type"<<endl;
            goto Type;
        }
        goto adminMenu;

    }
    break;
    case 7 :
    {
openfile :
        cout<<"Enter File Name Example (file.txt) : ";
        cin>>file_name;
        int flagg=1;
        for(int q=0; q<filenames.size(); q++)
        {
            if(file_name==filenames[q])
            {
                cout<<"This File is already Entered"<<endl;
                flagg=0;
                break;
            }
            else
                flagg=1;
        }
        if (flagg==0)
        {
            goto adminMenu;
        }
        else if(flagg==1)
        {
            filenames.push_back(file_name);
            string line;
            ifstream file;
            file.open(file_name);
            if(file.is_open()==false)
            {
                cout<<"Wrong file name"<<endl;
                goto openfile;
            }
            while(getline(file,line))
            {
                if(line=="MCQ")
                {
                    x++;
                    Question question2;
                    question2.readQuestionFromFile(file_name,file);
                    if((question2== mcq)==false)
                    {
                        question2.setID(x);
                        mcq.push_back(question2);
                    }
                }
                if(line=="TF")
                {
                    int error_check;
                    x++;
                    TFQuestion question2;
                    question2.readQuestionFromFile(file_name,file,error_check);
                    if(error_check==1)
                    {
                        cout<<"There is an Error in the loading process"<<endl;
                        break;
                    }
                    if((question2== tfq)==false)
                    {
                        question2.setID(x);
                        tfq.push_back(question2);
                    }
                }
                if(line=="COMPLETE")
                {
                    int error_check;
                    x++;
                    Compelete_Question question2;
                    question2.readQuestionFromFile(file_name,file,error_check);
                    if(error_check==1)
                    {
                        cout<<"There is an Error in the loading process"<<endl;
                        break;
                    }
                    if((question2== cmq)==false)
                    {
                        question2.setID(x);
                        cmq.push_back(question2);
                    }
                }
                if(line!="MCQ"&&line!="TF"&&line!="COMPLETE")
                {
                    cout<<"There is an Error in the loading process"<<endl;
                    break;
                }
            }
            cout<<"Done loading Your File."<<endl;
            goto adminMenu;
        }
    }
    break;
    case 8 :
        return 0;
        break;
    default :
    {
        cout<<"Wrong Entery"<<endl;
        goto adminMenu;
    }
    }
}
void NewQuiz (vector <Player> &p,vector <Question> &mcq,vector <TFQuestion> &tfq,vector<Compelete_Question>&cmq,int &i)
{
    //the function generates new quiz
    srand(time(0)) ;
    int ran,ran2,ran3,z=0,rand_arr_options[5],a,c; // the a , c to connect the entered char with the correct answer in MCQ Questions
    int MCQ_C=0,TF_C=0,CM_C=0,score; //score calculating variables
    char answer;
    string answer2;
    ran = rand() % (mcq.size());
    p[i].quiz.QTitle[0]=mcq[ran].getQuestiontitle();
    cout<<"["<<z+1<<"] "<<mcq[ran].getQuestiontitle()<<endl<<"     ";
    random(rand_arr_options);
    int b=1;
    int y=0;
    for(int c=0; c<4; c++)
    {
        cout<<"["<<char(97+c)<<"] ";
        if(rand_arr_options[c]==0)
        {
            cout<<mcq[ran].getCorrectchoice()<<"\t\t";
            p[i].quiz.right_Answer[0]=mcq[ran].getCorrectchoice();
            a=b;
        }
        if(rand_arr_options[c]==1)
            cout<<mcq[ran].getChoice2()<<"\t\t";
        if(rand_arr_options[c]==2)
            cout<<mcq[ran].getChoice3()<<"\t\t";
        if(rand_arr_options[c]==3)
            cout<<mcq[ran].getChoice4()<<"\t\t";
        b++;
    }
    cout<<endl;
answer :
    cin>>answer;
    if (answer=='a') // to identify the answer and connect it to the right one
        c=1;
    else if (answer=='b')
        c=2;
    else if (answer=='c')
        c=3;
    else if (answer=='d')
        c=4;
    else
    {
        cout<<"choose right option"<<endl;
        goto answer;
    }
    if (rand_arr_options[c-1]==0) //these steps to store the player's answer to use it in show the last 2 details
        p[i].quiz.Answer[0]=mcq[ran].getCorrectchoice();
    else if (rand_arr_options[c-1]==1)
        p[i].quiz.Answer[0]=mcq[ran].getChoice2();
    else if (rand_arr_options[c-1]==2)
        p[i].quiz.Answer[0]=mcq[ran].getChoice3();
    else if (rand_arr_options[c-1]==3)
        p[i].quiz.Answer[0]=mcq[ran].getChoice4();
    if (c==a)
    {
        cout<<"Correct"<<endl;
        p[i].setMCQ_Score(1);
        MCQ_C=1;
        p[i].quiz.score[0]=1;
    }
    else
    {
        cout<<"Wrong"<<endl;
        p[i].setMCQ_Score(0);
        p[i].quiz.score[0]=0;
    }
    z++;
    ran2 = rand() % tfq.size();
    cout<<"["<<z+1<<"] "<<tfq[ran2].getQuestiontitle()<<endl;
    p[i].quiz.QTitle[1]=tfq[ran2].getQuestiontitle();
    p[i].quiz.right_Answer[1]=tfq[ran2].getCorrectchoice();
tfq_Answer :
    cin>>answer;
    p[i].quiz.Answer[1]=answer;
    if(answer=='T'||answer=='F')
    {
        if(answer==tfq[ran2].getCorrectchoice())
        {
            cout<<"Correct"<<endl;
            p[i].setTF_Score(2);
            p[i].quiz.score[1]=2;
            TF_C=2;
        }
        else
        {
            cout<<"Wrong"<<endl;
            p[i].setTF_Score(0);
            p[i].quiz.score[1]=0;
        }
    }
    else
    {
        cout<<"Invalid Answer,Try Again"<<endl;
        goto tfq_Answer;
    }
    ran3 = rand ()% cmq.size();
    cout<<"["<<z+1<<"] "<<cmq[ran3].getQuestiontitle()<<endl;
    p[i].quiz.QTitle[2]=cmq[ran3].getQuestiontitle();
    p[i].quiz.right_Answer[2]=cmq[ran3].getCorrectchoice();
    cin>>answer2;
    p[i].quiz.Answer[2]=answer2;
    if(answer2==cmq[ran3].getCorrectchoice())
    {
        cout<<"Correct"<<endl;
        p[i].setComplete_Score(3);
        p[i].quiz.score[2]=3;
        CM_C=3;
    }
    else
    {
        cout<<"Wrong"<<endl;
        p[i].setComplete_Score(0);
        p[i].quiz.score[2]=0;
    }

    score = CM_C+TF_C+MCQ_C; //the score calculating equation
    p[i].setScore(score);
    p[i].quiz.total_score=score;
    p[i].details.push_back(p[i].quiz);
    cout<<"Your Score is : "<<score<<" / 6"<<endl;


}

int Player_Menu (vector <Player> &p,vector <Admin> &a,vector <Question> &mcq,vector <TFQuestion> &tfq,vector <Compelete_Question> &cmq, int &i)
{
    //That's everything the player is allowed to do
    int choice;
    string newFName,newLName;
    int static num_of_quiz=0;
playerMenu :
    cout<<"Welcome "<<p[i].getFirstname()<<" "<<p[i].getLastname()<<",   please choose from the following options:"<<endl;
    cout<<"[1] Switch Accounts \n[2] Update Your Name \n[3] Start New Quiz \n[4] Display all your Scores \n[5] Display Your Statistics"
        <<"\n[6] Display the details of your last 2 quizzes\n[7] Exit the program"<<endl;
    cout<< "My Choice : ";
    if (cin.fail()){ //to prevent the cin errors
        cin.clear();
        cin.ignore(100,'\n');}
    cin>>choice;
    switch (choice)
    {
    case 1 :
        return 1;
        break;
    case 2 :
    {
        cout<< "Enter Your New First Name : ";
        cin >>newFName;
        cout<< "Enter Your New Last Name : ";
        cin >>newLName;
        p[i].setFirstname(newFName);
        p[i].setLastname(newLName);
        goto playerMenu;
    }
    break;
    case 3 :
    {
        p[i].setNum();
        num_of_quiz++;
        NewQuiz(p,mcq,tfq,cmq,i);
        goto playerMenu;
    }
    break;
    case 4 :
    {
        if(p[i].getNum()==0)
        {
            cout<<"No Quizzes Taken"<<endl;
            goto playerMenu;
        }
        int Size;
        Size=p[i].getSizeofSocres();
        cout<<"Number of Quizzes Taken : "<<num_of_quiz<<endl;
        cout<<"Your Scores : "<<endl;
        for(int a=0; a<Size; a++)
        {
            cout<<"["<<a+1<<"] "<<p[i].getScore(a)<<"/ 6 "<<endl;
        }
        goto playerMenu;
    }
    break;
    case 5 :
    {
        if(p[i].getNum()==0)
        {
            cout<<"No Quizzes Taken"<<endl;
            goto playerMenu;
        }
        cout<<"Your score statistics per quiz:\n";
        cout<<"\t- Number of Quizzes taken: "<<p[i].getNum()<<endl;
        cout<<"\t- Highest quiz score: "<<p[i].getHigh()<<"/6"<<endl;
        cout<<"\t- Lowest quiz score: "<<p[i].getLow()<<"/6"<<endl;
        cout<<"\t- Average quiz score: "<<p[i].getAverage_sc()<<"/6"<<endl;
        cout<<"Your score statistics per question type: \n";
        cout<<"\t- Number of MC questions: "<<p[i].getNum()<<endl;
        cout<<"\t- Number of TF questions: "<<p[i].getNum()<<endl;
        cout<<"\t- Number of Complete questions: "<<p[i].getNum()<<endl;
        cout<<"\t- Average grade for MC questions: "<<p[i].getAverage_mcq()<<"/1"<<endl;
        cout<<"\t- Average grade for TF questions: "<<p[i].getAverage_TF()<<"/2"<<endl;
        cout<<"\t- Average grade for Complete questions: "<<p[i].getAverage_com()<<"/3"<<endl;
        cout<<"Press [b] if you want to go back to the main menu or [e] to exit"<<endl;
        char answerr;
answerr :
        cin>>answerr;
        if(answerr=='b')
            goto playerMenu;
        else if (answerr='e')
            return 0;
        else
        {
            cout<<"invalid Choice"<<endl;
            goto answerr;
        }
    }
    break;
    case 6 :
    {
        if(p[i].getNum()<2)
        {
            cout<<"Not Enough Quizzes Taken"<<endl;
            goto playerMenu;
        }
        int s=p[i].details.size();
        cout<<"\t-For the Quiz before the last : "<<endl;
        for (int t=0; t<3; t++)
        {
            cout<<"The Question: "<<p[i].details[s-2].QTitle[t]<<endl;
            cout<<"The Right Answer: "<<p[i].details[s-2].right_Answer[t]<<endl;
            cout<<"The Answer: "<<p[i].details[s-2].Answer[t]<<endl;
            cout<<"The Score: "<<p[i].details[s-2].score[t]<<endl;
        }
        cout<<"The Total Score : "<<p[i].details[s-2].total_score<<endl;
        cout<<"------------------------------------------------\n";
        cout<<"\t-For the last Quiz : "<<endl;

        for (int q=0; q<3; q++)
        {
            cout<<"The Question: "<<p[i].details[s-1].QTitle[q]<<endl;
            cout<<"The Right Answer: "<<p[i].details[s-1].right_Answer[q]<<endl;
            cout<<"The Answer: "<<p[i].details[s-1].Answer[q]<<endl;
            cout<<"The Score: "<<p[i].details[s-1].score[q]<<endl;
        }
        cout<<"The Total Score : "<<p[i].details[s-1].total_score<<endl;
        cout<<"-----------------------------------------------\n";
    }
    goto playerMenu;
    break;
    case 7 :
        return 0;
        break;
    default :
    {
        cout<<"Wrong Entery"<<endl;
        goto playerMenu;
    }
    }
}
int main()
{
    vector<string> filenames;
    int usernum; //That number will represent the number of the index of the player or admin that logged in inside the vector
    vector <Admin> admins;
    Admin admin1("Admin","admin","User","user");
    admins.push_back(admin1);
    vector <Player> players;
    Player player1 ("Player","player","User","user");
    players.push_back(player1);
    vector <Question> MCQ;
    Question q1("Which one of the following is a flightless bird?","emu","duck","hen","swan",1);
    Question q2("Which is the capital of Egypt?","Cairo","Alex","Oman","Luxor",2);
    MCQ.push_back(q1);
    MCQ.push_back(q2);
    vector <TFQuestion> TFQ;
    TFQuestion q3(" A swan is a flightless bird",'F',3);
    TFQuestion q4("An emu is a flightless bird",'T',4);
    TFQ.push_back(q3);
    TFQ.push_back(q4);
    vector <Compelete_Question> CMQ;
    Compelete_Question q5("Hundred-year war was fought between ... and England.","France",5);
    Compelete_Question q6("The branch of science the studies cells is called ... .","Cytology",6);
    CMQ.push_back(q5);
    CMQ.push_back(q6);
    PrintIntro();
login :
    string username,password;
    cout<<"please enter your username : ";
    cin>>username;
    cout<<"please enter your password : ";
    cin>>password;
    int f = Login(admins,players,username,password,usernum);// to complete the login and see if the logged in user is admin or player or it's invalid login
    if (f==1)
    {
        int r = Admin_Menu(admins,players,MCQ,TFQ,CMQ,usernum,filenames);
        if (r==1)
            goto login; // to switch accounts
        else if (r==0)
            return 0; // to exit the program
    }
    else if (f==2)
    {
        int r1 = Player_Menu(players,admins,MCQ,TFQ,CMQ,usernum);
        if (r1==1)
            goto login; // to switch accounts
        else if (r1==0)
            return 0; // to exit prpgram
    }
    else
    {
        cout<<"Invalid Login"<<endl;
        goto login;
    } // to go back to the login
    return 0;
}
