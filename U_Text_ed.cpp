//---------------------------------------------------------------------------
/*



*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include <U_Main_form.h>

#pragma hdrstop

#include "U_Text_ed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TText_editor *Text_editor;

bool flag_change = false;
bool flag_save = false;

extern int flag_edit_file;
extern AnsiString send_addr_file_txt;

void request(TObject *Sender);

//---------------------------------------------------------------------------
__fastcall TText_editor::TText_editor(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TText_editor::Button1Click(TObject *Sender)
{
	//���� ���� �� ��� ��������, �� ������������ ������ �� ���������� ���������
	// �� ���������
	// ��� ��������� � �������������� �� ���� �� ��������

	if(flag_change == false || flag_save == true){
		this->Hide();
		MainForm->Show();

	}else{
		request(Sender);
	}

}
//---------------------------------------------------------------------------
void __fastcall TText_editor::FormClose(TObject *Sender, TCloseAction &Action)
{
	// ���� ���� �� ��� ��������, �� ������������ ������ �� ���������� ���������
	// �� ���������
	// ��� ��������� � �������������� �� ���� �� ��������
	if(flag_change == false || flag_save == true){
		this->Hide();
		MainForm->Show();

	}else{
		request(Sender);
	}

}
//---------------------------------------------------------------------------

void __fastcall TText_editor::FormShow(TObject *Sender)
{
	//��������� ���� � ��������� ���� ���� ��������

	OpenDialog1->FileName = send_addr_file_txt;
	Memo1->Lines->LoadFromFile(OpenDialog1->FileName);
	flag_change = false;
	flag_save = false;
}
//---------------------------------------------------------------------------
void __fastcall TText_editor::Button_saveClick(TObject *Sender)
{
	//��������� ���� �� ���������� ����, ��� ����� ������������� ���
	flag_save = true;
	SaveDialog1->FileName = send_addr_file_txt;
	TEncoding *enc;
	Memo1->Lines->SaveToFile(SaveDialog1->FileName,enc->ANSI);

}
//---------------------------------------------------------------------------

void __fastcall TText_editor::Memo1Change(TObject *Sender)
{
	flag_change = true;
}
//---------------------------------------------------------------------------
void request(TObject *Sender){
	int user_choice_status_flag = Application->MessageBox(L"��������� ��������� � �����?", L"������", MB_YESNO|MB_ICONEXCLAMATION);

	if(user_choice_status_flag == 6){  //��� ������ �� = 6, ������ ��� = 7
	  Text_editor->Button_saveClick(Sender);
	}

	Text_editor->Hide();
	MainForm->Show();
}

