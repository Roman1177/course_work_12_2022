//---------------------------------------------------------------------------

#include <vcl.h>
#include <U_Main_form.h>

#pragma hdrstop

#include "U_Reference_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRef_form *Ref_form;
//---------------------------------------------------------------------------
__fastcall TRef_form::TRef_form(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TRef_form::FormClose(TObject *Sender, TCloseAction &Action)
{
	this->Hide();
}
//---------------------------------------------------------------------------
