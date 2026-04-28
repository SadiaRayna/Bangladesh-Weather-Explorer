
/*
 * Bangladesh Weather Explorer — DS Project
 * DS: Struct Array, Stack, Queue, Bubble Sort
 * Data: 10 cities x 15 days (April 2026)
 */

#include <iostream>
#include <string>
using namespace std;

const int MAX=150, C=10, DAYS=15; // 10 cities x 15 days = 150 records

// single city list used by all functions
string cities[C] = {"Dhaka","Chittagong","Rajshahi","Khulna","Barishal",
 "Sylhet","Rangpur","Mymensingh","Cumilla","Bogura"};

// DS 1: Struct Array — groups all weather fields into one unit
struct WeatherRecord { int date; string city; float temp, humidity, rain; };
WeatherRecord records[MAX]; // main dataset
int recCount = 0; // number of loaded records

// DS 2: Stack — weather history (LIFO)
// push adds on top, pop retrieves last added first
WeatherRecord stk[MAX]; int top = -1; // top=-1 means empty
void push(WeatherRecord r) { stk[++top] = r; } // increment then insert
WeatherRecord pop() { return stk[top--]; } // return then decrement
bool stackEmpty() { return top == -1; }

// DS 3: Queue — city requests (FIFO)
// enqueue adds to rear, dequeue serves from front
string cq[MAX]; int qf=0, qr=0; // qf=front, qr=rear
void enqueue(string s) { cq[qr++] = s; } // insert at rear
string dequeue() { return cq[qf++]; } // serve from front
bool queueEmpty() { return qf == qr; } // empty when front catches rear

void printRec(const WeatherRecord& r) {
 cout << " [Apr " << r.date << "] " << r.city
 << " | Temp:" << r.temp << "C"
 << " Humidity:" << r.humidity << "%"
 << " Rain:" << r.rain << "%\n";
}

// shows city list, returns 0-based index or -1 if invalid
int pickCity() {
 for (int i=0;i<C;i++) cout << " " << i+1 << "." << cities[i];
 cout << "\n City: ";
 int c; cin >> c;
 return (c>=1 && c<=C) ? c-1 : -1;
}

// generates all 150 records using base values + daily offsets
void loadData() {
 float base[C][3] = {
 {32,78,55},{30,83,68},{35,64,22},{33,77,50},{31,82,65},
 {29,85,73},{28,76,40},{31,80,58},{32,78,53},{30,76,43}
 };
 float tv[DAYS] = { 0.5,-1,1,-0.5,-2,-1.5,0,1,-0.5,1.5,2,-1,-2,-1.5,0.5};
 float hv[DAYS] = {0,2,-3,4,7,9,5,1,-2,-4,-6,2,6,10,3};
 float rv[DAYS] = {0,5,-15,15,25,30,10,-5,-10,-20,-25,5,20,35,0};
 recCount = 0;
 for (int c=0;c<C;c++)
 for (int d=0;d<DAYS;d++)
 records[recCount++] = {d+1, cities[c],
 base[c][0]+tv[d], base[c][1]+hv[d], base[c][2]+rv[d]};
}

// DS 4: Bubble Sort — sorts a copy of records[] (sortBy: 1=temp, 2=humidity, 3=rain)
void bubbleSort(int sortBy) {
 WeatherRecord s[MAX];
 for (int i=0;i<recCount;i++) s[i]=records[i]; // copy to protect original
 for (int i=0;i<recCount-1;i++)
 for (int j=0;j<recCount-i-1;j++) {
 float a = sortBy==1?s[j].temp:sortBy==2?s[j].humidity:s[j].rain;
 float b = sortBy==1?s[j+1].temp:sortBy==2?s[j+1].humidity:s[j+1].rain;
 if (a>b) { WeatherRecord t=s[j]; s[j]=s[j+1]; s[j+1]=t; }
 }
 cout << " Sorted by " << (sortBy==1?"Temp":sortBy==2?"Humidity":"Rain") << ":\n";
 for (int i=0;i<recCount;i++) printRec(s[i]);
}

int main() {
 loadData();
 cout << "=== Bangladesh Weather Explorer ===\n"
 << " 10 cities | 15 days (April 2026)\n";

 int ch;
 do {
 cout << "\n 1.View 2.Push to history [Stack]\n"
 << " 3.Pop history 4.Enqueue city [Queue]\n"
 << " 5.Process queue 6.Sort by temp [Bubble Sort]\n"
 << " 7.Sort by humidity 8.Sort by rain [Bubble Sort]\n"
 << " 0.Exit\n Choice: ";
 cin >> ch;

 if (ch==1||ch==2) {
 int ci = pickCity();
 if (ci==-1) { cout << " Invalid.\n"; continue; }
 int d; cout << " Date (1-15): "; cin >> d;
 bool found=false;
 for (int i=0;i<recCount;i++)
 if (records[i].city==cities[ci] && records[i].date==d) {
 if (ch==1) printRec(records[i]);
 else { push(records[i]); cout << " Pushed.\n"; }
 found=true; break;
 }
 if (!found) cout << " Not found.\n";
 }
 else if (ch==3) {
 if (stackEmpty()) cout << " History empty.\n";
 else { cout << " Last viewed:\n"; printRec(pop()); }
 }
 else if (ch==4) {
 int ci = pickCity();
 if (ci==-1) { cout << " Invalid.\n"; continue; }
 enqueue(cities[ci]); cout << " " << cities[ci] << " enqueued.\n";
 }
 else if (ch==5) {
 if (queueEmpty()) { cout << " Queue empty.\n"; continue; }
 string city = dequeue();
 cout << " Processing: " << city << "\n";
 for (int i=0;i<recCount;i++)
 if (records[i].city==city) printRec(records[i]);
 }
 else if (ch>=6&&ch<=8) bubbleSort(ch-5);
 else if (ch==0) cout << " Goodbye!\n";
 else cout << " Invalid choice.\n";

 } while (ch!=0);
 return 0;
}
