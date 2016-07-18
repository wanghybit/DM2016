#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

const int SESSCION_LENGTH = 1010;
const int FILE_LENGTH = 1010;
const int MAX_NUMBERS = 100010;
const int DOMAIN_NAME_LENGTH = 201;
const int EPISODE_LENGTH = 100;
const int HOUR = 48;
const int EPS = 0;

struct Domain {
    char name[MAX_NUMBERS][DOMAIN_NAME_LENGTH];     //domain name
    int timesOfEachDomain[MAX_NUMBERS];    //times of each domain name
    int numberOfDifferentDomain;    //number of different domain name in each hour
    bool isRetrialed[MAX_NUMBERS];  //mark each domain name when computing frequent episode
}domain[HOUR];


int main() {
    ifstream readFile;
    ofstream writeFile;
    char originalFile[FILE_LENGTH] = "CSession_01";
    char preprocessedFile[FILE_LENGTH] = "FrequentEpisode";

    readFile.open(originalFile, ios::in);
    if (!readFile.is_open()) {
        cout << "OPEN FAILED!" << endl;
        exit(0);
    }

    writeFile.open(preprocessedFile, ios::out);
    if (!writeFile.is_open()) {
        cout << "OPEN FAILED!" << endl;
        exit(0);
    }

    char eachSesscion[SESSCION_LENGTH];
    int iDomain = 0;
    char temp[DOMAIN_NAME_LENGTH];
    char timeHour[4] = "";  //record time of each session
    int iTime = 0;
    bool isTheFirstTime = false;
    while (readFile.peek()!=EOF) {
        //get each domain name and count the number of queries of at each domain name by hour
        readFile.getline(eachSesscion, SESSCION_LENGTH);
        sscanf(eachSesscion, "%*[^ ] %[^|]", temp);
        char timeTemp[4];
        sscanf(eachSesscion,"%2s", timeTemp);

        //count the number of queries during each hour
        if ((!isTheFirstTime) || (!strcmp(timeHour, timeTemp))) {
            if(!isTheFirstTime) {
                strcpy(timeHour, timeTemp);
                isTheFirstTime = true;
            }

            bool isFind = false;
            for (int i = 0; i < iDomain; i++) {
                if (!strcmp(domain[iTime].name[i], temp)){
                    domain[iTime].timesOfEachDomain[i]++;
                    isFind = true;
                    break;
                }
            }
            //cout<<temp<<endl;
            if (!isFind) {
                strcpy(domain[iTime].name[iDomain], temp);
                domain[iTime].timesOfEachDomain[iDomain]++;
                iDomain++;
            }
        }
        else {
            //there are some wrong time order in data set
            //then we need to store the session in the last hour **ignore
            if (((timeTemp[0] == '1')&&strcmp(timeHour, timeTemp)>0)
                ||((timeTemp[0] == '0')&&(timeTemp[0] == '2')&&strcmp(timeHour, timeTemp)<0)) {
                cout<<"**"<<endl;
                continue;
            }

            cout <<iTime<<endl;
            cout << temp<<endl;
            cout<<timeTemp<<endl;
            domain[iTime].numberOfDifferentDomain = iDomain;
            iDomain = 0;
            iTime++;
            strcpy(timeHour, timeTemp);
            strcpy(domain[iTime].name[iDomain], temp);
            domain[iTime].timesOfEachDomain[iDomain]++;


        }

    }
   // iTime++;
    cout<<iTime<<endl;

    //get frequent episode of each domain name
    for (int i = 0; i < iTime; i++){
        for (int j= 0; j < domain[i].numberOfDifferentDomain; j++) {
            //if (domain[i].timesOfEachDomain[j] < 50) continue;
            if (domain[i].isRetrialed[j]) continue;
            //if (strcmp("attack.eatuo.com.", domain[i].name[j])) continue;
            char frequentEpisode[EPISODE_LENGTH];
            domain[i].isRetrialed[j] = true;

            int len = 0;
            frequentEpisode[len++] = '0';
            frequentEpisode[len++] = '0';
            frequentEpisode[len++] = 's';
            int preNumbers = domain[i].timesOfEachDomain[j]; //number of the domain name in previous hour
            for (int m = 1; m < iTime; m++){

                if (m < 10)  frequentEpisode[len++] = '0';
                else if (m >= 10)  frequentEpisode[len++] = m/10 +'0';
                frequentEpisode[len++] = m%10 +'0';
                if (i == m) {
                    frequentEpisode[len++] = 'u';
                    continue;
                }
                //no appearing in the previous time
                if (i >= m) {
                    frequentEpisode[len++] = 's';
                    continue;
                }
                int n = 0;
                for (n = 0; n < domain[m].numberOfDifferentDomain; n++) {
                    if (domain[m].isRetrialed[n]) continue;
                    if (!strcmp(domain[i].name[j], domain[m].name[n])) {
                        domain[m].isRetrialed[n] = true;
                        if ( preNumbers == domain[m].timesOfEachDomain[n]) {
                            frequentEpisode[len++] = 's';
                        }
                        else if (preNumbers - domain[m].timesOfEachDomain[n] > EPS) {
                            frequentEpisode[len++] = 'd';
                        }
                        else {
                            frequentEpisode[len++] = 'u';
                        }
                        preNumbers = domain[m].timesOfEachDomain[n];
                        break;
                    }
                }

                //if not find in current hour m
                if (n >= domain[m].numberOfDifferentDomain) {
                    frequentEpisode[len++] = 'd';
                    preNumbers = 0;
                }
             }
             frequentEpisode[len] = '\0';
             int l = strlen(domain[i].name[j]);
             //writeFile.write((char *)(&l), sizeof(int));
             domain[i].name[j][l++] = ' ';domain[i].name[j][l] = '\0';
             writeFile.write(domain[i].name[j], l * sizeof(char));
             frequentEpisode[len++] = '\n';frequentEpisode[len] = '\0';
             writeFile.write(frequentEpisode, len * sizeof(char));
             //cout << domain[i].name[j]<<"***"<<frequentEpisode<<endl;
        }
    }

    cout <<iDomain <<endl;
    writeFile.close();
    readFile.close();

    /*readFile.open(preprocessedFile, ios::in);
    int l;
    char domainName[DOMAIN_NAME_LENGTH];
    int num;
    while (readFile.peek() != EOF) {
        readFile.read((char *)(&l), sizeof(int));
        readFile.read(domainName, l * sizeof(char));
        domainName[l] = '\0';
        readFile.read((char *)(&num), sizeof(int));
        cout << l << "   " << domainName << num<< endl;
    }
    readFile.close();*/

    system("pause");
    return 0;
}
/*
com edu gov mil net org int arts firm info nom rec store web
 cn hk mo tw us uk jp

*/
