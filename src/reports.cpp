/* File: reports.cpp
 * Description: Functions related to creating solution reports.
 */

#include<iostream>
#include<iomanip>
#include<ostream>
#include<cmath>

#include "pattern.h"
#include "cmdline.h"
#include "extern.h"

using namespace std;

/*-------------------------------------------------------------------
 * Precondition: Call to function store_solution.
 * Print stored solution patterns completely. 
-------------------------------------------------------------------*/
void Pattern::print_solution(glp_prob * master_lp, OrderWidthContainer& ow_set)
{

	for(int i = 0; i < (int)option->rformats.size(); i++)
	{
		char * filename = option->rfilenames[i];

		/* Restore cout to original state. */
		if(option->silent == true)
			cout.rdbuf(option->cout_buf);

		if(option->rformats[i] == TEXT) {

			if(!strcmp(filename, "stdout"))
				print_text_report(cout, master_lp, ow_set);
			else {
				ofstream fout(filename);
				cout<<"Generating solution report "<<filename<<endl;
				print_text_report(fout, master_lp, ow_set);
			}

		} else if(option->rformats[i] == XML) {

			if(!strcmp(filename, "stdout"))
				print_xml_report(cout, master_lp, ow_set);
			else {
				ofstream fout(filename);
				cout<<"Generating solution report "<<filename<<endl;
				print_xml_report(fout, master_lp, ow_set);
			}
		}
	}
}

/*-------------------------------------------------------------------
 * Print solution report to 'fout' in text format. 
-------------------------------------------------------------------*/
void Pattern::print_text_report(ostream& fout, glp_prob * master_lp, OrderWidthContainer& ow_set)
{
	double x;
	fout << endl << " # Solution Report # "<< endl << endl;
	fout << "Best integer obj. func. value = " << BBNode::get_best_int_obj_val() << endl;

	PatternIterator pat_iter = PatternList.begin();	
	for(; pat_iter != PatternList.end(); pat_iter++) {
		
		x = (*pat_iter)->get_int_sol();
		if(fabs(x) <= EPSILON)
			continue;

		fout<< "Pattern count = "<<setw(4)<<x<<": ";

		for(int i = 1; i <= (*pat_iter)->nzcnt; i++) {
			int ow_row_index = (*pat_iter)->ind[i];
			double ow_count = (*pat_iter)->val[i];

			OrderWidth * ow;
		       	ow = OrderWidth::find_orderwidth(ow_set, ow_row_index);
			fout<<setw(5)<<ow->get_width() << " x " <<setw(2)<< ow_count <<", ";			
		}
		fout << endl;		
	}
}

/*-------------------------------------------------------------------
 * Print solution report to 'fout' in XML format. 
-------------------------------------------------------------------*/
void Pattern::print_xml_report(ostream& fout, glp_prob * master_lp, OrderWidthContainer& ow_set) 
{
	fout << "TODO: XML Solution report" << endl;
}
