//---------------------------------------------------------------------------

#include <vcl.h>

#include <U_Main_form.h>
#pragma hdrstop

#include "U_Start_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStart_form *Start_form;

bool start_flag = false;
//---------------------------------------------------------------------------
__fastcall TStart_form::TStart_form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TStart_form::ÏðîäîëæèòüClick(TObject *Sender)
{
	start_flag = true;
	this->Hide();
	MainForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TStart_form::FormClose(TObject *Sender, TCloseAction &Action)
{
	start_flag = true;
	this->Hide();
	MainForm->Show();
	MainForm->Visible = true;
}
//---------------------------------------------------------------------------



