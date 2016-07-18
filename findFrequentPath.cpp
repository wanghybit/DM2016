#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;  //max frequent number

struct Session{
    int itemNumber; //number of domain name in each frequent path
    char domainName[10][30];    //domain name in each session
};

struct Day{
    int frequentNumber; //number of frequent path in each day
    Session session[MAXN];    //domain information in each day in each session
}day[10]; //7 in total

char space[10] = "    ";
char changeLine[2] = "\n";
int main() {
    ifstream in[100];
    ofstream out("finalFrequentPath.txt", ios::out|ios::binary);
	char file_name[100];
	char eachLine[300];
	for (int i = 1; i <= 7; i++)
	{
		sprintf(file_name, "%d.txt", i);
		in[i].open(file_name, ios::in);
        in[i].getline(eachLine, 300 * sizeof(char));
        int iSession = 0;
        while (in[i].peek() != EOF) {
            in[i].getline(eachLine, 300 * sizeof(char));
            int len = strlen(eachLine);

            int iDomain = 0;
            int iStr = 0;
            //deal with each session, count number of domain name
            for (int k = 0; k < len; k++) {
                if(eachLine[k] != '=') {
                    day[i].session[iSession].domainName[iDomain][iStr++] = eachLine[k];
                }
                else {
                    k = k+2;
                    day[i].session[iSession].domainName[iDomain][iStr] = '\0';
                    //cout << day[i].session[iSession].domainName[iDomain]<<"   ";
                    while (!(eachLine[k+1]>='0' && eachLine[k+2] <= '9')) {
                            k++;
                    }
                    iStr = 0;
                    iDomain ++;
                }
            }
            day[i].session[iSession].domainName[iDomain][iStr] = '\0';
            //cout << day[i].session[iSession].domainName[iDomain]<<endl;
            //cout<<iDomain<<endl;
            day[i].session[iSession].itemNumber = iDomain;
            iSession++;

        }
        day[i].frequentNumber = iSession;
        in[i].close();
	}

	for (int i = 1; i <= 1; i++) {

        int iSession = day[i].frequentNumber;
        for (int f = 0; f < iSession; f++) {
            bool isFindInEachDay = true;
            int iDomain = day[i].session[f].itemNumber;
            int j = 1;
            for (j = 1; j <= 7; j++) {
                if (i == j) continue;
                 int jSession = day[j].frequentNumber;
                 int k = 0;
                 for (k = 0; k < jSession; k++){ //find in other sessions
                    int jDomain = day[j].session[k].itemNumber;
                    if (iDomain != jDomain) continue;
                    bool isFindInSession = true;
                    for (int m = 0; m < iDomain; m++) { //domain name in each frequent path
                        bool isMatch = false;
                        for (int n = 0; n < jDomain; n++) {
                            if (!strcmp(day[i].session[f].domainName[m], day[j].session[k].domainName[n])) {
                                isMatch = true;
                            }
                        }
                        if (!isMatch) {
                            isFindInSession = false;
                            break;
                        }
                    }
                    if (isFindInSession) {
                        break;
                    }
                }
                //not find in j day
                if (k >= jSession) {
                    isFindInEachDay = false;
                    break;
                }

            }
            // find in each day
            if (j >= 8) {
                for (int m = 0; m < iDomain; m++) {
                    //cout <<day[i].session[f].domainName[m]<<"    ";
                    int len = strlen(day[i].session[f].domainName[m]);
                    out.write(day[i].session[f].domainName[m], len * sizeof(char));
                    out.write(space, 4 * sizeof(char));
                }
                out.write(changeLine, 1 * sizeof(char));
                //cout<<endl;
            }
        }

	}
    out.close();
    return 0;
}

