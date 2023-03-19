//---------------------------------------------------------------------------

#ifndef class_quartH
#define class_quartH

#include "ComObj.hpp"
#include <utilcls.h>

#include <string>
using namespace std;

class Quarter{

private:
	bool date_ERROR_f;          //���� ������ ������
	bool flag_st; 		      	//���� ���������
	bool type_file;             //���� ������ ����� 0-��� 1-excel/calc

	int column;              	//�������
	int row;            	    //������
	int max_work;               //������������� ������ (������������ ��� �������)
	int counter_row;            //������� ������
	int max_value;              //������������ �������

	AnsiString file_address;    //����� ���������� �������� ����
	//string file_address;    //

	Variant quart;              //  ???????

public:

	Quarter(){

		date_ERROR_f = false;
		flag_st = false;
		type_file =false;

		column =0;
		row = 0;
		max_work = 0;
		file_address = "";
		counter_row =0;
		max_value =0;
	}

	//---�������---
	void set_row(int const val);
	void set_max_value(int const val);
	void set_flag(bool const fg);
	void set_type_flag(bool const fg);
	void set_error_flag(bool const fg);

	void set_address(AnsiString const addr);
//	void set_address(string const addr);
	void set_quart(Variant const val);
	void set_max_work(int const val);

	//---�������---
	int get_row();
	int get_max_value();
	int get_counter_row();
	int get_col();
	int get_max_work();

	bool get_flag();
	bool get_type_flag();
	bool get_error_flag();

	AnsiString get_file_addr();
//	string get_file_addr();
	Variant get_quart();

	//---����. ������---
	 void inc_row();
	 void inc_counter_row();
     void exit_Excel();
	 void dec_row();
	 void delete_row();
};




//---------------------------------------------------------------------------
#endif
