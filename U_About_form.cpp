//---------------------------------------------------------------------------

#include <vcl.h>
#include <U_Main_form.h>
#pragma hdrstop

#include "U_About_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbout_form *About_form;
//---------------------------------------------------------------------------
__fastcall TAbout_form::TAbout_form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAbout_form::Button1Click(TObject *Sender)
{
	this->Hide();
	MainForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TAbout_form::FormClose(TObject *Sender, TCloseAction &Action)
{
	this->Hide();
	MainForm->Show();
}
//---------------------------------------------------------------------------
