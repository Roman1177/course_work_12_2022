//---------------------------------------------------------------------------

#ifndef U_About_formH
#define U_About_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TAbout_form : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TLabel *Label1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TAbout_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAbout_form *About_form;
//---------------------------------------------------------------------------
#endif
