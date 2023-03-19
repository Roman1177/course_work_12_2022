#include <vcl.h>

#include <U_About_form.h>
#include <U_Text_ed.h>
#include <U_Excel_ed.h>
#include <U_Start_form.h>
#include <U_Load_form.h>
#include <U_Reference_form.h>

#include <string>
#pragma hdrstop

#include "U_Main_form.h"
#include "class_quart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
Quarter quarter_1;
Quarter quarter_2;
Quarter quarter_3;
Quarter quarter_4;

extern bool start_flag;

bool calculation_flag_status = false;       //���� ������� 0 �������� �� ���� / 1 ��� ������

AnsiString send_addr_file_txt;  			//���������� ��� ��������� ������ �����
int flag_edit_file;                         //���� �������������� �����

//---------------------------------------------------------------------------
bool alphabet_check(string str);
bool numbers_check(string str);
bool max_val_check(int);

int dynamic_prog_method(int,const int,const int);
int box(int W, int *w, int *v, int n);
int greedy_method(int,int,int);
int box_greedy_method(int,int,int*,int*,int,int*,bool,int *count_item);

void qsortRecursive(double*,int,int*,int*);
void open_file(Quarter &quart,int var, AnsiString Open_addr = "");
void save_file();
void edit_file(int);
void Clear_form_data();
void check_date();
void array_ini(int,int*,int*,int);
void result_output(bool type, int var, int *res_list, int count_val, int res_price,  int number_item = 0, int counter_item = 0);
void request_before_close();
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	 flag_edit_file = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	if(start_flag == false){
		Start_form->Show();
	}

	AnsiString order_name = "�������� ������";
	AnsiString workload = "����� ����� (���)";
	AnsiString profit = "������� �� �����";

	//���������� ���������� ����������
	MainForm->StringGrid1->Cells[0][0] = order_name;
	MainForm->StringGrid2->Cells[0][0] = order_name;
	MainForm->StringGrid3->Cells[0][0] = order_name;
	MainForm->StringGrid4->Cells[0][0] = order_name;

	MainForm->StringGrid1->Cells[1][0] = workload;
	MainForm->StringGrid2->Cells[1][0] = workload;
	MainForm->StringGrid3->Cells[1][0] = workload;
	MainForm->StringGrid4->Cells[1][0] = workload;

	MainForm->StringGrid1->Cells[2][0] = profit;
	MainForm->StringGrid2->Cells[2][0] = profit;
	MainForm->StringGrid3->Cells[2][0] = profit;
	MainForm->StringGrid4->Cells[2][0] = profit;

	if(flag_edit_file != 0){

		if(flag_edit_file >= 1 && flag_edit_file <= 4){       //����������� ���� ����� ��� ���������� �� 1 �� 4 TXT, ��� excel
			MainForm->OpenDialog->FilterIndex = 1;
		}else{
			Load_form->Show();
			MainForm->OpenDialog->FilterIndex = 2;
		}

		if(flag_edit_file == 1 || flag_edit_file == 11){           //��������� ���� ��������
			open_file(quarter_1,1,quarter_1.get_file_addr());
		}
		if(flag_edit_file == 2 || flag_edit_file == 12){
			open_file(quarter_2,2,quarter_2.get_file_addr());
		}
		if(flag_edit_file == 3 || flag_edit_file == 13){
			open_file(quarter_3,3,quarter_3.get_file_addr());
		}
		if(flag_edit_file == 4 || flag_edit_file == 14){
			open_file(quarter_4,4,quarter_4.get_file_addr());
		}

		if(MainForm->OpenDialog->FilterIndex == 2){
            Load_form->Hide();
			Excel_editor->Hide();
		}

	  flag_edit_file = 0;  //����� �����
	}

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(calculation_flag_status == true){
	   request_before_close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Open1Click(TObject *Sender){open_file(quarter_1,1);}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Open2Click(TObject *Sender){open_file(quarter_2,2);}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Open3Click(TObject *Sender){open_file(quarter_3,3);}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Open4Click(TObject *Sender){open_file(quarter_4,4);}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Exit1Click(TObject *Sender){MainForm->Close();}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N2Click(TObject *Sender){edit_file(1);}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N21Click(TObject *Sender){edit_file(2);}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N31Click(TObject *Sender){edit_file(3);}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N41Click(TObject *Sender){edit_file(4);}
//---------------------------------------------------------------------------
void __fastcall TMainForm::G1Click(TObject *Sender){Ref_form->Show();}
//---------------------------------------------------------------------------
void __fastcall TMainForm::About1Click(TObject *Sender){About_form->Show();}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender){save_file();}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button5Click(TObject *Sender)
{
	if(quarter_1.get_flag() == true || quarter_2.get_flag() == true || quarter_3.get_flag() == true || quarter_4.get_flag() == true){

		calculation_flag_status = false;    //����� ����� �������
		Clear_form_data();                 	//�������� ������ ���������� ��������
		check_date();                       //�������� ������� ������

		int result = 0;

		if(quarter_1.get_flag() == true && quarter_1.get_error_flag() == false){
			if(max_val_check(1)){  //�������� �� ������� ����. ���������� ������� ����
				quarter_1.set_max_work(MainForm->Edit_qu_1->Text.ToDouble());   //�������� ������������ ��� �������

				if(MainForm->RadioGroup1->ItemIndex == 0){  //������������
					result = dynamic_prog_method(1, quarter_1.get_row(), quarter_1.get_max_work());
				}else{  									//������
					result = greedy_method(1, quarter_1.get_row(), quarter_1.get_max_work());
				}
				quarter_1.set_max_value(result);
			}else{
				Application->MessageBox(L"������� ������������ ����� ������ � 1 �������� \n(�� ����� 91-�� �������� ���)", L"������", MB_OK);
			}
		}

		if(quarter_2.get_flag() == true && quarter_2.get_error_flag() == false){
			if(max_val_check(2)){  //�������� �� ������� ����. ���������� ������� ����
				quarter_2.set_max_work(MainForm->Edit_qu_2->Text.ToDouble());   //�������� ������������ ��� �������

				if(MainForm->RadioGroup1->ItemIndex == 0){  //������������
					result = dynamic_prog_method(2, quarter_2.get_row(), quarter_2.get_max_work());
				}else{  									//������
					result = greedy_method(2, quarter_2.get_row(), quarter_2.get_max_work());
				}
				quarter_2.set_max_value(result);
			}else{
				Application->MessageBox(L"������� ������������ ����� ������ � 2 �������� \n(�� ����� 91-�� �������� ���)", L"������", MB_OK);
			}
		}
		if(quarter_3.get_flag() == true && quarter_3.get_error_flag() == false){
			if(max_val_check(3)){  //�������� �� ������� ����. ���������� ������� ����
				quarter_3.set_max_work(MainForm->Edit_qu_3->Text.ToDouble());   //�������� ������������ ��� �������

				if(MainForm->RadioGroup1->ItemIndex == 0){  //������������
					result = dynamic_prog_method(3, quarter_3.get_row(), quarter_3.get_max_work());
				}else{  									//������
					result = greedy_method(3, quarter_3.get_row(), quarter_3.get_max_work());
				}
				quarter_3.set_max_value(result);
			}else{
				Application->MessageBox(L"������� ������������ ����� ������ � 3 �������� \n(�� ����� 91-�� �������� ���)", L"������", MB_OK);
			}
		}
		if(quarter_4.get_flag() == true && quarter_4.get_error_flag() == false){
			if(max_val_check(4)){  //�������� �� ������� ����. ���������� ������� ����
				quarter_4.set_max_work(MainForm->Edit_qu_4->Text.ToDouble());   //�������� ������������ ��� �������

				if(MainForm->RadioGroup1->ItemIndex == 0){  //������������
					result = dynamic_prog_method(4, quarter_4.get_row(), quarter_4.get_max_work());
				}else{  									//������
					result = greedy_method(4, quarter_4.get_row(), quarter_4.get_max_work());
				}
				quarter_4.set_max_value(result);
			}else{
				Application->MessageBox(L"������� ������������ ����� ������ � 4 �������� \n(�� ����� 91-�� �������� ���)", L"������", MB_OK);
			}
		}

		result = quarter_1.get_max_value() + quarter_2.get_max_value() + quarter_3.get_max_value() + quarter_4.get_max_value();

		MainForm->Edit_result->Text = result;
	}else{
	   Application->MessageBox(L"����������� ������� ������! \n����������, �������� ����(�).", L"������", MB_OK|MB_ICONEXCLAMATION);
	}


}
//---------------------------------------------------------------------------
int dynamic_prog_method(int var,const int  counter_val,const int  weight_max){

//*******************
	//StringGrid1->Cells[�������][������]
//*******************

		int result_price = 0;             	//���������� ��������
		int counter_item = 0;             	//���������� ���������� �������

		int m_weight = weight_max + 1;      // ����������� ������������ ����������� ��� �������
		int m_val = counter_val + 1;        // ����������� ���������� ��������� ��� �������

		int cur_weight = weight_max;        //������� ���

		int *value;
		value = new int [counter_val];      // ������ ��������

		int *weight;
		weight = new int [counter_val];     // ������ ����

		int *resul_list;                 	// ������ ��������� �������� � ����������� �����
		resul_list = new int[counter_val];

		for(int i = 0; i < counter_val; i++ ){
			resul_list[i] = 0;
		}

		double** matrix = new double* [m_val];

		for (int i = 0; i < m_val; i++) {
			matrix[i] = new double[m_weight];
		}

		array_ini(var, value, weight, counter_val); //������������� �������� ����������

		for (int i = 0; i < m_val; i++) {
			matrix[i][0] = 0;    					//�������� 1 ������� ������ ������, ��� ��� ��� ���� ���� ������� 0, ���-�� ��������� 0
		}

		for (int j = 0; j < m_weight; j++) {
			matrix[0][j] = 0;    					//�������� 1 �������� ������ ������, ���������� ����. �����������
		}


		if(MainForm->RadioGroup2->ItemIndex == 0){  	//������� ������������

			for (int k = 1; k < m_val; ++k)            	//������
			{
				for (int s = 1; s < m_weight; ++s)     	//�������
				{
					if (weight[k - 1] <= s) { 		   	//���� ��� �������� ������ ��� ����� ���� S, �� � ������� ������� �������� �����
														//����������� ��������(������, ����� �������) ���
						matrix[k][s] = max(matrix[k - 1][s], matrix[k - 1][s - weight[k - 1]] + value[k - 1]);
					}
					else{                            	//����� ������� ������� �������� ����, ����� �������
						matrix[k][s] = matrix[k - 1][s];
					}
				}
			}

			for(int i = counter_val; i > 0; i--){     						  //������������ ������ �������� ��������� �������� � �������� ����������� �����
				if(matrix[i][cur_weight] !=  matrix[i - 1][cur_weight]){
				   cur_weight -= weight[i-1];
				   resul_list[i-1] = 1; 									  //������������ ������� �� 0 � 1, 1 ���� ������� ������ � ����� ����������� ���������
				}
			}

			result_price = matrix[counter_val][weight_max];   				  //������������ ��������� �������
			result_output(false, var, resul_list, counter_val, result_price); //����� ������ �������� � �������

		}else{                                      //�������� ������������

			int counter = 0;                        //
			int counter_i = 0;                      //���������� ��������� � ������ ������


			for (int i = 0; i < counter_val; i++) {
				for (int j = 0; j < m_weight; j++) {

					if (i - 1 < 0) {
						matrix[i][j] = matrix[0][j];
					}
					else {
						matrix[i][j] = matrix[i - 1][j];
					}
					if (weight[i] <= j) {
						matrix[i][j] = max(matrix[i][j], matrix[i][j - weight[i]] + value[i]);
					}
				}
			}


			for(int i = counter_val - 1; i >= 0; i--){  //������������ ������ ���������� ��� �������� ������������

				if(i > 0){
					if(matrix[i][cur_weight] >  matrix[i - 1][cur_weight]){

						while(cur_weight != 1 && cur_weight > 0){

							cur_weight -= weight[i];
							if(cur_weight > 0){
								counter++;
								counter_i = i;
							}
						}
						break;	//������������� ���������
					}
				}else{
					counter = weight_max;
					counter_i = 0;
				}
			}

			resul_list[0] = value[counter_i];                                                  //����. ��������� ��� ������������ ������ � ��������� value[counter_i]
			result_price = matrix[counter_val - 1][weight_max];                                //����. �������
			result_output(true, var, resul_list, counter_val, result_price,counter_i,counter); //����� ������ �������� � �������
		}

		calculation_flag_status = true; //������ ���������

		for (int i = 0; i < m_val; i++) {
			delete[] matrix[i];
		}

		delete[] matrix;
		delete[] value;
		delete[] weight;
		delete[] resul_list;

		return (result_price);

}
//---------------------------------------------------------------------------
int greedy_method(int var, int counter_val, int weight_max){

	int result_price = 0;             	//���������� ��������
	int counter_item = 0;             	//���������� ���������� �������

	int *value;
	value = new int [counter_val];      // ������ ��������

	int *weight;
	weight = new int [counter_val];     // ������ ����

	int *resul_list;                 	// ������ ��������� �������
	resul_list = new int[counter_val];

	for(int i = 0; i < counter_val; i++ ){
		resul_list[i] = 0;
	}

	array_ini(var, value, weight, counter_val); //������������� �������� ����������

	if(MainForm->RadioGroup2->ItemIndex == 0){  //�������

	   result_price = box_greedy_method(var, weight_max, value, weight, counter_val, resul_list, false, &counter_item);
	   result_output(false, var, resul_list, counter_val, result_price); //����� ������ �������� � �������

	}else{

		int temp_val = 0;

		result_price = box_greedy_method(var, weight_max, value, weight, counter_val, resul_list, true, &counter_item);

		for(int i = 0 ; i < counter_val; i++){                    //����� �������� ��������

			switch(var){
				case 1:{ if(resul_list[0] == MainForm->StringGrid1->Cells[2][i + 1].ToInt()){temp_val = i;} break; }
				case 2:{ if(resul_list[0] == MainForm->StringGrid2->Cells[2][i + 1].ToInt()){temp_val = i;} break; }
				case 3:{ if(resul_list[0] == MainForm->StringGrid3->Cells[2][i + 1].ToInt()){temp_val = i;} break; }
				case 4:{ if(resul_list[0] == MainForm->StringGrid4->Cells[2][i + 1].ToInt()){temp_val = i;} break; }
			}
			if(temp_val != 0){break;}   //� ������ ���� ����� ��������, �������� ��������� ����
		}

		result_output(true, var, resul_list, counter_val, result_price, temp_val, counter_item); //����� ������ �������� � �������

	}

	calculation_flag_status = true; //������ ���������

	delete[] value;
	delete[] weight;
	delete[] resul_list;

	return result_price;
}

void qsortRecursive(double* mas, int size, int *val, int *weig) {
    //��������� � ������ � � ����� �������
    int i = 0;
    int j = size - 1;

	//����������� ������� �������
    double mid = mas[size / 2];

	//����� ������
    do {
        //��������� ��������, ���� ��, ������� ����� ���������� � ������ �����
        //� ����� ����� ������� ����������(��������� �� �����) ��������, ������� ������ ������������
        while (mas[i] > mid) {
            i++;
		}

        //� ������ ����� ���������� ��������, ������� ������ ������������
        while (mas[j] < mid) {
            j--;
        }

        //������ �������� �������
        if (i <= j) {
			double tmp = mas[i];             //��������� �������� ������ �� ��������
			mas[i] = mas[j];
			mas[j] = tmp;

			int temp_1 = val[i];            //������������ ������ � ������� ����, �����
			val[i] = val[j];
            val[j] = temp_1;

            temp_1 = weig[i];
            weig[i] = weig[j];
            weig[j] = temp_1;

            i++;
            j--;
        }
    } while (i <= j);


    //����������� ������, ���� ��������, ��� �����������
    if (j > 0) {
        //"����� �����"
        qsortRecursive(mas, j + 1, val, weig);
    }
    if (i < size) {
        //"����� �����"
        qsortRecursive(&mas[i], size - i, &val[i], &weig[i]);
    }
}

int box_greedy_method(int var, int W, int *val, int* weig, int n, int* res_val, bool type,int *count_item)
{

	double* unit_price;                         //�������� ����
	unit_price = new double[n];

	for (int i = 0; i < n; i++) {                  //������������ ������� �������� ����
		unit_price[i] = (double)val[i] / weig[i];
	}

	qsortRecursive(unit_price, n, val, weig);  //��������� ������� �� �������� �������� ����

	int cur_weight = 0;                         //������� ���
	int tot_value = 0;                          //����� ����
	AnsiString str;

	if(type == false){                          //������� ����� �������

		for (int i = 0; i < n; ++i){

			if (cur_weight + weig[i] <= W){    //���� ������� ��� + ��� i �������� ������ ��� ����� ������������� ����
				cur_weight += weig[i];         //�� �������� ������� ���
				tot_value += val[i];           //��������� ��� ���� � ����� ��������

				for(int j = 0; i < n; j++){   //������������ ������ ��� ������ ������

					switch(var){
						case 1:{str = MainForm->StringGrid1->Cells[2][j+1];break;}
						case 2:{str = MainForm->StringGrid2->Cells[2][j+1];break;}
						case 3:{str = MainForm->StringGrid3->Cells[2][j+1];break;}
						case 4:{str = MainForm->StringGrid4->Cells[2][j+1];break;}
					}

					if(val[i] == (str.ToInt())){//����� ���������� ���������������� ������� � �����������
						res_val[j] = 1;
						break;
					}
				}
			}
		}

	}else{                                      //�������� ����� �������

		res_val[0] = val[0];	//��������� ����������� ����/��������

		while(cur_weight + weig[0] <= W){
			cur_weight += weig[0];
			tot_value += val[0];
			(*count_item)++;
		}

	}
	delete[] unit_price;

	return tot_value;
}
//---------------------------------------------------------------------------
void open_file(Quarter &quart,int var, AnsiString Open_addr){

	if(Open_addr == ""){ 								//���� ���� ����������� � ������, � �� ����� ��������������
		MainForm->OpenDialog->Title = "������� ����";
		MainForm->OpenDialog->FileName = "";			// �� ������ ������
	}

	if(quart.get_flag() == true){   //���� ���� ��� ������ ����� ������� ������ �� ����������
		switch(var){
			case 1:{MainForm->StringGrid1->RowCount = 1;break;}
			case 2:{MainForm->StringGrid2->RowCount = 1;break;}
			case 3:{MainForm->StringGrid3->RowCount = 1;break;}
			case 4:{MainForm->StringGrid4->RowCount = 1;break;}
		}
		quart.set_flag(false);
		quart.set_row(0);
	}

	if(Open_addr == "" && MainForm->OpenDialog->Execute()) { //���� ���� ����������� � ������, � �� ����� ��������������
		quart.set_address(MainForm->OpenDialog->FileName);  //�������� ������
	}else if(Open_addr != ""){
		quart.set_address(Open_addr);
	}

	if(MainForm->OpenDialog->FilterIndex == 1){  //������ txt ����

		string sentence_1 = "";
		string substr = "��������";
		string word = "";
		string name = "";

		bool flag_end_file = true;
		bool flag_first_col = false;
		bool flag_second_col = false;

		int counter_ = 0;
		int a = 0;
		int b = 0;
		int c = 0;

		AnsiString name_file;

		if(Open_addr != ""){ //���� ���� ����������� ����� ��������������
			MainForm->OpenDialog->FileName = Open_addr;
		}

		name_file = ExtractFileName(MainForm->OpenDialog->FileName);

		switch(var){
			case 1:{MainForm->Label1->Caption = "�������� �����: " + name_file; break;}
			case 2:{MainForm->Label4->Caption = "�������� �����: " + name_file;break;}
			case 3:{MainForm->Label8->Caption = "�������� �����: " + name_file;break;}
			case 4:{MainForm->Label12->Caption = "�������� �����: " + name_file;break;}
		}


		ifstream user_file(quart.get_file_addr().c_str());      //������� ���������� ��� ���� � ��������� ����

		if (!user_file.is_open()) {                         	// ���� ���� �� ���������� ������� �������� �� ������
			Application->MessageBox(L"�� ������� ������� ����!", L"������", MB_OK);
		}
		else{                                                   //���� ���� ������� ������

			quart.set_flag(true);
			quart.set_type_flag(false);                         //��� ����� ���
			quart.set_error_flag(false);

			getline(user_file, sentence_1, '\n');		        //����������� ������� ����������� �� ������� ����� ������

			if (sentence_1.find(substr) != std::string::npos) { //���� � ��������� ����������� ���� �������� �����, ����������  �������

				quart.inc_row();
				switch(var){
					case 1:{MainForm->StringGrid1->RowCount += 1;break;}
					case 2:{MainForm->StringGrid2->RowCount += 1;break;}
					case 3:{MainForm->StringGrid3->RowCount += 1;break;}
					case 4:{MainForm->StringGrid4->RowCount += 1;break;}
				}

				flag_end_file = false;
			}

			while (flag_end_file != true) {

				getline(user_file, sentence_1, '\n');           //���������� ����� ������� �� 2 �� ����� �����
				name = "";

				if (sentence_1 == "") {                         //���� ������ ������ ��������� ���������� ������ �� �����
					flag_end_file = true;
				}

				while (sentence_1 != "") {

					if (sentence_1[0] == '\t' || sentence_1[0] == ' ') {  //���� ����� ������ � ������ ������ ��������� ��� ������� �� ������� ���
						sentence_1.erase(0, 1);
						counter_++;                             //������� ����������
					}

					b = sentence_1.find_first_of("\t");         //����� ������� ��������� ������� � ������, � ������� ��� �������
					c = sentence_1.find_first_of(" ");

					if ((b < c && b != -1) || c == -1) {
						word = sentence_1.substr(a, b);             //�������� ��������� ������� (�,�)
					}

					if((c < b && c != -1) || b == -1){
						word = sentence_1.substr(a, c);             //�������� ��������� ������� (�,c)
					}
					if (c == -1 && b == -1) {
						word = sentence_1;
					}

					if (word != "") {                           //���� ��������� �� ������ ������� ��

						bool flag_alphabet = false;             //����� �������� �������� � ���������

						flag_alphabet = alphabet_check(word);

						if ((counter_ == 0 || counter_ == 1) && flag_alphabet == true) { //������ �������
							if(name == ""){
								name = word;
							}else{
								name += " " + word;
							}

							switch(var){
								case 1:{MainForm->StringGrid1->Cells[0][quart.get_row()]= name.c_str();break;}
								case 2:{MainForm->StringGrid2->Cells[0][quart.get_row()]= name.c_str();break;}
								case 3:{MainForm->StringGrid3->Cells[0][quart.get_row()]= name.c_str();break;}
								case 4:{MainForm->StringGrid4->Cells[0][quart.get_row()]= name.c_str();break;}
							}

							flag_first_col = true;
							counter_ = 0;
						}

						if(counter_ > 1 && flag_first_col == false){
							name = "������ ������";
							switch(var){
								case 1:{MainForm->StringGrid1->Cells[0][quart.get_row()]= name.c_str();break;}
								case 2:{MainForm->StringGrid2->Cells[0][quart.get_row()]= name.c_str();break;}
								case 3:{MainForm->StringGrid3->Cells[0][quart.get_row()]= name.c_str();break;}
								case 4:{MainForm->StringGrid4->Cells[0][quart.get_row()]= name.c_str();break;}
							}
							flag_first_col = true;
							quart.set_error_flag(true);
						}

						if (counter_ >= 1 && flag_first_col == true && flag_second_col == false) {  //������ �������

							string  print_word = word;
							if(numbers_check(print_word) == false){ //���� �������� � ����� ����� �� ����� �� ������� �� ����� �����, �� ������� ��� �������
								print_word ="������ ������";
								quart.set_error_flag(true);
							}

							switch(var){
								case 1:{MainForm->StringGrid1->Cells[1][quart.get_row()]= print_word.c_str();break;}
								case 2:{MainForm->StringGrid2->Cells[1][quart.get_row()]= print_word.c_str();break;}
								case 3:{MainForm->StringGrid3->Cells[1][quart.get_row()]= print_word.c_str();break;}
								case 4:{MainForm->StringGrid4->Cells[1][quart.get_row()]= print_word.c_str();break;}
							}

							flag_second_col = true;
							counter_ = 0;
						}
						if (counter_ > 1 && flag_second_col == true) {//������ �������

							string  print_word = word;
							if(numbers_check(print_word) == false){ //���� �������� � ������� �� ����� �� ������� �� ����� �����, �� ������� ��� �������
								print_word ="������ ������";
								quart.set_error_flag(true);
							}

							switch(var){
								case 1:{MainForm->StringGrid1->Cells[2][quart.get_row()]= print_word.c_str();break;}
								case 2:{MainForm->StringGrid2->Cells[2][quart.get_row()]= print_word.c_str();break;}
								case 3:{MainForm->StringGrid3->Cells[2][quart.get_row()]= print_word.c_str();break;}
								case 4:{MainForm->StringGrid4->Cells[2][quart.get_row()]= print_word.c_str();break;}
							}

							quart.inc_row();
							switch(var){
								case 1:{MainForm->StringGrid1->RowCount += 1;break;}
								case 2:{MainForm->StringGrid2->RowCount += 1;break;}
								case 3:{MainForm->StringGrid3->RowCount += 1;break;}
								case 4:{MainForm->StringGrid4->RowCount += 1;break;}
							}

							flag_first_col = false;
							flag_second_col = false;
							counter_ = 0;
						}
					}

					if ((b < c && b != -1) || c == -1) {
						sentence_1.erase(a, b);                     //�������� ��������� �� ������
					}
					if ((c < b && c != -1) || b == -1) {
						sentence_1.erase(a, c);                     //�������� ��������� �� ������
					}
					if (c == -1 && b == -1) {
						sentence_1 = "";                             //�������� �����������, ��� ��� � ��� �� ������� �� ������������� ����������
					}
				}
			}

			quart.dec_row();
			switch(var){//������� ������ ������
				case 1:{MainForm->StringGrid1->RowCount -= 1;break;}
				case 2:{MainForm->StringGrid2->RowCount -= 1;break;}
				case 3:{MainForm->StringGrid3->RowCount -= 1;break;}
				case 4:{MainForm->StringGrid4->RowCount -= 1;break;}
			}

			user_file.close(); // ��������� ����
		}
	}

	if(MainForm->OpenDialog->FilterIndex == 2){    //������ excel

		AnsiString buf;
		AnsiString exit_row;
		AnsiString exit_next_row;

		if(quart.get_file_addr() != ""){

			try{ //������� �������� ����������� � ������
				quart.set_quart(CreateOleObject("EXCEL.Application")); //�������� ������������ � ������

				quart.set_flag(true);
				quart.set_type_flag(true);      //��� �����  1-excel/calc
				quart.set_error_flag(false);    //����� �����

				AnsiString name_file = ExtractFileName(MainForm->OpenDialog->FileName);

				switch(var){
					case 1:{MainForm->Label1->Caption = "�������� �����: " + name_file; break;}
					case 2:{MainForm->Label4->Caption = "�������� �����: " + name_file;break;}
					case 3:{MainForm->Label8->Caption = "�������� �����: " + name_file;break;}
					case 4:{MainForm->Label12->Caption = "�������� �����: " + name_file;break;}
				}
			}
			catch(...){
				ShowMessage("������, ���������� ������� Microsoft Excel");
				quart.set_flag(false);
			}

			Load_form->Show();	//���������� ��������� ����, ����� ������������ �� ����� ����� ��������� �������

			if(quart.get_flag()==true){

				quart.get_quart().OlePropertyGet("Workbooks").OlePropertyGet("Open",WideString(quart.get_file_addr()));

				do{
					quart.inc_row();

					switch(var){
						case 1:{MainForm->StringGrid1->RowCount += 1;break;}
						case 2:{MainForm->StringGrid2->RowCount += 1;break;}
						case 3:{MainForm->StringGrid3->RowCount += 1;break;}
						case 4:{MainForm->StringGrid4->RowCount += 1;break;}
					}

					for(int i = 1; i<= 3 ; i++){

						buf = quart.get_quart().OlePropertyGet("Cells", quart.get_row() + 1, i);

						if(i == 1 && alphabet_check(buf.c_str()) == false){
							buf = "������ ������";
							quart.set_error_flag(true);
						}

						if((i == 2 || i ==3) && numbers_check(buf.c_str()) == false){
							buf = "������ ������";
							quart.set_error_flag(true);
						}

						switch(var){
							case 1:{MainForm->StringGrid1->Cells[i - 1][quart.get_row()] = buf;break;}
							case 2:{MainForm->StringGrid2->Cells[i - 1][quart.get_row()] = buf;break;}
							case 3:{MainForm->StringGrid3->Cells[i - 1][quart.get_row()] = buf;break;}
							case 4:{MainForm->StringGrid4->Cells[i - 1][quart.get_row()] = buf;break;}
						}
					}

					exit_row = quart.get_quart().OlePropertyGet("Cells", quart.get_row() + 1, 1);
					exit_next_row = quart.get_quart().OlePropertyGet("Cells", quart.get_row() + 2, 1);

				}while(exit_row != exit_next_row); //���������� ��������� ������ ����� ��������� ������ � �������

				switch(var){//������� ������ ������
					case 1:{MainForm->StringGrid1->RowCount -= 1;break;}
					case 2:{MainForm->StringGrid2->RowCount -= 1;break;}
					case 3:{MainForm->StringGrid3->RowCount -= 1;break;}
					case 4:{MainForm->StringGrid4->RowCount -= 1;break;}
				}

				quart.dec_row();
				quart.exit_Excel();	// ��������� excel

				Load_form->Hide(); //�������� �������������� �����
			}
		}
	}
 }
void save_file(){

	if(calculation_flag_status == true){
		AnsiString type_metod, buff;

		buff = "������������";

		if(MainForm->RadioGroup2->ItemIndex == 0){   //�������
			type_metod = "�������";
		}else{  									 //��������
			type_metod = "��������";
		}

		AnsiString name_save_file = "�����-�����������_�����_�������";      //�� ���������
		AnsiString type_file =".txt";   									//�� ���������
		AnsiString URL = "C:\\";
		AnsiString file;

		MainForm->SaveDialog->Title = "���������� �����";

		MainForm->SaveDialog->DefaultExt = type_file;                       //�� ��������� ���

		MainForm->SaveDialog->InitialDir = URL;                             //�� ��������� ���� �

		MainForm->SaveDialog->FileName = name_save_file;                    //�� ��������� ��� �����

		if(MainForm->SaveDialog->Execute()) {

			if(MainForm->SaveDialog->FilterIndex == 1){

				URL = MainForm->SaveDialog->FileName;

				file = URL;

				ofstream report_file;             //������� ����
				report_file.open(file.c_str());   //��������� ���� ��� ������

				if(quarter_1.get_flag() == true){
					AnsiString str;
					str ="____I_�������____\n";
					str += type_metod + " " + buff + "\n";

					int index = MainForm->ListBox_qu_1->Count;  //�������� ���������� �����

						for(int i = 0; i < index; i++){
						   AnsiString buf = MainForm->ListBox_qu_1->Items->Strings[i];
						   str += buf + "\n";
						}

					str += "������������ ��������� ������� = " + MainForm->Edit_res_qu_1->Text + "\n";
					report_file << str;
				}
				if(quarter_2.get_flag() == true){
					AnsiString str;
					str ="\n____II_�������____\n";
					str += type_metod + " " + buff + "\n";

					int index = MainForm->ListBox_qu_2->Count;  //�������� ���������� �����

						for(int i = 0; i < index; i++){
						   AnsiString buf = MainForm->ListBox_qu_2->Items->Strings[i];
						   str += buf + "\n";
						}

					str += "������������ ��������� ������� = " + MainForm->Edit_res_qu_2->Text + "\n";
					report_file << str;
				}
				if(quarter_3.get_flag() == true){
					AnsiString str;
					str ="\n____III_�������____\n";
					str += type_metod + " " + buff + "\n";

					int index = MainForm->ListBox_qu_3->Count;  //�������� ���������� �����

						for(int i = 0; i < index; i++){
						   AnsiString buf = MainForm->ListBox_qu_3->Items->Strings[i];
						   str += buf + "\n";
						}

					str += "������������ ��������� ������� = " + MainForm->Edit_res_qu_3->Text + "\n";
					report_file << str;
				}
				if(quarter_4.get_flag() == true){
					AnsiString str;
					str ="\n____IV_�������____\n";
					str += type_metod + " " + buff + "\n";

					int index = MainForm->ListBox_qu_4->Count;  //�������� ���������� �����

						for(int i = 0; i < index; i++){
						   AnsiString buf = MainForm->ListBox_qu_4->Items->Strings[i];
						   str += buf + "\n";
						}

					str += "������������ ��������� ������� = " + MainForm->Edit_res_qu_4->Text + "\n";
					report_file << str;
				}

				AnsiString str_1 =  "\n��������� �������: " + MainForm->Edit_result->Text;

				report_file << str_1;
				report_file.close();
			}

			if(MainForm->SaveDialog->FilterIndex == 2){

				//����� ��� �������
				int _row = 1;   //������
				int _col = 1;   //�������

				URL = MainForm->SaveDialog->FileName;

				file = URL;

				AnsiString str_col_1 = "��������";
				AnsiString str_col_2 = "����������";

				Variant report_file_1, report_book, report_sheets, report_cell;

				report_file_1 = CreateOleObject("Excel.Application");    //������� ������
				report_book = report_file_1.OlePropertyGet("Workbooks");
				report_file_1.OlePropertySet("SheetsInNewWorkbook",1);   //��������� ��� � ������ ����� ������ 1 ��������
				report_book.OleProcedure("Add");                         // ������� �����

				report_sheets = report_book.OlePropertyGet("Item",1).OlePropertyGet("Worksheets");  //�������������� 1 �������� ����� (��� ���������)
				report_sheets.OlePropertyGet("Item",1).OlePropertySet("Name",WideString("�����"));  //������ �������� ��������

				report_cell = report_sheets.OlePropertyGet("Item",1).OlePropertyGet("Cells");       //�������������� ��� ��������� ������ � ��������

				report_cell.OlePropertySet("ColumnWidth",18);	//������������� ������ ����� �������� 130 ��������

				report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_col_1)); //������ �������� Value,WideString(��� ������) �� ������� Item, x,y

				_col = 2; //������� �� ������� ������� ������ ������

				report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_col_2)); //������ �������� Value,WideString(��� ������) �� ������� Item, x,y

				_col = 1;   //������� � ������� 1
				_row = 2;   //����� ������� ������������

				Load_form->Show();  //���������� ���� ����, ����� ������������ �� ������� ����� ��������� �������

				if(quarter_1.get_flag() == true){

					_row++;
					str_col_1 = "____I_�������____";

					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_col_1));
						_row++;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(type_metod));
						_col++;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(buff));
						_row++;
						_col--;

					AnsiString str_1;
					int number =0;
					int size =0;
					int index = MainForm->ListBox_qu_1->Count;  //�������� ���������� �����

						for(int i =0; i < index;i++){

						   AnsiString buf = MainForm->ListBox_qu_1->Items->Strings[i];

						   number = buf.Pos(" ");
						   size = buf.Length();

						   str_1 = buf.SubString(0,number);
						   report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
						   _col++;

						   str_1 = buf.SubString(number,size);
						   report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
						   _row++;
						   _col = 1;
						}

					str_1 = "����� (max):";
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
					_col = 2;

					str_1 = MainForm->Edit_res_qu_1->Text;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
					_row++;
					_col = 1;
				}
				if(quarter_2.get_flag() == true){

					_row++;
					str_col_1 = "____II_�������____";

					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_col_1));
						_row++;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(type_metod));
						_col++;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(buff));
						_row++;
						_col--;

					AnsiString str_1;
					int number =0;
					int size =0;
					int index = MainForm->ListBox_qu_2->Count;  //�������� ���������� �����

						for(int i =0; i < index;i++){

						   AnsiString buf = MainForm->ListBox_qu_2->Items->Strings[i];

						   number = buf.Pos(" ");
						   size = buf.Length();

						   str_1 = buf.SubString(0,number);
						   report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
						   _col++;

						   str_1 = buf.SubString(number,size);
						   report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
						   _row++;
						   _col = 1;
						}

					str_1 = "����� (max):";
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
					_col = 2;

					str_1 = MainForm->Edit_res_qu_2->Text;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
					_row++;
					_col = 1;

				}
				if(quarter_3.get_flag() == true){

					_row++;
					str_col_1 = "____III_�������____";

					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_col_1));
						_row++;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(type_metod));
						_col++;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(buff));
						_row++;
						_col--;

					AnsiString str_1;
					int number =0;
					int size =0;
					int index = MainForm->ListBox_qu_3->Count;  //�������� ���������� �����

						for(int i =0; i < index;i++){

						   AnsiString buf = MainForm->ListBox_qu_3->Items->Strings[i];

						   number = buf.Pos(" ");
						   size = buf.Length();

						   str_1 = buf.SubString(0,number);
						   report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
						   _col++;

						   str_1 = buf.SubString(number,size);
						   report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
						   _row++;
						   _col = 1;
						}

					str_1 = "����� (max):";
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
					_col = 2;

					str_1 = MainForm->Edit_res_qu_3->Text;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
					_row++;
					_col = 1;
				}
				if(quarter_4.get_flag() == true){

					_row++;
					str_col_1 = "____IV_�������____";

					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_col_1));
						_row++;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(type_metod));
						_col++;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(buff));
						_row++;
						_col--;

					AnsiString str_1;
					int number =0;
					int size =0;
					int index = MainForm->ListBox_qu_4->Count;  //�������� ���������� �����

						for(int i =0; i < index;i++){

						   AnsiString buf = MainForm->ListBox_qu_4->Items->Strings[i];

						   number = buf.Pos(" ");
						   size = buf.Length();

						   str_1 = buf.SubString(0,number);
						   report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
						   _col++;

						   str_1 = buf.SubString(number,size);
						   report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
						   _row++;
						   _col = 1;
						}

					str_1 = "����� (max):";
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
					_col = 2;
					str_1 = MainForm->Edit_res_qu_4->Text;
					report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_1));
					_row++;
					_col = 1;
				}

				_row++;
				AnsiString str_end;

				str_end = "��������� ����:";
				report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_end));
				_col = 2;
				str_end = MainForm->Edit_result->Text;
				report_cell.OlePropertyGet("Item", _row , _col).OlePropertySet("Value",WideString(str_end));

				report_file_1.OlePropertyGet("WorkBooks",1).OleProcedure(L"SaveAs",WideString(file)); //���������� ����� �� ������
				report_file_1.OleProcedure("Quit"); //��������� ����
				report_file_1 = Unassigned;
			}
			Load_form->Hide(); //�������� �������������� �����
		}

		calculation_flag_status = false;
		Application->MessageBox(L"����� ������� �����������.", L"�����", MB_OK);

	}else{
		int user_choice_status_flag = Application->MessageBox(L"������������ ������ �����?", L"������", MB_YESNOCANCEL|MB_ICONEXCLAMATION);

		if(user_choice_status_flag == 6){  //��� ������ �� = 6, ������ ��� = 7
			calculation_flag_status = true;
			save_file();
			calculation_flag_status = false;
		}
	}
}
void edit_file(int var){

	switch(var){
		case 1:{
			if(quarter_1.get_flag() == true){
				send_addr_file_txt = quarter_1.get_file_addr();

				if(quarter_1.get_type_flag() == false){   //txt
					flag_edit_file = 1;
					MainForm->Hide();
					Text_editor->Show();
				}else{                                    // excel
					flag_edit_file = 11;
					Excel_editor->Show();
				}
			}else{
				Application->MessageBox(L"���� �����������!", L"������", MB_OK|MB_ICONSTOP);
			}
			break;
		}
		case 2:{
			if(quarter_2.get_flag() == true){
				send_addr_file_txt = quarter_2.get_file_addr();

				if(quarter_2.get_type_flag() == false){   //txt
					flag_edit_file = 2;
					MainForm->Hide();
					Text_editor->Show();
				}else{                                    // excel
					flag_edit_file = 12;
					Excel_editor->Show();
				}
			}else{
				Application->MessageBox(L"���� �����������!", L"������", MB_OK|MB_ICONSTOP);
			}
			break;
		}
		case 3:{
			if(quarter_3.get_flag() == true){
				send_addr_file_txt = quarter_3.get_file_addr();

				if(quarter_3.get_type_flag() == false){   //txt
					flag_edit_file = 3;
					MainForm->Hide();
					Text_editor->Show();
				}else{                                    // excel
					flag_edit_file = 13;
					Excel_editor->Show();
				}
			}else{
				Application->MessageBox(L"���� �����������!", L"������", MB_OK|MB_ICONSTOP);
			}
			break;
		}
		case 4:{
			if(quarter_4.get_flag() == true){
				send_addr_file_txt = quarter_4.get_file_addr();

				if(quarter_4.get_type_flag() == false){   //txt
					flag_edit_file = 4;
					MainForm->Hide();
					Text_editor->Show();
				}else{                                    // excel
					flag_edit_file = 14;
					Excel_editor->Show();
				}
			}else{
				Application->MessageBox(L"���� �����������!", L"������", MB_OK|MB_ICONSTOP);
			}
			break;
		}
	}

}
bool alphabet_check(string str){

	string letters_1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string letters_2 = "�������������������������������������Ũ��������������������������";

	if (str.find_first_of(letters_1) != std::string::npos || str.find_first_of(letters_2) != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}
bool numbers_check(string str){

	string numbers = "0123456789";

	if (str.find_first_of(numbers) != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}
bool max_val_check(int var){
	//������� �������� ������� ������������� ���������� ������� ����
	int value = 0;
	switch(var){
		//������ �������
		case 1:{if(MainForm->Edit_qu_1->Text != ""){value = MainForm->Edit_qu_1->Text.ToDouble();}break;}
		//������ �������
		case 2:{if(MainForm->Edit_qu_2->Text != ""){value = MainForm->Edit_qu_2->Text.ToDouble();}break;}
		//������ �������
		case 3:{if(MainForm->Edit_qu_3->Text != ""){value = MainForm->Edit_qu_3->Text.ToDouble();}break;}
		//��������� �������
		case 4:{if(MainForm->Edit_qu_4->Text != ""){value = MainForm->Edit_qu_4->Text.ToDouble();}break;}
	}

	if(value > 0 && value <=91){
		return (true);
	}else{
		return (false);
	}
}
void Clear_form_data(){
	//������� �������� ������, ���� ����� ��� ���������� ������
	if(quarter_1.get_flag() == true){
	   MainForm->Edit_res_qu_1->Text = 0;
	   MainForm->ListBox_qu_1->Items->Clear();
	}
	if(quarter_2.get_flag() == true){
	   MainForm->Edit_res_qu_2->Text = 0;
	   MainForm->ListBox_qu_2->Items->Clear();
	}
	if(quarter_3.get_flag() == true){
	   MainForm->Edit_res_qu_3->Text = 0;
	   MainForm->ListBox_qu_3->Items->Clear();
	}
	if(quarter_4.get_flag() == true){
	   MainForm->Edit_res_qu_4->Text = 0;
	   MainForm->ListBox_qu_4->Items->Clear();
	}
}
void array_ini(int var, int *val, int *wei, int n){
	//������� ���������� �������� ������� ��� ������������ �������
	AnsiString str_1;
	AnsiString str_2;

	switch(var){
		case 1:{       //������ �������
			for(int i = 0; i < n; ++i){
				if(MainForm->StringGrid1->Cells[1][i+1] != "" && MainForm->StringGrid1->Cells[2][i+1] != ""){
					wei[i] = MainForm->StringGrid1->Cells[1][i+1].ToDouble();
					val[i] = MainForm->StringGrid1->Cells[2][i+1].ToDouble();
				}else{
					wei[i] = 0;
					val[i] = 0;
				}
			}
			break;
		}
		case 2:{       //������ �������
			for(int i = 0; i < n; ++i){
				if(MainForm->StringGrid2->Cells[1][i+1] != "" && MainForm->StringGrid2->Cells[2][i+1] != ""){
					wei[i] = MainForm->StringGrid2->Cells[1][i+1].ToDouble();
					val[i] = MainForm->StringGrid2->Cells[2][i+1].ToDouble();
				}else{
					wei[i] = 0;
					val[i] = 0;
				}
			}
			break;
		}
		case 3:{       //������ �������
			for(int i = 0; i < n; ++i){
				if(MainForm->StringGrid3->Cells[1][i+1] != "" && MainForm->StringGrid3->Cells[2][i+1] != ""){
					wei[i] = MainForm->StringGrid3->Cells[1][i+1].ToDouble();
					val[i] = MainForm->StringGrid3->Cells[2][i+1].ToDouble();
				}else{
					wei[i] = 0;
					val[i] = 0;
				}
			}
			break;
		}
		case 4:{       //��������� �������
			for(int i = 0; i < n; ++i){
				if(MainForm->StringGrid4->Cells[1][i+1] != "" && MainForm->StringGrid4->Cells[2][i+1] != ""){
					wei[i] = MainForm->StringGrid4->Cells[1][i+1].ToDouble();
					val[i] = MainForm->StringGrid4->Cells[2][i+1].ToDouble();
				}else{
					wei[i] = 0;
					val[i] = 0;
				}
			}
			break;
		}

	}

}
void result_output(bool type, int var, int *res_list, int count_val, int res_price,  int number_item, int counter_item){
	//������� ������ �����������
	if(type == false){ //�������

		for(int i = 0; i < count_val; i++){

			switch(var){
				case 1:{
					if(res_list[i] == 1){
						AnsiString s1 = MainForm->StringGrid1->Cells[0][i+1] + ": " + MainForm->StringGrid1->Cells[2][i+1]  + " x 1";
						MainForm->ListBox_qu_1->Items->Add(s1);
					}
					break;
				}
				case 2:{
					if(res_list[i] == 1){
						AnsiString s1 = MainForm->StringGrid2->Cells[0][i+1] + ": " + MainForm->StringGrid2->Cells[2][i+1]  + " x 1";
						MainForm->ListBox_qu_2->Items->Add(s1);
					}
					break;
				}
				case 3:{
					if(res_list[i] == 1){
						AnsiString s1 = MainForm->StringGrid3->Cells[0][i+1] + ": " + MainForm->StringGrid3->Cells[2][i+1]  + " x 1";
						MainForm->ListBox_qu_3->Items->Add(s1);
					}
					break;
				}
				case 4:{
					if(res_list[i] == 1){
						AnsiString s1 = MainForm->StringGrid4->Cells[0][i+1] + ": " + MainForm->StringGrid4->Cells[2][i+1]  + " x 1";
						MainForm->ListBox_qu_4->Items->Add(s1);
					}
					break;
				}
			}
		}
		switch(var){
			case 1:{MainForm->Edit_res_qu_1->Text = res_price;break;}
			case 2:{MainForm->Edit_res_qu_2->Text = res_price;break;}
			case 3:{MainForm->Edit_res_qu_3->Text = res_price;break;}
			case 4:{MainForm->Edit_res_qu_4->Text = res_price;break;}
		}

	}else{             //��������

		switch(var){
			case 1:{
				AnsiString s1 = MainForm->StringGrid1->Cells[0][number_item+1] + ": " + IntToStr(res_list[0]) + " x " + IntToStr(counter_item);
				MainForm->ListBox_qu_1->Items->Add(s1);
				MainForm->Edit_res_qu_1->Text = res_price;
			break;
			}
			case 2:{
				AnsiString s1 = MainForm->StringGrid2->Cells[0][number_item+1] + ": " + IntToStr(res_list[0]) + " x " + IntToStr(counter_item);
				MainForm->ListBox_qu_2->Items->Add(s1);
				MainForm->Edit_res_qu_2->Text = res_price;
			break;
			}
			case 3:{
				AnsiString s1 = MainForm->StringGrid3->Cells[0][number_item+1] + ": " + IntToStr(res_list[0]) + " x " + IntToStr(counter_item);
				MainForm->ListBox_qu_3->Items->Add(s1);
				MainForm->Edit_res_qu_3->Text = res_price;
			break;
			}
			case 4:{
				AnsiString s1 = MainForm->StringGrid4->Cells[0][number_item+1] + ": " + IntToStr(res_list[0]) + " x " + IntToStr(counter_item);
				MainForm->ListBox_qu_4->Items->Add(s1);
				MainForm->Edit_res_qu_4->Text = res_price;
			break;
			}
		}
	}
}
void check_date(){
	//������� �������� ������������ ������
	if(quarter_1.get_flag() == true && quarter_1.get_error_flag() == true){
		Application->MessageBox(L"������ ������ ������ �� �����! \n���������� ��������� � ������������ ������� ������ ����� �������� I.", L"������", MB_OK|MB_ICONEXCLAMATION);
	}
	if(quarter_2.get_flag() == true && quarter_2.get_error_flag() == true){
		Application->MessageBox(L"������ ������ ������ �� �����! \n���������� ��������� � ������������ ������� ������ ����� �������� II.", L"������", MB_OK|MB_ICONEXCLAMATION);
	}
	if(quarter_3.get_flag() == true && quarter_3.get_error_flag() == true){
		Application->MessageBox(L"������ ������ ������ �� �����! \n���������� ��������� � ������������ ������� ������ ����� �������� III.", L"������", MB_OK|MB_ICONEXCLAMATION);
	}
	if(quarter_4.get_flag() == true && quarter_4.get_error_flag() == true){
		Application->MessageBox(L"������ ������ ������ �� �����! \n���������� ��������� � ������������ ������� ������ ����� �������� IV.", L"������", MB_OK|MB_ICONEXCLAMATION);
	}
}
void request_before_close(){
	//������� ������� �� ���������� ���������� �������, ���� ���������� �� ����
	int user_choice_status_flag = Application->MessageBox(L"��������� ���������� �������� � �����?", L"������", MB_YESNO|MB_ICONEXCLAMATION);

	if(user_choice_status_flag == 6){  //��� ������ �� = 6, ������ ��� = 7
		save_file();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Edit_qu_1KeyPress(TObject *Sender, System::WideChar &Key){
	//������� ��������� ����� ������ (����. ���������� ������� ���� � ��������)

	if (Sender) {//�������� �� ������� 0 ��� ������ �����, true -> �������
		if(MainForm->Edit_qu_1->Text == "0" && MainForm->Edit_qu_1->Focused()){
			MainForm->Edit_qu_1->Text = "";
		}
		if(MainForm->Edit_qu_2->Text == "0" && MainForm->Edit_qu_2->Focused()){
			MainForm->Edit_qu_2->Text = "";
		}
		if(MainForm->Edit_qu_3->Text == "0" && MainForm->Edit_qu_3->Focused()){
			MainForm->Edit_qu_3->Text = "";
		}
		if(MainForm->Edit_qu_4->Text == "0" && MainForm->Edit_qu_4->Focused()){
			MainForm->Edit_qu_4->Text = "";
		}
	}

	//��������� ����� ������, ������ �� ���� ����� �������� ����� ���� � backspace
	if(!((Key >= '0' && Key <= '9') || (Key == VK_BACK))){
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

