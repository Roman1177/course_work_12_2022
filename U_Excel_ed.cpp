//---------------------------------------------------------------------------

#include <vcl.h>
#include <U_Main_form.h>
#include <U_Load_form.h>

#include "ComObj.hpp"
#include <utilcls.h>

#pragma hdrstop

#include "U_Excel_ed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TExcel_editor *Excel_editor;

bool flag_change = false;
Variant excel_file, excel_sheet, excel_cell;
extern AnsiString send_addr_file_txt;

void save_edit_file();
void request();
void close_form();
//---------------------------------------------------------------------------
__fastcall TExcel_editor::TExcel_editor(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TExcel_editor::Button1Click(TObject *Sender)
{
	if(flag_change == true){
		request();
	}else{
	  close_form();
	}
}
//---------------------------------------------------------------------------
void __fastcall TExcel_editor::FormShow(TObject *Sender)
{

	Load_form->Show();	//показываем временное окно, чтобы пользователь не думал будто программа зависла

	AnsiString buffer;
	AnsiString exit_row;

	int row =0;
    StringGrid1->RowCount =1;
	excel_file = CreateOleObject("EXCEL.Application");
	excel_file.OlePropertyGet("Workbooks").OlePropertyGet("Open",WideString(send_addr_file_txt));


	do{
		row++;
		StringGrid1->RowCount += 1;

		for(int i = 1; i <= 3;i++){
			buffer = excel_file.OlePropertyGet("Cells", row, i);

			if(row == 1){
				StringGrid1->Cells[i-1][0] = buffer;    //шапка таблицы
				exit_row = StringGrid1->Cells[0][0];     //костыль
			}else{
				StringGrid1->Cells[i-1][row-1] = buffer;
				exit_row = StringGrid1->Cells[0][row-1];
			}
		}

	}while(exit_row != "");

	StringGrid1->RowCount -= 2;     //удаление лишних строк

	Load_form->Hide();
	MainForm->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TExcel_editor::Button2Click(TObject *Sender)
{
	save_edit_file();
}
//---------------------------------------------------------------------------
void __fastcall TExcel_editor::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(flag_change == true){
		request();
	}else{
	  close_form();
	}
}
//---------------------------------------------------------------------------
void __fastcall TExcel_editor::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	//здесь происходит выделение какой нибудь конкреной ячейки
	 StringGrid1->Options << goEditing;
}
//---------------------------------------------------------------------------
void __fastcall TExcel_editor::StringGrid1KeyPress(TObject *Sender, System::WideChar &Key)
{
	flag_change = true;
}
//---------------------------------------------------------------------------
void save_edit_file(){

	AnsiString str_1;

	int index = Excel_editor->StringGrid1->RowCount;  //получаем количество строк
	int row_excel =1;

	excel_sheet = excel_file.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
	excel_cell = excel_sheet.OlePropertyGet("Item",1).OlePropertyGet("Cells");

	do{
		for(int i = 1; i <= 3;i++){

		  str_1 = Excel_editor->StringGrid1->Cells[i-1][row_excel-1];
		  excel_cell.OlePropertyGet("Item", row_excel , i).OlePropertySet("Value",WideString(str_1));
		}
		row_excel++;
		index--;
	}while(index != 0);

	excel_file.OlePropertyGet("WorkBooks",1).OleProcedure(L"Save");
	flag_change = false;
}
void request(){

	int user_choice_status_flag = Application->MessageBox(L"Сохранить изменения в файле?", L"Запрос", MB_YESNO|MB_ICONEXCLAMATION);

	if(user_choice_status_flag == 6){  //код кнопки да = 6, кнопки нет = 7
	  save_edit_file();
	}
	close_form();
}
void close_form(){
   	excel_file.OleProcedure("Quit");
	excel_file = Unassigned;
	excel_sheet = Unassigned;
	excel_cell = Unassigned;

	//
	MainForm->Show();
}
