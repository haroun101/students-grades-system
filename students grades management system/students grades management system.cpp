/*
Student Grades Management System
--------------------------------
A C++ console application to manage student grades including:
- Adding/removing students
- Calculating totals, averages, and percentages
- Finding highest/lowest grades and top students
- Validating grade inputs (max 50)
*/

#include <iostream>
#include <vector>
#include <limits> //lib for function for checking the validation of the input
#include <string>
#include <algorithm> // for sorting built in function 
#include <map> // because i used map for the list and calling the functions
#include <functional> // because i maped on a num of the list with his function 
using namespace std;

    // vec of pari  first -> string for the name of the student 
    //              second -> vec of int for the grades
vector<pair<string,vector<double>>> name_and_grades;
//vec to stor the total grades of students
vector<int>vec_total;

void read_stdents_data(){
        // initial pair to get the data and we will push it int the main vec "name_and_grades"
        pair<string , vector<double>> student ;
        cout<<"enter the name of the student \n";
        cin>>student.first;
        for(int j = 0 ;j<3;j++){
            double subject_grade;
            cout<<"enter the grade of the "<<(j+1)<<" subject \n";
            while(true){
                cin>>subject_grade;
            //  checking if the input is valid or not 
                while(cin.fail()){
                    cout<<"enter an integer <=50 idiot\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cin>>subject_grade;
                }
                if(subject_grade<=50){
                    student.second.push_back(subject_grade);
                    break;
                }
                cout<<"the grade must to be <= 50 ,try again \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n') ;
            }
        }
        sort(student.second.rbegin(),student.second.rend());
        cout<<"\n\n";
        name_and_grades.push_back(student);
        cout<<"student added successfully :) \n";
        return ;
    
}
    // calculate the total grades for each student
double calc_total_grades(const vector<double>& grades){
    double toutal =0;
    for(auto &grade : grades ) toutal+=grade;
    vec_total.push_back(toutal);
    return toutal;
}
// calculate the percentage 
double calc_percentage (int num_of_subjects , double toutal){
    double max_toutal =num_of_subjects*50.0;
   double precent = (toutal/max_toutal)*100.0;
    return precent;
}

double calc_average( int num_of_subjects,double toutal ){
    return (toutal/num_of_subjects);
}

double calc_class_average( int num_of_subjects,double total_class ){
    return total_class/(num_of_subjects*name_and_grades.size());
}
// get all the sudents data 
// total , percentage and average
void print_info(){
    int num_of_subjects = 3;
   //  checking if there are students or not 
     if(name_and_grades.size()==0){
        cout<<"there is no student \n";
        return;
    }
    else{
        double total_class =0;
    for(const auto &data : name_and_grades){
        string name = data.first;
        const vector<double>&grades = data.second ;
        double toutal = calc_total_grades(grades);
        total_class+=toutal;
        cout<<"student: "<<name<<"\n";
        cout<<"the toutal: "<<calc_total_grades(grades)<<"\n";
        cout<<"the percentage: "<<calc_percentage(num_of_subjects,toutal)<<" %\n";
        cout<<"the average: "<<calc_average(num_of_subjects,toutal)<<"\n";
        cout<<"\n";
    }
        cout<<"class average: "<<calc_class_average(num_of_subjects,total_class)<<"\n";
    }
}
// get a specific student data
void student_info(){
     if(name_and_grades.size()==0){
        cout<<"there is no students \n";
    }
    else {
    cout<<"enter the student name to get all his data \n";
    string student_name ; cin>>student_name;
     for(const auto &data : name_and_grades){
        if(student_name==data.first){
            const vector<double>&grades = data.second ;
            double toutal = calc_total_grades(grades);
            cout<<"student: "<<student_name<<"\n";
            cout<<"the toutal: "<<calc_total_grades(grades)<<"\n";
            cout<<"the percentage: "<<calc_percentage(3,toutal)<<" %\n";
            cout<<"the average: "<<calc_average(3,toutal)<<"\n";
            cout<<"\n";
            return ;
        }

    }
    cout<<"there is no student with this name \n";
    }
}

void remove_student(){
    if(name_and_grades.size()==0){
        cout<<"there is no student to remove \n";
        return;
    }
    else {
        cout<<"enter the name of the student you want to remove\n";
        string remove_name;
        cin>>remove_name;
        bool found = false ;
        for(auto it = name_and_grades.begin() ; it!=name_and_grades.end() ; it++){
            if(it->first==remove_name){
               name_and_grades.erase(it);
               found = true;
                cout << "Student removed successfully.\n";
               break;
            }
        }
        if(!found) cout << "Student not found.\n";
    }
}
// compare function to sort the students descending by total grades 
bool compareBySecond(const pair<string, vector<double>>& a,const pair<string, vector<double>>&  b) {
    double totalA = calc_total_grades(a.second);
    double totalB = calc_total_grades(b.second);
    return totalA > totalB;
}

void first_student(){
     if(name_and_grades.size()==0){
        cout<<"there is no student \n";
        return;
    }
    else {
        sort(name_and_grades.begin(),name_and_grades.end(),compareBySecond);
           cout<<"the top student is: "<<name_and_grades[0].first<<"\n";
    }
}


void highest_grade(){
    if(name_and_grades.size()==0){
        cout<<"there is no student \n";
        return;
    }
    else{
        double highest = -1;
            for (const auto& who_the_first : name_and_grades) {
                if (!who_the_first.second.empty()) {
                    if(highest<who_the_first.second.front()){
                        highest =  who_the_first.second.front(); 
                    }
                }
            }
            cout << "The highest grade is: " << highest << "\n";
    }
}
// the name of the student who has the highest grade
void highest_grade_name(){
    if(name_and_grades.size()==0){
        cout<<"there is no student \n";
        return;
    }
    else{
        double highest = -1;
        string highest_grade_student;
            for (const auto& who_the_first : name_and_grades) {
                if (!who_the_first.second.empty()) {
                    if(highest<who_the_first.second.front()){
                        highest =  who_the_first.second.front();
                        highest_grade_student = who_the_first.first; 
                    }
                }
            }
            cout << "The student who has the highest grade is: " << highest_grade_student << "\n";
    }
}

void lowest_grade(){
   double minn = 100;
    if(name_and_grades.size()==0){
        cout<<"there is no student \n";
        return;
    }
    else {
        for (const auto& student : name_and_grades) {
            if (!student.second.empty()) {
               if(minn>student.second.back()){
                minn = student.second.back();
               }  
            }
        }
        cout << "The highest grade is: " << minn << "\n";
    }
}
// the name of the student who has the lowest grade
void lowest_grade_name(){
    if(name_and_grades.size()==0){
        cout<<"there is no student \n";
        return;
    }
    else{
        double highest = -1;
        string lowest_grade_student ;
            for (const auto& who_the_last : name_and_grades) {
                if (!who_the_last.second.empty()) {
                    if(highest<who_the_last.second.front()){
                        highest =  who_the_last.second.front(); 
                        lowest_grade_student = who_the_last.first;
                    }
                }
            }
            cout << "The student who has the lowest grade is: " << lowest_grade_student << "\n";
    }
}
// the highest grade of a student 
void highest_grade_for_student (){ 
    if(name_and_grades.size()==0){
        cout<<"there is no students \n";
    }
    else {

        cout<<"enter the student name \n";
        string student_name; cin>>student_name;
        for(const auto &it :name_and_grades ){
            if(it.first==student_name){
                 cout<<"the highest grade of "<<student_name<<" is : "<<it.second.front()<<" \n";
                 return ;
                }
        }
        cout<<"there is no student with this name :( \n";
    }

}
// the lowest grade of a student 
void lowest_grade_for_student (){
     if(name_and_grades.size()==0){
        cout<<"there is no students \n";
    }
    else { 
    cout<<"enter the student name \n";
    string student_name; cin>>student_name;
    for(const auto &it :name_and_grades ){
        if(it.first==student_name){
             cout<<"the lowest grade of "<<student_name<<" is : "<<it.second.back()<<" \n";
             return ;
        }
        
    }
     cout<<"there is no student with this name :( \n";
    }
}
// the rate of the  students 
void rate_of_students (){
     if(name_and_grades.size()==0){
        cout<<"there is no students \n";
    }
    else {
    sort(name_and_grades.begin(),name_and_grades.end(),compareBySecond);
    cout<<"the rate of the students is : \n";
    int n = 1;
    for(const auto &students : name_and_grades){
        cout<<"student number "<<n++<<" is "<< students.first <<" \n";
    }
    }
}
// here i made a list by map the key is the num of the list and the value is the function i want to call
void list() {
    map<int, function<void()>> actions ;
    actions[1] = read_stdents_data;
    actions[2] = remove_student;
    actions[3] = first_student;
    actions[4] = highest_grade;
    actions[5] = lowest_grade;
    actions[6] = highest_grade_name;
    actions[7] = lowest_grade_name;
    actions[8] = highest_grade_for_student;
    actions[9] = lowest_grade_for_student;
    actions[10] = student_info;
    actions[11] = print_info;
    actions[12] = rate_of_students;

    int num; cin>>num;
    while(cin.fail() || num < 1 || num > 12){
        cout<<"enter a number from 1 to 12 idiot \n"; 
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
        cin>>num;
    }
    actions[num]();
    list();
}
// here is the list 
void print_list(){
    cout << "enter 1 to : Add student and his grades \n";
    cout << "enter 2 to : remove student \n";
    cout << "enter 3 to : know the first student \n";
    cout << "enter 4 to : know the highest grade \n";
    cout << "enter 5 to : know the lowest grade \n";
    cout << "enter 6 to : know the student who has the highest grade \n";
    cout << "enter 7 to : know the student who has the lowest grade \n";
    cout << "enter 8 to : know the highest grade of a student \n";
    cout << "enter 9 to : know the lowest grade of a student \n";
    cout << "enter 10 to : Know the data of a student \n";
    cout << "enter 11 to : Know the data of all students \n";
    cout << "enter 12 to : Know the the rate of students \n";
};

int main(){
    print_list();
    list();

    return 0;
}