
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "PreTriage.h"
#include "utils.h"
#include "Patient.h"
#include "Time.h"

using namespace std;

namespace sdds {
	void PreTriage::reg()
	{
	}

	void PreTriage::admit()
	{
	}

	const Time PreTriage::getWaitTime(const Patient& p) const
	{
		unsigned int count = 0;
		int i;
		for (i = 0; i < m_lineupSize; i++) {
			if (*m_lineup[i] == p) {
				count++;
			}
		}

		if (*m_lineup[i] == 'T') {
			return m_averTriageWait * count;
		}
		else if (*m_lineup[i] == 'C') {
			return m_averCovidWait * count;
		}

	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		Time current;
		current.setToNow();
		Time A = (Time)p + current; //CT-PTT

		int number = p.number() - 1; //PTN

		if (p == 'T') {
			m_averTriageWait = (A + (m_averTriageWait * number)) / p.number();
		}
		else if (p == 'C') {
			 m_averCovidWait = (A + (m_averCovidWait * number)) / p.number();
		}
		
	}

	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const
	{
		for (int i = 0; i < m_lineupSize; i++) {
			if (*m_lineup[i] == type) {
				return i;
			}
			else return -1;
		}
	}

	void PreTriage::load()
	{
	}

	PreTriage::PreTriage(const char* dataFilename): m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit",2),m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage",2),m_averCovidWait(15),m_averTriageWait(5)
	{
		m_dataFilename = new char[sizeof(dataFilename)]; 
		strcpy(m_dataFilename, dataFilename);
		//load();
	}

	PreTriage::~PreTriage()
	{
		ofstream fout; 
		fout.open(m_dataFilename);
		if (fout.is_open()) {
			fout <<  m_averCovidWait << ',' << m_averTriageWait << endl;
			for (int i = 0; i < m_lineupSize; i++){
				fout << i + 1 << "- ";
				m_lineup[i]->csvWrite(fout);
				fout << endl;
			}
		}
		fout.close();

		cout << "Saving Average Wait Times," << endl; 
		cout << "\tCOVID Test: " << m_averCovidWait << endl; 
		cout << "\tTriage: " << m_averTriageWait << endl; 

		for (int i = 0; i < m_lineupSize; i++) { 
			cout << i + 1 << "- "; 
			m_lineup[i]->csvWrite(cout); 
			cout << endl;
		} 

		delete[] m_lineup;
		delete[] m_dataFilename; 
		m_dataFilename = nullptr; 
		cout << "done!";
	}

	void PreTriage::run(void)
	{
		int quit = -1;
		while (quit != 0) {
			m_appMenu >> quit;
			if (quit == 1) {
				reg();
			}
			else if (quit == 2) {
				admit();
			}	
		}
	}
}